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
    int semid = semget(sem_key,2,IPC_CREAT|0600);
    int shmid = shmget(shm_key, sizeof(struct shmseg),IPC_CREAT|0600);
    shm = shmat(shmid,NULL,0);
    while(1)
    {
        reserveSem(semid,READ_SEM);//阻塞读者，当写者处理完数据后释放
        if(shm->cnt == 1)
            break;
        write(STDOUT_FILENO,shm->buf,shm->cnt);//将共享内存段中的数据写入标准输出
        releaseSem(semid,WRITE_SEM);//用于读者处理完数据后释放写者
    }
    releaseSem(semid,WRITE_SEM);//示意已经读取了全部数据
    shmdt(shm);//分离内存段
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