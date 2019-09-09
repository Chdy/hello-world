//
// Created by 邓岩 on 2018/12/18.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include "daemon.c"

#define SOCK_PATH "/Users/dengyan/"

void handler(int s)
{
    pid_t pid;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
        printf("child pid %d terminate ", pid);
}

struct addrinfo * host_serv(const char * host, const char * serv, int family, int socktype);
int tcp_connect(const char * host, const char * serv);
int tcp_listen(const char * host, const char * serv, socklen_t * addrlenp);

#define	CMGROUP_MAX 16

struct cmsgcred {
    pid_t	cmcred_pid;		/* PID of sending process */
    uid_t	cmcred_uid;		/* real UID of sending process */
    uid_t	cmcred_euid;		/* effective UID of sending process */
    gid_t	cmcred_gid;		/* real GID of sending process */
    short	cmcred_ngroups;		/* number or groups */
    gid_t	cmcred_groups[CMGROUP_MAX];	/* groups */
};

//Todo:--------------------------------------------------------------------------main---------------------------------------------------------------------
int main(int argc, char *argv[]) {
    int fd;
    char buf[100];
    struct sockaddr_un un, addr;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    struct  arpreq re;


    return 0;
}
//Todo:--------------------------------------------------------------------------main---------------------------------------------------------------------

struct addrinfo * host_serv(const char * host, const char * serv, int family, int socktype)
{
    struct addrinfo hints, *res;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_CANONNAME;
    hints.ai_family = family;
    hints.ai_socktype = socktype;

    if (getaddrinfo(host, serv, &hints, &res) != 0)
        return  NULL;
    return res;
}

int tcp_connect(const char * host, const char * serv)
{
    int sockfd, n;
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;

    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
        err_quit("tcp_connect error for %s, %s:%s", host, serv, gai_strerror(n));

    ressave = res;
    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0)
            continue;

        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
            break;

        close(sockfd);
    } while ((res = res->ai_next) != NULL);

    if (res == NULL)
        err_quit("tcp_connect error for %s, %s", host, serv);

    freeaddrinfo(ressave);

    return sockfd;
}

int tcp_listen(const char * host, const char * serv, socklen_t * addrlenp)
{
    int listenfd, n;
    const int on = 1;
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;

    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
        err_quit("tcp_listen error for %s, %s:%s", host, serv, gai_strerror(n));

    ressave = res;

    do {
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0)
            continue;

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;

        close(listenfd);
    } while ((res = res->ai_next) != NULL);

    listen(listenfd, 5);
    if (addrlenp)
        *addrlenp = res->ai_addrlen;
    
    freeaddrinfo(ressave);

    return listenfd;
}

int udp_client(const char * host, const char * serv, struct sockaddr ** saptr, socklen_t * lenp)
{
    int sockfd, n;
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_NUMERICSERV;

    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
        err_quit("udp_client error for %s, %s:%s", host, serv, gai_strerror(n));

    ressave = res;
    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd > 0)
            break;
    } while ((res = res->ai_next) != NULL);

    if (res == NULL)
        err_quit("udp_client error for %s, %s", host, serv);

    *saptr = malloc(res->ai_addrlen);
    memcpy(*saptr, res->ai_addr, res->ai_addrlen);
    *lenp = res->ai_addrlen;
    
    freeaddrinfo(ressave);

    return sockfd;
}


int udp_connect(const char * host, const char * serv)
{
    int sockfd, n;
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_NUMERICSERV;

    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
        err_quit("udp_client error for %s, %s:%s", host, serv, gai_strerror(n));

    ressave = res;
    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd > 0)
            continue;
        
        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
            break;
        
        close(sockfd);
    } while ((res = res->ai_next) != NULL);

    if (res == NULL)
        err_quit("udp_client error for %s, %s", host, serv);

    freeaddrinfo(ressave);

    return sockfd;
}

int udp_server(const char * host, const char * serv, socklen_t * addrlenp)
{
    int sockfd, n;
    const int on = 1;
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_NUMERICSERV;

    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
        err_quit("tcp_listen error for %s, %s:%s", host, serv, gai_strerror(n));

    ressave = res;

    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0)
            continue;

        if (bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
            break;

        close(sockfd);
    } while ((res = res->ai_next) != NULL);

    if (res == NULL)
        err_quit("tcp_connect error for %s, %s", host, serv);

    if (addrlenp)
        *addrlenp = res->ai_addrlen;

    return sockfd;
}