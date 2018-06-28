//
// Created by 邓岩 on 16/09/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(int argc,char ** argv)
{
    setbuf(stdout,NULL);
    char buf[100];
    char resbuf[10];
    int seqnum = 1;
    int sockfd,fd,len,reqlen;
    struct addrinfo hints,*result,*p;
    struct sockaddr_storage claddr;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_NUMERICSERV|AI_PASSIVE|AI_ADDRCONFIG;
    if(getaddrinfo(NULL,"50000",&hints,&result)!=0)
        exit(-1);
    for (p = result; p->ai_next != NULL ; p = p->ai_next) {
        sockfd = socket(p->ai_family,SOCK_STREAM,0);
        if(sockfd == -1)
            continue;
        if(bind(sockfd,p->ai_addr,p->ai_addrlen) == 0)
            break;
        close(sockfd);
    }
    listen(sockfd,5);
    for (;;)
    {
        len = sizeof(struct sockaddr_storage);
        if((fd = accept(sockfd,(struct sockaddr *)&claddr,&len))==-1)
            continue;
        if(claddr.ss_family == AF_INET)
            printf("Linking... IP %s\n",inet_ntop(AF_INET,&(((struct sockaddr_in *)&claddr)->sin_addr.s_addr),buf,100));
        else
            printf("Linking... IP %s\n",inet_ntop(AF_INET6,&(((struct sockaddr_in6 *)&claddr)->sin6_addr.__u6_addr),buf,100));
        len = read(fd,buf,10);
        buf[len] = 0;
        reqlen = atoi(buf);
        snprintf(resbuf,10,"%d\n",seqnum);
        write(fd,resbuf,strlen(resbuf));
        seqnum += reqlen;
        close(fd);
    }
}