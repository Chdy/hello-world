//
// Created by 邓岩 on 2018/10/25.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include "send_fd.h"
# include "unix_socket_api.h"

#define CS_OPEN "/Users/dengyan/serve"
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

    printf("ftp:");
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
        printf("\nftp:");

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
    int len;
    char buf[12];
    struct iovec iov[3];
    static int fd = -1;

    if (fd < 0) {
        if ((fd = cli_conn(CS_OPEN)) < 0) { //生成unix域套接字对
            printf("cli_conn error");
            return -1;
        }
    }
    sprintf(buf, " %d", flag);
    iov[0].iov_base = CL_OPEN " "; //字符串连接
    iov[0].iov_len = strlen(CL_OPEN) + 1;
    iov[1].iov_base = name; //想打开的文件名
    iov[1].iov_len = strlen(name);
    iov[2].iov_base = buf; //打开的标志
    iov[2].iov_len = strlen(buf) + 1;
    len = iov[0].iov_len + iov[1].iov_len + iov[2].iov_len;
    if (writev(fd, iov, 3) != len) { //聚集写
        printf("write error");
        return -1;
    }
    return recv_fd(fd, write);
}
