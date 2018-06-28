//
// Created by Vain loser on 28/11/2016.
//

# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <string.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <unistd.h>

# define RIO_BUFSIZE 8192
typedef struct
{
    int rio_fd;
    int rio_cnt;//缓冲区未被读取区域大小
    char * rio_bufptr;//缓冲区有效区头地址
    char rio_buf[RIO_BUFSIZE];//缓冲区域
}rio_t;

/*
 *int bind(int sockfd,struct sockaddr * my_addr,int addrlen);
 *int listen(int sockfd,int backlog);
 */
int open_listenfd(int port);
void echo(int coonfd);

int main(int argc,char ** argv)
{
    int i = 1;
    int listenfd,connfd,port;
    socklen_t clientlen;
    struct sockaddr_in clientaddr;
    struct hostent * hp;
    char * haddrp;
    port = atoi(argv[1]);
    listenfd = open_listenfd(port);
    while(1)
    {
        printf("Linking...\n");
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd,(struct sockaddr *)&clientaddr,&clientlen);
        printf("Link,OK\n");
        if(!(hp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr),AF_INET)))
            //目的服务器端处于局域网时，不能使用gethostbyaddr和gethostbyname
            printf("server connected to LAN\n");
        else
        {
            haddrp = inet_ntoa(clientaddr.sin_addr);
            printf("server connected to %s (%s)\n", hp->h_name, haddrp);
        }
        echo(connfd);
        close(connfd);
    }
    exit(0);
}

int open_listenfd(int port)
{
    int listenfd,optval = 1;
    struct sockaddr_in server_addr;
    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
        return -1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const char *)&optval, sizeof(int)) < 0)
        return -1;
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons((unsigned short)port);
    if(bind(listenfd,(struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        return -1;
    if(listen(listenfd,5) < 0)
        return -1;
    return listenfd;
}

void echo(int connfd)
{
    size_t n;
    char buf[100];
    rio_t rio;
    rio_readinitb(&rio,connfd);
    while((n = rio_readlineb(&rio,buf,100))!=0)
    {
        printf("server receive %d bytes：",n-1);
        printf("%s",buf);
        rio_writen(connfd,buf,n);
    }
    printf("Link is interrupted\n");
}