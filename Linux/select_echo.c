//
// Created by 邓岩 on 2018/12/22.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

void handler(int s)
{
    pid_t pid;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
        printf("child pid %d terminate ", pid);
}

int main(int argc, char *argv[]) {
    int listenfd, clifd, udpfd, n;
    socklen_t len;
    int on = 1, maxfd = -1;
    struct sockaddr_in servaddr, cliaddr;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_quit("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(23333);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    signal(SIGCHLD, handler);

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
        err_quit("setsockopt error");

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        err_quit("bind error");

    listen(listenfd, 5);

    if ((udpfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        err_quit("udp socket error");

    if (bind(udpfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        err_quit("bind error");

    maxfd = listenfd > udpfd?listenfd:udpfd;
    fd_set set;
    FD_ZERO(&set);

    for ( ;; ) {
        FD_SET(listenfd, &set);
        FD_SET(udpfd, &set);

        if (select(maxfd + 1, &set, NULL, NULL, NULL) < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("select error");
        }

        if (FD_ISSET(listenfd, &set)) {
            char name[40];
            len = sizeof(cliaddr);
            clifd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
            printf("connect from %s:%d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, name, sizeof(name)), ntohs(cliaddr.sin_port));
            fflush(stdout);

            if (fork() == 0) {
                char buf[4096];
                close(listenfd);
                while ((n = read(clifd, buf, sizeof(buf))) > 0) {
                    write(clifd, buf, n);
                }
                exit(-1);
            }
            close(clifd);
        }

        if (FD_ISSET(udpfd, &set)) {
            char buf[4096];
            len = sizeof(cliaddr);
            n = recvfrom(udpfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &len);
            sendto(udpfd, buf, n, 0, (struct sockaddr *)&cliaddr, len);
        }
    }
}

/*
 *
 * int main(int argc, char *argv[]) {
    char buf[4096];
    int tcpfd, udpfd, len, choose, n;
    struct sockaddr_in servaddr, cliaddr;

    if ((tcpfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("tcp socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(23333);
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if ((udpfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        err_sys("udp socket error");

    if (connect(tcpfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");


    connect(udpfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    for (;;) {
        printf("1: TCP echo\n");
        printf("2: UDP echo\n");

        scanf("%d", &choose);
        switch (choose) {
            case 1:
                n = read(STDIN_FILENO, buf, 4096);
                write(tcpfd, buf, n);
                n = read(tcpfd, buf, n);
                write(STDOUT_FILENO, buf, n);
                break;
            case 2:
                n = read(STDIN_FILENO, buf, 4096);
                write(udpfd, buf, n);
                n = read(udpfd, buf, n);
                write(STDOUT_FILENO, buf, n);
                break;
            default:
                break;
        }
    }

    return 0;
  }
 */