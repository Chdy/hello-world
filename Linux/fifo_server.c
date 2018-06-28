//
// Created by 邓岩 on 15/07/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

# define CLIENT_FIFO_TEMPLATE "/Users/dengyan/clientfifo.%d"
# define CLIENT_NAME_LEN sizeof(CLIENT_FIFO_TEMPLATE)+20
//接受从客户端发送过来的消息，并进行处理，由于对单个请求处理速度很快，此程序不需要并发设计

struct request
{
    int pid;
    int rstlen;
};

struct response
{
    int resnum;
};

int main(void)
{
    struct request req;
    struct response res;
    int serverfd,dummyfd,writefd;
    int num = 0;
    char clientfifo[CLIENT_NAME_LEN];
    umask(0);
    if((mkfifo("/Users/dengyan/serverfifo",0711)==-1)&&errno!=EEXIST)
    {
        printf("error on make fifo\n");
        exit(-1);
    }
    int i;
    serverfd = open("/Users/dengyan/serverfifo",O_RDONLY);//打开服务器管道的读取端，此处会阻塞，直到有客户端打开了该管道的写端
    dummyfd = open("/Users/dengyan/serverfifo",O_WRONLY);//打开服务器管道的写端，自身打开写端是因为如果客户端的写端如果全部关闭，39行的read函数会直接返回0而不是阻塞
    for (;;) {
        if((i = read(serverfd,&req, sizeof(struct request)))!= sizeof(struct request))//读取客户端的请求
        {
            printf("server error on read %d\n",i);
            exit(-1);
        }
        printf("receive the request from process %d\n",req.pid);
        snprintf(clientfifo,CLIENT_NAME_LEN,CLIENT_FIFO_TEMPLATE,req.pid);
        if((writefd = open(clientfifo,O_WRONLY))==EOF)
            continue;
        res.resnum = num;
        if(write(writefd,&res, sizeof(struct response))!= sizeof(struct response))//向客户端进行响应
        {
            printf("server error on write\n");
            exit(-1);
        }
        close(writefd);
        num+=req.rstlen;
    }
}