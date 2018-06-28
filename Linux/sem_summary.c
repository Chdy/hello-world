//
// Created by 邓岩 on 01/11/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(void)//使子进程先运行
{
    union semun sem;
    sem.val = 0;
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_flg = 0;
    int key = ftok("/Users/dengyan/exam",'x');
    int semid = semget(key,1,IPC_CREAT|0611);//创建信号量
    int i = semctl(semid,0,SETVAL,sem.val);//初始化单个信号量
    if(fork())
    {
        sbuf.sem_op = -1;
        while(!semop(semid,&sbuf,1))
        {
            printf("I am parents \n");
            sleep(2);
        }
    } else
    {
        sbuf.sem_op = 1;
        while(!semop(semid,&sbuf,1))
        {
            printf("I am child \n");
            sleep(2);
        }
    }
}