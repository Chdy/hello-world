//
// Created by 邓岩 on 23/03/2018.
//
/*--------------------------------------------------
 以散列表为数据结构放置锁，并生成另一个锁控制对散列表的改变
 保证加锁的固定顺序以及解锁顺序，这样可以防止死锁的产生
 如果锁的粒度太粗(即分配较少的锁，每个锁有着更大的范围)
 就会出现很多线程阻塞等待相同的锁，这并不能改善并发性
 如果锁的粒度太细，那么过多的锁开销会使系统性能收到影响
 而且代码会变的复杂，因此应该在满足锁需求的情况下，在代码
 复杂性和性能之间找到正确的平衡
 --------------------------------------------------*/
# include </Users/dengyan/ClionProjects/Linux/linux.h>

struct quote
{
    int id;
    int count;
    pthread_mutex_t mutex;
    struct quote * next;
};

# define NHASH 10
# define HASH(id) (((unsigned int)id)%NHASH)

struct quote * fhash[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct quote * mutexalloc(int id)
{
    int index;
    struct quote * mutex;
    if((mutex = (struct quote *)malloc(sizeof(struct quote)))!=NULL)
    {
        mutex->id = id;
        mutex->count = 1;
        if(pthread_mutex_init(&mutex->mutex,NULL)!=0)
        {
            free(mutex);
            return 0;
        }
        index = HASH(id);
        pthread_mutex_lock(&hashlock);
        mutex->next = fhash[index];
        fhash[index] = mutex;
        pthread_mutex_lock(&mutex->mutex);
        pthread_mutex_unlock(&hashlock);
        pthread_mutex_unlock(&mutex->mutex);
    } else
        return 0;
    return mutex;
}

void mutexplus(struct quote * mutex)
{
    pthread_mutex_lock(&mutex->mutex);
    mutex->count++;
    pthread_mutex_unlock(&mutex->mutex);
}

void mutexminus(struct quote * mutex)
{
    int index;
    struct quote * p;
    pthread_mutex_lock(&mutex->mutex);
    if(mutex->count == 1)
    {
        pthread_mutex_unlock(&mutex->mutex);//此处必须先解锁mutex，因为如果在锁住mutex的状态下申请上锁hashlock，此时可能有其他的线程持有hashlock并且正在申请上锁同一个mutex，造成死锁
        //pthread_mutex_lock(&hashlock);//在mutexfind里已经上锁了hashlock，这里不能再上锁，如果单独调用此函数则需要加上改行和下面注释掉的一行
        pthread_mutex_lock(&mutex->mutex);
        if(mutex->count == 1)
        {
            index = HASH(mutex->id);
            p = fhash[index];
            if(p == mutex)
            {
                fhash[index] = mutex->next;
            } else
            {
                while(mutex!=p->next)
                {
                    p = p->next;
                }
                p->next = p->next->next;
            }
            //pthread_mutex_unlock(&hashlock);
            pthread_mutex_unlock(&mutex->mutex);
            free(mutex);
            printf("count值为0，结构已释放\n");
        }
        else
        {
            mutex->count--;
            pthread_mutex_unlock(&hashlock);
            pthread_mutex_unlock(&mutex->mutex);
            printf("操作成功,当前count值为:%d\n",mutex->count);
        }
    }
    else
    {
        mutex->count--;
        pthread_mutex_unlock(&mutex->mutex);
        printf("操作成功,当前count值为:%d\n",mutex->count);
    }
}

struct quote * mutexfind(int id,void (*ch)(struct quote *))
{
    struct quote * mutex;
    pthread_mutex_lock(&hashlock);
    for (mutex = fhash[HASH(id)]; mutex!=NULL ; mutex = mutex->next) {
        if(mutex->id == id){
            ch(mutex);
            break;
        }
    }
    if(mutex == NULL)
        return 0;
    pthread_mutex_unlock(&hashlock);
    return mutex;
}

void hashprint(int i)
{
    struct quote * p;
    if(i == 9)
        return;
    p = fhash[i];
    while(p!=NULL)
    {
        printf("id %2d count %2d ",p->id,p->count);
        p = p->next;
    }
    printf("\n");
    hashprint(i+1);
}

int main(void)
{
    char * p;
    char buf[100];
    struct quote * mutex;
    int a,n,id,num = 0;
    while(1)
    {
        printf("请输入您想进行的操作：\n 1.批量创建互斥量\n 2.增加互斥量\n 3.减少互斥量\n 4.打印散列表\n");
        scanf("%d",&a);
        switch (a)
        {
            case 1:
                printf("请输入想要创建的互斥量id:\n");
                n = read(STDIN_FILENO,buf,100);
                buf[n-1] = ' ';
                buf[n] = 0;
                p = buf;
                while(*p!=0)
                {
                    if(*p!=' ') {
                        num = 10 * num + *p - 48;
                    }
                    else if(mutexalloc(num)!=NULL)
                    {
                        printf("创建id%d成功!\n",num);
                        num = 0;
                    }
                    p++;
                }
                break;
            case 2:
                printf("请输入想要增加的互斥量id:\n");
                scanf("%d",&id);
                if((mutex = mutexfind(id,mutexplus))!=NULL)
                {
                    printf("修改成功，当前count值为:%d\n",mutex->count);
                } else
                    printf("未找到对应互斥量\n");
                break;
            case 3:
                printf("请输入想要减少的互斥量id:\n");
                scanf("%d",&id);
                if((mutex = mutexfind(id,mutexminus))==NULL)
                    printf("未找到对应互斥量\n");
                break;
            case 4:
                hashprint(0);
        }
    }
}

