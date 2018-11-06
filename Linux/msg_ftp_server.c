//
// Created by 邓岩 on 26/07/2017.
//

//ftp服务器端

# include </Users/dengyan/ClionProjects/Linux/linux.h>

# define RESP_FAILURE 1
# define RESP_DATA 2
# define RESP_END 3

int server_key = 0xaaaaa;

struct responseMsg
{
    long type;
    char data[2048];//经实验，mac上的信号队列的容量是2048个字节，long为八个字节
};

struct requestMsg
{
    long type;
    int clientId;
    char filepath[100];
};

void sig_handler(int sig)
{
    while(waitpid(-1,NULL,WNOHANG)>0)
        continue;
}

void requestHanle(struct requestMsg * req)
{
    int fd;
    int num;
    struct responseMsg res;
    if((fd = open(req->filepath,O_RDONLY))==EOF)//如果无法打开文件
    {
        res.type = RESP_FAILURE;//该type类型标记为失败
        snprintf(res.data,2040,"%s","Can't open\n");
        msgsnd(req->clientId,&res, strlen(res.data),0);//发送失败信息给客户端
        exit(EXIT_FAILURE);
    }
    res.type = RESP_DATA;
    while((num = read(fd,res.data,2040))>0)//读取客户端请求文件的内容
    {
        msgsnd(req->clientId,&res,num,0);//将文件内容发送给客户端
    }
    res.type = RESP_END;
    msgsnd(req->clientId,res.data,0,0);
}

int main(void)
{
    int server;
    struct sigvec sigv;
    struct requestMsg req;
    sigv.sv_handler = sig_handler;
    sigv.sv_flags = 0;
    sigv.sv_mask = 0;
    sigvec(SIGCHLD,&sigv,NULL);//设置信号处理函数，回收子进程
    server = msgget(server_key,0600|IPC_CREAT);//获取服务器消息队列的标识符
    for (;;) {
        if(msgrcv(server,&req,104,0,0)==-1)//获取从客户端发送过来的请求
        {
            if(errno==EINTR)
                continue;
            break;
        }
        if(fork()==0)//采用并行处理，以防阻塞后所带来的资源浪费
        {
            requestHanle(&req);//进行处理
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}