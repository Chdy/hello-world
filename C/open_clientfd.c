//
// Created by Vain loser on 27/11/2016.
//

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <string.h>
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
 * struct sockaddr {
 *      unsigned short sa_family;
 *      char sa_data[14];
 *};
 * struct sockaddr_in {
 *      unsigned short sin_family;
 *      unsigned short sin_port;
 *      struct in_addr sin_addr;
 *      unsigned char sin_zero[8];
 * };
 * int clientfd = socket(AF_INET,SOCK_STREAM,0);//AF_INET表明正在使用因特网，SOCK_STREAM表示这个套接字是因特网连接的一个端点
 * int connext(int sockfd,struct sockaddr * serv_addr,int addrlen);
 * 目的服务器端处于局域网时，不能使用gethostbyaddr和gethostbyname
 */
int open_clientfd(char * hostname,int port);

int main(int argc,char **argv)
{
    int clientfd,port;
    char * host,buf[100];
    rio_t rio;
    host = argv[1];
    port = atoi(argv[2]);
    clientfd = open_clientfd(host,port);
    rio_readinitb(&rio,clientfd);
    while(fgets(buf,100,stdin))
    {
        rio_writen(clientfd,buf,strlen(buf));
        rio_readlineb(&rio,buf,100);
        fputs(buf,stdout);
    }
    close(clientfd);
    exit(0);
}

int open_clientfd(char * hostname,int port)
{
    int clientfd;
    struct hostent * hp;
    struct in_addr addr;
    struct sockaddr_in server_addr;
    if((clientfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
        return -1;
    //printf("OK");
    bzero((char *)&server_addr,sizeof(server_addr));
    if(inet_aton(hostname,&addr)!=0)  //目的服务器端处于局域网时，不能使用gethostbyaddr和gethostbyname
    {
        server_addr.sin_addr.s_addr = addr.s_addr;
    }
    else
    {
        hp = gethostbyname(hostname);
        bcopy(hp->h_addr_list[0], &server_addr.sin_addr.s_addr, hp->h_length);
    }
    server_addr.sin_family = AF_INET;
    //bcopy(hp->h_addr_list[0],&server_addr.sin_addr.s_addr, hp->h_length);
    server_addr.sin_port = htons(port);
    if(connect(clientfd,(struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        return -1;
    return clientfd;
}