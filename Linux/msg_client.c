//
// Created by 邓岩 on 26/07/2017.
//

//ftp客户端

# include </Users/dengyan/ClionProjects/Linux/linux.h>

# define RESP_FAILURE 1
# define RESP_DATA 2
# define RESP_END 3

int server_key = 0xaaaaa;

struct responseMsg
{
    long type;
    char data[4196];
};

struct requestMsg
{
    long type;
    int clientId;
    char filepath[100];
};

int clientId;

void rmid(void)
{
    msgctl(clientId,IPC_RMID,NULL);
}

int main(int argc,char ** argv)
{
    int numBytes;
    struct responseMsg res;
    struct requestMsg req;
    atexit(rmid);
    int server = msgget(server_key,0200);
    clientId = msgget(IPC_PRIVATE,0600|IPC_CREAT);
    req.type = 1;
    req.clientId = clientId;
    strcpy(req.filepath,argv[1]);
    msgsnd(server,&req,strlen(req.filepath)+5,0);
    /*
    这里之所以要增加5是因为struct request结构中第二项为int项
    根据本人的实验，msgsnd的第三个参数应该为除了type项之外的其他数据大小之和，此处就应该为strlen(req.filepath)+sizeof(int)+1，1为空白符所占大小
    */
    numBytes = msgrcv(clientId,&res,2048,0,0);
    if(res.type==RESP_FAILURE)
    {
        printf("%s",res.data);
        msgctl(clientId,IPC_RMID,NULL);
        exit(-1);
    }
    write(STDOUT_FILENO,res.data,strlen(res.data));
    while(res.type==RESP_DATA)
    {
        numBytes = msgrcv(clientId,&res,2048,0,0);
        write(STDOUT_FILENO,res.data,numBytes);
    }
    msgctl(clientId,IPC_RMID,NULL);
    return 0;
}