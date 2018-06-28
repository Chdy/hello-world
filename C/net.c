//
// Created by Vain loser on 03/12/2016.
//

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# define RIO_BUFSIZE 8192
typedef struct
{
    int rio_fd;
    int rio_cnt;//缓冲区未被读取区域大小
    char * rio_bufptr;//缓冲区有效区头地址
    char rio_buf[RIO_BUFSIZE];//缓冲区域
}rio_t;
int open_listenfd(int port);
ssize_t rio_readn(int fd,void * usrbuf,size_t n);
ssize_t rio_writen(int fd,void * usrbuf,size_t n);
void rio_readinitb(rio_t * rp,int fd);
static ssize_t rio_read(rio_t * rp,char * usrbuf,size_t n);
ssize_t rio_readlineb(rio_t * rp,void * usrbuf,size_t n);
ssize_t rio_readnb(rio_t * rp,void * usrbuf,size_t n);
ssize_t rio_readlineb(rio_t * rp,void * usrbuf,size_t n);

ssize_t rio_readlineb(rio_t * rp,void * usrbuf,size_t n)//每次最多读取n-1个,如果每次没写满遇到回车符，则返回值表示读取字符串的大小
{                                                      //包括'\n'，但是不包括0，如果写满的话，则最后包括0的大小
    int i,rc;
    char c,* bufp = usrbuf;
    for(i=1;i<n;i++)
    {
        if((rc = rio_read(rp,&c,1)) == 1)
        {
            *bufp++ = c;
            if(c == '\n')
                break;
        }
        else if(rc == 0)
        {
            if(i == 1)
                return 0;
            else
                break;
        }
        else
            return -1;
    }
    *bufp = 0;
    if(i == n | c!='\n')//情况一：如果读满,则减一，防止写入0；情况二：如果没写满，但是没有回车符，即最后一次处理时，减一，防止写入0;
        return i - 1;
    return i;
}

ssize_t rio_readnb(rio_t * rp,void * usrbuf,size_t n)//带缓冲的read函数，被中断后能自动重启
{
    size_t nleft = n;
    ssize_t nread;
    char * bufp = usrbuf;
    while(nleft > 0)
    {
        if((nread = rio_read(rp,bufp,nleft))<0)//此处调用带缓存的read函数
        {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

static ssize_t rio_read(rio_t * rp,char * usrbuf,size_t n)
{
    int cnt;
    while(rp->rio_cnt <= 0)//说明缓冲区为空,如果不为空则直接从缓冲区读取数据，无需再次调用read函数
    {
        rp->rio_cnt = read(rp->rio_fd,rp->rio_buf,sizeof(rp->rio_buf));//装填缓冲区，非常大
        if(rp->rio_cnt < 0)
        {
            if(errno!=EINTR)
                return -1;
        }
        else if(rp->rio_cnt == 0)
            return 0;
        else
            rp->rio_bufptr = rp->rio_buf;//因为重新装填所以重新指向缓冲区开头
    }
    cnt = n;
    if(rp->rio_cnt < n)
        cnt = rp->rio_cnt;
    memcpy(usrbuf,rp->rio_bufptr,cnt);
    rp->rio_cnt -= cnt;//将缓冲区大小减去被读取部分的大小
    rp->rio_bufptr += cnt;//将缓冲区有效区头指针向后移动
    return cnt;
}

void rio_readinitb(rio_t * rp,int fd)//将描述符与缓冲区绑定
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

ssize_t rio_readn(int fd,void * usrbuf,size_t n)//无缓冲的read函数，被中断后能自动重启
{
    size_t nleft = n;
    ssize_t nread;
    char * bufp = usrbuf;
    while(nleft > 0)
    {
        if((nread = read(fd,bufp,nleft)<0))
        {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

ssize_t rio_writen(int fd,void * usrbuf,size_t n)//无缓冲的wirte函数，被中断后能自动重启
{
    size_t nleft = n;
    ssize_t nwrite;
    char * bufp = usrbuf;
    while(nleft > 0)
    {
        if((nwrite = write(fd,bufp,nleft)) <= 0)
        {
            if(errno == EINTR)
                nwrite = 0;
            else
                return -1;
        }
        nleft -= nwrite;
        bufp += nwrite;
    }
    return 0;
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