//
// Created by 邓岩 on 2018/10/19.
//

//客户端，向消息队列中写入数据

# include </Users/dengyan/ClionProjects/Linux/linux.h>

#define MAXMSG 512

struct mymesg {
    long type;
    char text[MAXMSG];
};

int main(int argc, char *argv[]) {//第一个参数是消息队列的键，第二个参数是需要想消息队列中写入的数据
    key_t key;
    long qid;
    int n;
    struct mymesg m;
    if(argc != 3)
    {
        printf("argument dont enough\n");
        exit(-1);
    }
    key = strtol(argv[1],NULL,0);//将字符串形式的消息的键转换成整形
    if((qid = msgget(key,0)) < 0)
    {
        printf("cant open queue key %s",argv[1]);
        exit(-1);
    }
    memset(&m,0, MAXMSG);
    strcpy(m.text,argv[2]);
    n = strlen(m.text);
    m.type = 1;
    if(msgsnd(qid,&m,n,0) < 0)
    {
        printf("msgsnd error");
        exit(-1);
    }
    return 0;
}