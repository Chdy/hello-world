//
// Created by 邓岩 on 15/07/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

# define CLIENT_FIFO_TEMPLATE "/Users/dengyan/clientfifo.%d"
# define CLIENT_NAME_LEN sizeof(CLIENT_FIFO_TEMPLATE)+20
//该程序为客户端程序，向服务器请求获取一个唯一的序列号

struct request
{
    int pid;
    int rstlen;
};

struct response
{
    int resnum;
};

int main(int argc,char ** argv)
{
    struct request req;
    struct response res;
    int writrfd,readfd;
    req.pid = getpid();
    req.rstlen = atoi(argv[1]);
    char clientfifo[CLIENT_NAME_LEN];
    snprintf(clientfifo,CLIENT_NAME_LEN,CLIENT_FIFO_TEMPLATE,getpid());
    if(mkfifo(clientfifo,0711)==EOF)
    {
        printf("error on creating fifo\n");
        exit(-1);
    }
    writrfd = open("/Users/dengyan/serverfifo",O_WRONLY);//打开服务器管道的写端
    if(write(writrfd,&req, sizeof(struct request))!= sizeof(struct request))//向服务器发送请求
    {
        printf("error on writing date to server\n");
        exit(-1);
    }
    readfd = open(clientfifo,O_RDONLY);//打开服务器管道的读取端
    if(read(readfd,&res, sizeof(struct response))!= sizeof(struct response))//接受服务器响应的信息
    {
        printf("error on reading date fromserver\n");
        exit(-1);
    }
    close(writrfd);
    close(readfd);
    printf("get the num is %d",res.resnum);
    unlink(clientfifo);
}