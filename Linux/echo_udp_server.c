//
// Created by 邓岩 on 19/09/2017.
//
//echo迭代服务器，返回从客户端接受的信息，必须为特权进程，因为使用了7(echo)端口号

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(int argc,char ** argv)
{
    char buf[100];
    int sockfd,len,i;
    struct sockaddr_storage claddr;
    struct addrinfo hints,* results, * p;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE|AI_ADDRCONFIG;
    int n = getaddrinfo(NULL,"echo",&hints,&results);
    for (p = results; p->ai_next!=NULL;p = p->ai_next ) {
        sockfd = socket(p->ai_family,SOCK_DGRAM,0);
        if(sockfd == -1)
            exit(-1);
        if(bind(sockfd,p->ai_addr,p->ai_addrlen) == -1)
            continue;
        freeaddrinfo(results);
    }
    for (;;) {
        len = sizeof(struct sockaddr_storage);
        i = recvfrom(sockfd,buf,100,0,(struct sockaddr *)&claddr,&len);
        sendto(sockfd,buf,i,0,(struct sockaddr *)&claddr,len);
    }
}