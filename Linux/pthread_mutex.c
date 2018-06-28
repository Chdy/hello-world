//
// Created by 邓岩 on 23/03/2018.
//
/*-------------------------------------------------
 引用值的增加及减少以及释放，使用线程互斥量保证引用值的正确性
 -------------------------------------------------*/
# include </Users/dengyan/ClionProjects/Linux/linux.h>

struct quote
{
    int count;
    pthread_mutex_t mutex;
    int id;
};

struct quote * mutexalloc(int id)
{
    struct quote * mutex;
    if((mutex = (struct quote *)malloc(sizeof(struct quote)))!=NULL)
    {
        mutex->id = id;
        pthread_mutex_init(&mutex->mutex,NULL);
        mutex->count = 1;
    } else
        printf("互斥量分配失败\n");
    return mutex;
}

void mutexplus(struct quote * mutex)
{
    pthread_mutex_lock(&mutex->mutex);
    mutex->count++;
    printf("now the count is %d\n",mutex->count);
    pthread_mutex_unlock(&mutex->mutex);
}

void mutexminus(struct quote * mutex)
{
    pthread_mutex_lock(&mutex->mutex);
    if(--mutex->count==0)
    {
        pthread_mutex_unlock(&mutex->mutex);
        printf("count is zero,quote id %d was released\n",mutex->id);
        pthread_mutex_destroy(&mutex->mutex);
        free(mutex);
        exit(0);
    } else
    {
        printf("now the count is %d\n",mutex->count);
        pthread_mutex_unlock(&mutex->mutex);
    }
}

int main(void)
{
    char mark;
    struct quote * mutex = mutexalloc(1);
    while(1)
    {
        read(STDIN_FILENO,&mark,2);
        if(mark == '+')
            mutexplus(mutex);
        if(mark == '-')
            mutexminus(mutex);
    }
}