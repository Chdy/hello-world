//
// Created by 邓岩 on 27/03/2018.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(int argc, char *argv[]) {

    struct timespec t;
    clock_gettime(CLOCK_REALTIME,&t);
    printf("%s",ctime(&t.tv_sec));
    t.tv_sec += 5;
    pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex1);
    pthread_cond_timedwait(&cond1,&mutex1,&t); //在5s内如果条件变量未满足返回，并且不会重新申请互斥锁
    clock_gettime(CLOCK_REALTIME,&t);
    pthread_mutex_lock(&mutex1);
    printf("%s",ctime(&t.tv_sec));
}