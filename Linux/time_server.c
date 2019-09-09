//
// Created by 邓岩 on 2018/12/18.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(int argc, char *argv[]) {
    int sockfd, n, fd;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        exit(-1);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_port = htons(13333);
    servaddr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0)
        exit(-1);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        exit(-1);
    }

    listen(sockfd, 5);

    while (1) {
        if ((fd = accept(sockfd, NULL, NULL)) < 0) {
            printf("%s", strerror(errno));
            continue;
        }
        time_t t = time(NULL);
        char * str = ctime(&t);
        write(fd, str, strlen(str));
        close(fd);
    }

}

//带超时处理的客户端

/*
 * void alarm_handler(int a)
{
    return;
}
 * int main(int argc, char *argv[]) {
    int sockfd, n;
    char buf[4097];
    struct sockaddr_in servaddr;
    struct sockaddr_in6 a;
    void (*sigfunc)(int a);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13333);
    if (inet_pton(AF_INET, "132.232.100.170", &servaddr.sin_addr) == -1)
        err_quit("inet_pton error");

    sigfunc = signal(SIGALRM, alarm_handler);
    alarm(10);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        if (errno == EINTR)
            errno = ETIMEDOUT;
        err_sys("connect error");
    }
    alarm(0);
    signal(SIGALRM, sigfunc);

    while ((n = read(sockfd, buf, 4096)) > 0) {
        write(STDOUT_FILENO, buf, n);
    }
    close(sockfd);
}
 */