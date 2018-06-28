//
// Created by 邓岩 on 22/08/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
//信号量修改与查看，二元信号量协议

int main(int argc,char ** argv)
{
    struct semid_ds ds;
    union semun arg;
    arg.buf = &ds;
    struct sembuf sop[5];
    int key = ftok("/Users/dengyan",'x');
    int identity = semget(key,5,IPC_CREAT|0600);
    if(semctl(identity,0,IPC_STAT,arg)==-1)
    {
        printf("error\n");
    }
    printf("the semaphore is %d\n",arg.buf->sem_nsems);
    arg.array = malloc(5 * sizeof(arg.array[0]));
    for (int j = 0; j < 5; ++j) {
        arg.array[j] = j;
    }
    sop[0].sem_flg = 0;
    sop[1].sem_flg = 0;
    sop[2].sem_flg = SEM_UNDO;
    sop[0].sem_num = 0;
    sop[1].sem_num = 1;
    sop[2].sem_num = 2;
    sop[0].sem_op = 10;
    sop[1].sem_op = 10;
    sop[2].sem_op = 10;
    //semop(identity,sop,3);
    semctl(identity,0,GETALL,arg);
    for (int i = 0; i < 5; ++i) {
        printf("%d\n",arg.array[i]);
    }
}

int initSemAvailable(int semId,int semNums)
{
    union semun arg;
    arg.val = 1;
    return semctl(semId,semNums,SETVAL,arg);
}

int initSemInUse(int semId,int semNums)
{
    union semun arg;
    arg.val = 0;
    return semctl(semId,semNums,SETVAL,arg);
}

int reserveSem(int semId,int semNums)
{
    struct sembuf sop;
    sop.sem_op = -1;
    sop.sem_num = semNums;
    sop.sem_flg = 0;
    while(semop(semId,&sop,1) == -1)
        if(errno != EINTR)
            return -1;
    return 0;
}

int releaseSem(int semId,int semNums)
{
    struct sembuf sop;
    sop.sem_op = 1;
    sop.sem_num = semNums;
    sop.sem_flg = 0;
    while(semop(semId,&sop,1) == -1)
        if(errno != EINTR)
            return -1;
    return 0;
}