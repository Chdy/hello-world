//
// Created by 邓岩 on 2018/12/20.
//

/*
 * 带信号处理程序的echo服务器
 */

# include </Users/dengyan/ClionProjects/Linux/linux.h>

void handler(int s)
{
    pid_t pid;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
        printf("child pid %d terminated\n", pid);
}

int main(int argc, char ** argv) {
    setbuf(stdout, NULL);
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    signal(SIGCHLD, handler);

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_quit("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(23333);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) == -1)
        err_quit("bind error");

    if ((listen(listenfd, 5)) < 0)
        err_quit("listen error");

    for ( ; ; ) {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr)) < 0)
            err_sys("accept error");

        if (fork() == 0) {
            close(listenfd);
            int n;
            char buf[4096];
            while ((n = read(connfd, buf, 4096)) > 0) {
                write(connfd, buf, n);
            }
            exit(0);
        }
        close(connfd);
    }

}

/*
 *     int fd;
    char buf[100];
    struct sockaddr_in servaddr;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(23333);

    if (connect(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    for ( ; ; ) {
        int n = read(STDIN_FILENO, buf, 100);
        write(fd, buf, n);
        n = read(fd, buf, 100);
        write(STDOUT_FILENO, buf, n);
    }
    return 0;
 */