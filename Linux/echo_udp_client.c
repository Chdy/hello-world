//
// Created by 邓岩 on 19/09/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(void)
{
    char buf[100];
    int sockfd,i;
    struct addrinfo hints,* result,* p;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = 0;
    hints.ai_family = AF_UNSPEC;
    getaddrinfo("localhost","echo",&hints,&result);
    for (p = result; p->ai_next != NULL ; p = p->ai_next) {
        sockfd = socket(p->ai_family,SOCK_DGRAM,0);
        if(sockfd == -1)
            exit(-1);
        if(connect(sockfd,p->ai_addr,p->ai_addrlen) == -1)
            continue;
        freeaddrinfo(result);
    }
    for (;;) {
        i = read(STDIN_FILENO,buf,100);
        write(sockfd,buf,i);
        i = read(sockfd,buf,100);
        write(STDOUT_FILENO,buf,i);
    }
}