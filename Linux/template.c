//
// Created by 邓岩 on 14/07/2017.
//
# include </Users/dengyan/ClionProjects/Linux/linux.h>

pthread_t tid;

void printid(char * s)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s pid %d tid %lu,Ox%lx\n",s,pid,(unsigned long)tid,(unsigned long)tid);
}

void tuichu(void * s)
{
    printf("%s",s);
}

void * start(void * arg) {
    printid("new thread:");
    pthread_cleanup_push(tuichu, "thread exit handler\n");
        pthread_cleanup_push(tuichu,"thread exit 2\n");
            pthread_cleanup_push(tuichu,"thread exit 1\n");
            pthread_exit((void *) 13);
            pthread_cleanup_pop(0);
        pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return 0;
 }

int main(void)
{
    int err;
    void * rval;
    if((err = pthread_create(&tid,NULL,start,NULL))!=0)
        exit(-1);
    pthread_join(tid,&rval);
    printf("rval = %d\n",rval);
    printid("main thread:");
    sleep(1);
    exit(-1);
}