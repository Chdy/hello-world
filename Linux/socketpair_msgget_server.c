//
// Created by 邓岩 on 2018/10/19.
//

//此进程生成三个线程，每个线程连接一个消息队列以及一个unix域，当线程从消息队列读取到数据时，写入到unix域中，此时主线程的poll会返回，检查哪个一个unix域中有可读数据
//检测到后读出数据写到标准输出

# include </Users/dengyan/ClionProjects/Linux/linux.h>

#define NQ 3 //队列数量
#define  MAXMSZ 514 //最大消息大小
#define  KEY 0x123 //第一个消息队列的键值

struct threadinfo { //所生成线程的消息队列id以及连接的unix域套接字文件描述符
    int qid;
    int fd;
};

struct mymesg { //消息结构
    long type;
    char text[MAXMSZ];
};

void * helper(void * arg)
{
    int n;
    struct mymesg m;
    struct threadinfo * tip = arg;
    for(;;)
    {
        memset(&m,0, sizeof(m));
        if((n = msgrcv(tip->qid,&m,MAXMSZ,0,MSG_NOERROR)) < 0)
        {
            printf("msgrcv error");
            exit(-1);
        }
        if(write(tip->fd,m.text,n) < 0)
        {
            printf("write error");
            exit(-1);
        }
    }
}

int main(int argc, char *argv[]) {
    int i,n,err;
    int fd[2];
    int qid[NQ];
    struct pollfd pfd[NQ];
    struct threadinfo ti[NQ];
    pthread_t tid[NQ];
    char buf[MAXMSZ];
    for (i = 0; i < NQ; ++i) {
        if((qid[i] = msgget((KEY+i),IPC_CREAT|0666)) < 0)
        {
            printf("msgget error");
            exit(-1);
        }
        printf("queue ID %d is %d\n",i,qid[i]);
        if(socketpair(AF_UNIX,SOCK_DGRAM,0,fd) < 0)//这里使用数据报，因为这样可以保持消息边界，从而保证从套接字里一次只读取一条消息
        {
            printf("socketpair error");
            exit(-1);
        }
        pfd[i].fd = fd[0];
        pfd[i].events = POLLIN;
        ti[i].qid = qid[i];
        ti[i].fd = fd[1];
        pthread_create(&tid[i],NULL,helper,ti + i);
    }
    for(;;)
    {
        if(poll(pfd,NQ,-1) < 0)
        {
            printf("poll error");
            exit(-1);
        }
        for (i = 0; i < NQ; ++i) {
            if(pfd[i].revents & POLLIN)
            {
                if((n = read(pfd[i].fd,buf, MAXMSZ)) < 0)
                {
                    printf("read error");
                    exit(-1);
                }
                buf[n] = 0;
                printf("queue id %d,message %s\n",qid[i],buf);
            }
        }
    }

    return 0;
}