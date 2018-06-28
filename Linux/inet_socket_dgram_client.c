//
// Created by 邓岩 on 13/09/2017.
//
//用IPv6进行数据报数据传输

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(void)
{
    int i;
    char buf[100];
    struct sockaddr_in6 server;
    int sockfd = socket(AF_INET6,SOCK_DGRAM,0);
    server.sin6_port = htons(50000);
    server.sin6_family = AF_INET6;
    server.sin6_addr = inet_ntop(AF_INET6,"60.205.186.23",&server.sin6_addr);//in6addr_loopback;
    for (;;) {
        i = read(STDIN_FILENO,buf,100);
        sendto(sockfd,buf,i,0,(struct sockaddr *)&server,sizeof(struct sockaddr_in6));
        i = recvfrom(sockfd,buf,100,0,NULL,NULL);
        write(STDOUT_FILENO,buf,i);
    }
    return 0;
}