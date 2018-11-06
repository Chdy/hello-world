//
// Created by 邓岩 on 2018/10/25.
//
// 生成一个专门用于打开文件的子进程，子进程打开文件后，通过unix域套接字将文件描述符传送到父进程，然后父进程再通过文件描述符读取文件内容
// 这样做可以制造一个专门用于打开文件的进程，它拥有着更高的权限，或者它是设置了set-user-id位的进程，这样子进程能通过它打开原本需要更高权限的文件
// 不过在这个例子中使用是使用socketpair生成的域套接字，因此文件描述符只能在有关系的进程中传递

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include "send_fd.h"
#define CL_OPEN "open"
#define BUFFSIZE 8192
#define MAXLINE 100

int csopen(char *, int);

int main(int agrc, char ** agrs)
{
    setbuf(stdout, NULL);
    int n, fd;
    char buf[BUFFSIZE];
    char line[MAXLINE];

    while (fgets(line, MAXLINE, stdin) != NULL) { //读取想要打开的文件
        if (line[strlen(line) - 1] == '\n') //将换行符换为字符串结束符
            line[strlen(line) - 1] = 0;
        if ((fd = csopen(line, O_RDONLY)) < 0) //通过子进程来获取文件描述符
            continue;
        while ((n = read(fd, buf, BUFFSIZE)) > 0) //读取文件内容
            if (write(STDOUT_FILENO, buf, n) != n) {
                printf("write error");
                return -1;
            }

        if (n < 0) {
            printf("read error");
            return -1;
        }
        close(fd);
    }
    return 0;
}

int csopen(char * name, int flag)
{
    pid_t pid;
    int len;
    char buf[10];
    struct iovec iov[3];
    static int fd[2] = {-1, -1};

    if (fd[0] < 0) {
        if (socketpair(AF_UNIX, SOCK_DGRAM, 0, fd) < 0) { //生成unix域套接字对
            printf("socketpair error");
            return -1;
        }

        if ((pid = fork()) < 0) { //生成子进程
            printf("fork error");
            return -1;
        } else if (pid == 0) { //子进程
            close(fd[0]);
            if (fd[1] != STDIN_FILENO && dup2(fd[1],STDIN_FILENO) != STDIN_FILENO) { //将unix域套接字重定向到标准输入
                printf("dup2 error");
                return -1;
            }

            if (fd[1] != STDOUT_FILENO && dup2(fd[1],STDOUT_FILENO) != STDOUT_FILENO) { //将unix域套接字重定向到标准输出
                printf("dup2 error");
                return -1;
            }

            if (execlp("/Users/dengyan/ClionProjects/Linux/opend", "opend", (char *)0) < 0) { //子进程调用opend程序
                printf("execl error");
                return -1;
            }
            printf("%s", strerror(errno));
        }
        close(fd[1]);
    }
    sprintf(buf, " %d", flag);
    iov[0].iov_base = CL_OPEN " "; //字符串连接
    iov[0].iov_len = strlen(CL_OPEN) + 1;
    iov[1].iov_base = name; //想打开的文件名
    iov[1].iov_len = strlen(name);
    iov[2].iov_base = buf; //打开的标志
    iov[2].iov_len = strlen(buf) + 1;
    len = iov[0].iov_len + iov[1].iov_len + iov[2].iov_len;
    if (writev(fd[0], iov, 3) != len) { //聚集写
        printf("write error");
        return -1;
    }
    return recv_fd(fd[0], write);
}