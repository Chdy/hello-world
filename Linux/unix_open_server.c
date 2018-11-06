//
// Created by 邓岩 on 2018/10/25.
//
// 该程序需要在客户端运行之前运行，运行后建立监听描述符，当接收到请求后，将新建立的连接添加到监控描述符集内
// 注意：连接请求会导致监听描述符收到数据，此时select或者poll会返回，连接断开时，建立连接的那个文件描述符会由阻塞读变成不阻塞读状态(此时读取会直接返回0)，所以此时也会造成select和poll函数返回
// 这里有两个不同函数实现的方案，分别使用select或poll，对应的函数为loop_select，loop_poll，该程序原本可以设置为守护进程，不过由于我跳过了守护进程的章节，所以暂时不实现

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include "send_fd.h"
# include "unix_socket_api.h"

#define CS_OPEN "/Users/dengyan/serve"
#define CL_OPEN "open"
#define MAXLINE 100
#define WHITE " \n\t"
#define NALLOC 10 //每次扩展的客户进程结构体数量

typedef struct {
    int fd;
    uid_t uid;
}Client;

char errmsg[MAXLINE];
int flag;
char * pathname;
Client * client;
int client_size;

int cli_args(int, char **);
void handle_request(char *, int, int);
int buf_args(char * buf, int (*optfunc)(int, char **));
int client_add(int, uid_t);
void client_del(int);
static void client_alloc(void);
void loop_select(void);
void loop_poll(void);
static struct pollfd * grow_pollfd(struct pollfd * pfd, int * maxfd);

int main(int argc, char ** args)
{
    setbuf(stdout, NULL);
    loop_poll();
}

static struct pollfd * grow_pollfd(struct pollfd * pfd, int * maxfd)
{
    int i;
    int oldmax = *maxfd;
    int newmax = oldmax + NALLOC;

    if ((pfd = realloc(pfd, newmax * sizeof(struct pollfd))) == NULL) {
        printf("realloc error");
        return NULL;
    }
    for (i = 0; i < newmax; ++i) {
        pfd[i].fd = -1;
        pfd[i].events = POLLIN;
        pfd[i].revents = 0;
    }
    *maxfd = newmax;
    return pfd;
}

void loop_poll(void)
{
    int i, listenfd, clifd, nread;
    char buf[MAXLINE];
    uid_t uid;
    struct pollfd * pollfd;
    int numfd = 1;
    int maxfd = NALLOC;

    if ((pollfd = malloc(NALLOC * sizeof(struct pollfd))) == NULL) {
        printf("malloc error");
        return;
    }
    for (i = 0; i < NALLOC; ++i) { //初始化polled结构
        pollfd[i].fd = -1;
        pollfd[i].events = POLLIN;
        pollfd[i].revents = 0;
    }

    if ((listenfd = serv_listen(CS_OPEN)) < 0) {
        printf("serv_listen error");
    }
    client_add(listenfd, 0);
    pollfd[0].fd = listenfd;

    for (;;) {
        if (poll(pollfd, numfd, -1) < 0) { //阻塞直到某个描述符可进行非阻塞读取
            printf("poll error");
        }

        if (pollfd[0].revents & POLLIN) { //判断是否有新接入的连接
            if ((clifd = serv_accept(listenfd, &uid)) < 0) {
                printf("serv_accept error: %d", clifd);
            }
            client_add(clifd, uid);

            if (numfd == maxfd) //如果pollfd空间已满，则重分配一个更大的空间
                pollfd = grow_pollfd(pollfd, &maxfd);
            pollfd[numfd].fd = clifd;
            pollfd[numfd].events = POLLIN;
            pollfd[numfd].revents = 0;
            numfd++;
            printf("new connection: uid %d, fd %d\n", uid, clifd);
        }

        for (i = 1; i < numfd; ++i) { //判断是哪个描述符可进行非阻塞读取
            if (pollfd[i].revents & POLLHUP) { //对方已挂断
                goto hangup;
            } else if (pollfd[i].revents & POLLIN) { //如果接收到了数据
                if ((nread = read(pollfd[i].fd, buf, MAXLINE)) < 0) { //读取失败
                    printf("read error on fd %d\n", pollfd[i].fd);
                } else if (nread == 0) { //对端已关闭
hangup:
                    printf("closed: uid %d, fd %d\n", client[i].uid, pollfd[i].fd);
                    client_del(pollfd[i].fd);
                    close(pollfd[i].fd);
                    if (i < numfd - 1) { //如果删除的不是最后一个pollfd里最后一个fd，那么将最后一个polled数组的最后一个元素填充到此fd所占的内存处
                        pollfd[i].fd = pollfd[numfd - 1].fd;
                        pollfd[i].events = pollfd[numfd - 1].events;
                        pollfd[i].revents = pollfd[numfd - 1].revents;
                        i--; //下次会检查这个被移动的最后一个节点
                    }
                    numfd--; //数组有效元素个数减一
                } else { //正常读取到请求
                    handle_request(buf, nread, pollfd[i].fd);
                }
            }
        }
    }
}

void loop_select(void)
{
    int i, n, maxfd, maxi, listened, clifd, nread;
    char buf[MAXLINE];
    uid_t uid;
    fd_set rset, allset;

    FD_ZERO(&allset);
    if ((listened = serv_listen(CS_OPEN)) < 0) {
        printf("serv_listen error\n");
        return;
    }
    FD_SET(listened, &allset);
    maxfd = listened;
    maxi = -1;
    for (;;) {
        rset = allset;
        if ((n = select(maxfd + 1, &rset, NULL, NULL ,NULL)) < 0) { //这里有可能是接受到了新的连接请求，也有可能是已建立的连接收到了消息
            printf("select error\n");
        }

        if (FD_ISSET(listened, &rset)) { //如果收到消息的是监听描述符
            if ((clifd = serv_accept(listened, &uid)) < 0) { //与这个新的请求建立连接
                printf("serv_accept error\n");
            }
            i = client_add(clifd, uid); //保存另一端的信息
            FD_SET(clifd, &allset); //将新建立连接的描述符加入到select的监听集合中
            if (clifd > maxfd)
                maxfd = clifd; //如果新建立的描述符是当前最大的一个描述符整数，将其赋值给maxfd以便select对其进行监控
            if (i > maxi)
                maxi = i; //client结构体最大下标
            printf("new connection: uid %d, fd %d\n", uid, clifd);
            continue;
        }

        for (i = 0; i <= maxi; ++i) { //如果是某个其它的描述符有消息可读
            if ((clifd = client[i].fd) < 0) //查找当前有效的unix域套接字描述符
                continue;

            if (FD_ISSET(clifd, &rset)) { //判断是哪一个有效的描述符中有可读数据
                if ((nread = read(clifd, buf, MAXLINE)) < 0) { //读取失败
                    printf("read error");
                } else if (nread == 0){
                    printf("closed: uid %d, fd %d\n", client[i].uid, clifd); //如果连接断开
                    client_del(clifd);
                    FD_CLR(clifd, &allset);
                    close(clifd);
                } else { //收到请求
                    handle_request(buf, nread, clifd);
                }
            }
        }
    }
}

void client_del(int fd)
{
    int i;

    for (i = 0; i < client_size; ++i) {
        if (client[i].fd == fd) {
            client[i].fd = -1;
            return;
        }
    }
    printf("cant find the client entry for fd %d\n", fd);
}

int client_add(int fd, uid_t uid)
{
    int i;

    if (client == NULL)
        client_alloc();
again:
    for (i = 0; i < client_size; ++i) {
        if (client[i].fd == -1) {
            client[i].fd = fd;
            client[i].uid = uid;
            return i;
        }
    }

    client_alloc();
    goto again;
}

static void client_alloc(void)
{
    int i;

    if (client == NULL)
        client = malloc(NALLOC * sizeof(Client));
    else
        client = realloc(client, (client_size + NALLOC) * sizeof(Client));

    if (client == NULL) {
        printf("alloc error");
        return;
    }

    for (i = client_size; i < client_size + NALLOC; ++i) {
        client[i].fd = -1;
    }
    client_size += NALLOC;
}

void handle_request(char * buf, int nread, int fd)
{
    int newfd;
    if (buf[nread - 1] != 0) {
        snprintf(errmsg, MAXLINE -1, "request not null terminated: %*.*s\n", nread, nread, buf);
        send_err(fd, -1, errmsg);
        return;
    }
    if (buf_args(buf, cli_args) < 0) { //分解请求信息
        send_err(fd, -1, errmsg);
        return;
    }

    if ((newfd = open(pathname, flag)) < 0) { //打开父进程请求的文件
        snprintf(errmsg, MAXLINE - 1, "cant open %s: %s\n", pathname, strerror(errno));
        send_err(fd, -1, errmsg);
        return;
    }

    if (send_fd(fd, newfd) < 0) { //发送文件描述符权限
        printf("send_fd error");
        exit(-1);
    }
    close(newfd);
}

int buf_args(char * buf, int (*optfunc)(int, char **))
{
    char * ptr, *argv[5];
    int argc;

    if (strtok(buf, WHITE) == NULL) //strtok的第一个参数不能分配在静态文本区，第一次调用之后，返回值将会指向被分割后的第一个数据的指针
        return -1;
    argv[argc = 0] = buf;
    while ((ptr = strtok(NULL, WHITE)) != NULL) { //返回指向下一个数据的指针
        if (++argc >= 5)
            return -1;
        argv[argc] = ptr;
    }
    argv[++argc] = NULL;

    return optfunc(argc, argv);
}

int cli_args(int argc, char ** argv)
{
    if (argc != 3 || strcmp(argv[0], CL_OPEN) != 0) {
        strcmp(errmsg, "usage: <pathname> <flag>");
        return -1;
    }
    pathname = argv[1];
    flag = atoi(argv[2]);
    return 0;
}
