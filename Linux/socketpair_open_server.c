//
// Created by 邓岩 on 2018/10/25.
//
// 关联open_client程序
// 该程序只需要生成名为opend的可执行文件即可，由open_client生成子进程调用

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include "send_fd.h"

#define CL_OPEN "open"
#define MAXLINE 100
#define WHITE " \n\t"

char errmsg[MAXLINE];
int flag;
char * pathname;

int cli_args(int, char **);
void handle_request(char *, int, int);
int buf_args(char * buf, int (*optfunc)(int, char **));

int main(int argc, char ** args)
{
    int nread;
    char buf[MAXLINE];

    for (;;) {
        if ((nread = read(STDIN_FILENO, buf, MAXLINE)) < 0) { //读取父进程的请求
            printf("read error");
            return -1;
        } else if (nread == 0)
            break; //客户端关闭了另外一端
        handle_request(buf, nread, STDOUT_FILENO); //处理请求
    }
    exit(0);
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
