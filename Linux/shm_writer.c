//
// Created by 邓岩 on 27/08/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

# define WRITE_SEM 1
# define READ_SEM 0
# define BUFSIZE 1020
# define sem_key 0x1234
# define shm_key 0x2345

struct shmseg{
    int cnt;
    char buf[BUFSIZE];
};

int releaseSem(int semId,int semNums);
int reserveSem(int semId,int semNums);

int main(void)
{
    struct shmseg * shm;
    union semun sem;
    int semid = semget(sem_key,2,IPC_CREAT|0600);
    sem.val = 1;
    semctl(semid,WRITE_SEM,SETVAL,sem);//初始化写者信号量
    sem.val = 0;
    semctl(semid,READ_SEM,SETVAL,sem);//初始化读者信号量
    int shmid = shmget(shm_key, sizeof(struct shmseg),IPC_CREAT|0600);//获取共享内存段
    shm = shmat(shmid,NULL,0);//将内存段装载到进程的虚拟内存
    while(1)
    {
        reserveSem(semid,WRITE_SEM);//用于阻塞写者，当读者处理完数据后释放
        if((shm->cnt = read(STDIN_FILENO,shm->buf,BUFSIZE)) == EOF)//将从标准输入读取的数据写入共享内存段
            exit(-1);
        releaseSem(semid,READ_SEM);//用于写者处理完数据后释放读者
        if(shm->cnt == 1)//当直接敲入会车时，示意已写完数据
            break;
    }
    reserveSem(semid,WRITE_SEM);//等待读者确认数据已全部接受
    semctl(semid,0,IPC_RMID,NULL);//删除信号量
    shmdt(shm);//分离内存段
    shmctl(shmid,IPC_RMID,NULL);//删除内存段
    return 0;
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