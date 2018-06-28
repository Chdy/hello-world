//
// Created by 邓岩 on 12/03/2017.
//
// mac是小端机器，实验方法，在int中存入一个较大的数字，如Ox1f2f3f4f，然后定义一个指针指向该整形，将指针强制转换为char *后将后三个字节写为0，再次输出该数字，输出79，说明4f被存入最低地址的内存
# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include <GLUT/GLUT.h>

static jmp_buf env;

extern char ** environ;

void printWaitStatus(char * msg,int status);
void printSigset(FILE * io,const char * prestr,const sigset_t * sigset);
void printSigmask(FILE * io,const char * msg);
void printPending(FILE * io,const char * msg);

#ifdef USE_SIGSETJMP
static sigjmp_buf senv;
#else
static jmp_buf env;
#endif

static volatile sig_atomic_t canJmp = 0;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static __thread char sbuf[100];

void * thread_func(void * arg)
{
    printf("Other thread call strerror\n");
    strcpy(sbuf,"123456");
    printf("%s",sbuf);
    return 0;
}

void sig_handler(int sig)
{
    sigset_t mask;
    sigset_t premask;
    struct sigvec sv;
    printf("Caught SIGTSTP\n");
    signal(SIGTSTP,SIG_DFL);//将信号处理程序恢复成默认处理
    raise(SIGTSTP);//向自身发送SIGTSTP信号，此处可以发送SIGSTOP信号，下面的内容将不再需要，但是如果父进程需要获取子进程退出信息，将导致收到的退出信息不准确
    sigemptyset(&mask);
    sigaddset(&mask,SIGTSTP);
    sigprocmask(SIG_UNBLOCK,&mask,&premask);//取消对SIGTSTP的阻塞，此时进程会在此时停止
    //当接收到SIGCONT信号后，从此处开始继续执行，恢复开始的信号处理程序
    sigprocmask(SIG_SETMASK,&premask,NULL);
    sv.sv_mask = 0;
    sv.sv_handler = sig_handler;
    sigvec(SIGTSTP,&sv,NULL);
    printf("Handler is exiting\n");
}

struct mybuf
{
    long type;
    char text[1024];
};

void hand(int sig)
{
    int i;
    if(sig == SIGIO)
        printf("receive\n");
    //while(i = read(fd,sbuf,100))
    //    write(STDOUT_FILENO,sbuf,i);
}

void * f1(void * arg)
{
    int type;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,&type);
    int fd = open("/Users/dengyan/exam",O_WRONLY);
    write(fd,"ok",3);
    printf("tid = %p\n",pthread_self());
    printf("arg is %d\n",(int)arg);
    pthread_exit(pthread_self());
}

int main(int argc, char *argv[]) {
    struct stat st;
    struct dirent * dir;
    void * arg;
    pthread_t pt1;
    pthread_t pt2;
    pthread_rwlock_t rwlock;
    pthread_attr_t attr;
    int fd = open("/Users/dengyan/exam",O_WRONLY);
    write(fd,"2",1);
    /*pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    struct timespec t;
    clock_gettime(CLOCK_REALTIME,&t);
    printf("%s",ctime(&t.tv_sec));
    t.tv_sec += 20;
    pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
    pthread_create(&pt1,&attr,f1,5);
    pthread_cancel(pt1);
    sleep(1);*/
    printf("123");
    //printf("%s",strerror(error));
}

void printWaitStatus(char * msg,int status)
{
    if(msg!=NULL)
        printf("%s",msg);
    if(WIFEXITED(status))
        printf("child exited,status=%d\n",WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("child killed by signal %s\n",strsignal(WTERMSIG(status)));
    else if(WIFSTOPPED(status))
        printf("child stop by signal %s\n",strsignal(WSTOPSIG(status)));
    else if(WIFCONTINUED(status))
        printf("child continued\n");
    else
        printf("what happened to this child? status=%x\n",(unsigned)status);
}

void printSigset(FILE * io,const char * prestr,const sigset_t * sigset)
{
    int cnt = 0;
    for (int i = 1; i < NSIG; ++i) {
        if(sigismember(sigset,i))
        {
            cnt++;
            fprintf(io,"%s%s\n",prestr,strsignal(i));
        }
    }
    if(cnt==0)
        fprintf(io,"%s empty sigset\n",prestr);
}

void printSigmask(FILE * io,const char * msg)
{
    sigset_t curmask;
    sigprocmask(SIG_BLOCK,NULL,&curmask);
    if(msg!=NULL)
        fprintf(io,"%s",msg);
    printSigset(io,"\t\t",&curmask);
}

void printPending(FILE * io,const char * msg)
{
    sigset_t sigpend;
    sigpending(&sigpend);
    if(msg!=NULL)
        fprintf(io,"%s",msg);
    printSigset(io,"\t\t",&sigpend);
}
/* 学习过的系统调用函数:
 * fcntl(fd,F_SETFL,flags|O_ASYN) 设置信号IO，通过fcntl(fd,F_SETOWN,uid)设置接收SIGIO的进程
 * poll(pollfd[],int nfds,int timeout) pollfd{int fd,short events,short revents} events = POLLIN|POLLRDNORM|POLLRDBAND|POLLPRI|POLLOUT|POLLWRNORM|POLLWRBAND|POLLERR|POLLHUP|POLLNVAL，nfds指数组元素的个数，timeout为-1时永久等待，为0时测试后立即返回，其余值时为等待timeout毫秒
 * select(int nfds,fd_set * readset,fd_set * writeset,fd_set * errorset,timeval * intval) io多路复用，等待一定长的时间，返回已准备好的文件描述符个数，nfds为当前最大的文件描述符加1，这样就只会检查小于nfds的文件描述符状态，intval等于NULL时，永远等待，直到指定中的一个文件描述符已准备好或者捕捉到一个信号终端此进程，intval->tv_sec==0&&intval->tv_usec==0，不等待，测试所有文件描述符后立即返回，当intval有其他值时，等待指定的描述和微妙数，当指定描述符中的一个文件描述符准备好时，或者超过指定时间，则立即返回，readset，writeset，errorset分别返回所关心描述符状态的结果，每一个位对应一个描述符，当调用完成后，若对应位为1，则表示该下标对应的描述符为准备好状态，如设置为NULL，则表示对该状态不关心
 * ttyname(fd) 返回这个文件描述符相关联的终端名称
 * isatty(fd) 判断文件描述符是否同一个终端相关联
 * ctermid(buf) 返回进程控制终端的名称
 * ioctl(fd,TIOCGWINSZ,winsize *)
 * tcsetattr(fd,option,termios *) option = TCSANOW|TCSADRAIN|TCSAFLUSH 分别为修改立即生效，等处理完终端输出缓冲区的数据后生效，抛弃终端输入缓冲区的数据然后生效
 * tcgetattr(fd,termios *)
 * ioctl(fd,FIONREAD,&cnt) 获取终端输入队列中的未读取字节数
 * recvmsg()
 * sendmsg() 可以传递文件描述符
 * setsockopt(sockfd,level,optname,&optval,len)
 * getsockopt(sockfd,level,optname,&optval,&len) level = SOL_SOCKET optname = SO_REUSEADDR
 * getpeername(sockfd,sockaddr *,&len)
 * getsockname(sockfd,sockaddr *,&len)
 * sendfile(fd,sockfd,&offset,len) mac上未成功，且mac上有六个参数
 * recv(sockfd,buf,len,flags) flags = MSG_DONTWAIT
 * send(sockfd,buf,len,flags) flags = MSG_DONTWAIT|MSG_OOB|MSG_PEEK|MSG_WAITALL MSG_DONTWAIT此次调用不会阻塞，MSG_PEEK获取sockfd缓冲区中数据的一份副本，不会将数据从缓冲区移除，MSG_WAITALL直到等待接受到len个字节后才会返回
 * shutdown(sockfd,flags) flags = SHUT_RD|SHUT_WR|SHUT_RDWR
 * gethostbyname(port,char * protocal)
 * getservbyhost(char * name,char * protocal)
 * freeaddrinfo(addrinfo *)
 * getnameinfo(sockaddr *,addrlen,char * host,hostlen,char * service,servlen,flags) flags = NI_DGRAM|NI_NAMEREQD|NI_NOFQDN|NI_NUMERICHOST|NI_NUMERICSERV
 * getaddrinfo(char * host,char * service,addrinfo *,addrinfo **) addrinfo{ai_flags,ai_family,ai_socktype,ai_protocol,ai_addrlen,ai_canonname,sockaddr * ai_addr,addrinfo * ai_next} ai_family = AF_INET|AF_INET6|AF_UNSPEC 意义为获取哪种地址结构 ai_flags = AI_ADDRCONFIG|AI_ALL|AI_NUMERICHOST|AI_NUMERICSERV|AI_PASSIVE|AI_V4MAPPED
 * inet_ntop(domain,in_addr|in6_addr *,char *,addrlen) domain = AF_INET|AF_INET6
 * inet_pton(domain,char *,in_addr|in6_addr *) domain = AF_INET|AF_INET6 由表现形式转换成网络形式，即点分十进制字符串转换成二进制数字
 * inet_ntoa(char *,in_addr *) 只能用于IPv4，已过时
 * inet_aton(in_addr) 只能用于IPv4，已过时
 * ntohl(int)
 * ntohs(short)
 * htonl(int)
 * htons(short) h代表主机(host)，n代表网络(network)，表示在主机字节序与网络字节序之间进行转换
 * socketpair(domain,type,protocal,int [2]) domain = AF_UNIX|AF_INET|AF_INET6 type = SOCK_STREAM|SOCK_DGRAM
 * recvfrom(sockfd,buf,length,flags,sockaddr *,&addrlen)
 * sendto(sockfd,buf,length,flags,sockaddr *,addrlen)
 * connect(sockfd,sockaddr *,addrlen) 当在一个数据报socket上使用connect后，可以使用read和write操作描述符
 * accept(sockfd,sockaddr *,&addrlen) 会新建一个socket用于和接入的socket通信
 * listen(sockfd,backlog) backlog用于限制发起请求连接的数量，该函数用于监听接入的连接
 * bind(sockfd,sockaddr *,addrlen) sockaddr = sockaddr_un(AF_UNIX)|sockaddr_in(AF_INET)|sockaddr_in6(AF_INET6) addrlen要根据使用的sockaddr来确定，不能使用sizeof(struct sockaddr)
 * socket(domain,type,protocal) domain = AF_UNIX|AF_INET|AF_INET6 type = SOCK_STREAM|SOCK_DGRAM|SOCK_SEQPACKET 分别为流socket(TCP),数据包socket(UDP),有消息边界的流socket protocal通常为0，INADDR_LOOPBACK为IPV4回环地址，INADDR_ANY为IPV4通配地址，均为整形数据，IN6ADDR_LOOPBACK_INIT为IPV6回环地址，IN6ADDR_ANY_INIT为IPV6通配地址，为结构体类型
 * fcntl(fd,cmd,flock *) cmd = F_SETLK|F_SETLKW_F_GETLK 分别为设置锁，非阻塞操作设置锁，检测锁，flock{l_type,l_whence,l_start,l_len,l_pid} l_type = F_RDLCK|F_WRLCK|F_UNLCK 分别为设置读锁(共享锁)，写锁(互斥锁)，解锁，该函数放置锁需要与文件的打开模式相对应，即需要放置两种锁时，文件的打开模式应该为O_RDWR l_whence = SEEK_SET|SEEK_CUR|SEEK_END l_start为偏移量 l_len为长度，,当len为0时，表示锁的范围可以拓展到最大可能偏移量(无论此后追加写入了多少数据)，l_pid当cmd为F_GETLK时有效，返回拥有该锁的进程id，单个进程在某一时刻只能对一个文件区间拥有一把锁。多次加锁会覆盖上个锁
 * flock(fd,flags) flags = LOCK_SH|LOCK_EX|LOCK_UN|LOCK_NB LOCK_SH为设置共享锁，LOCK_EX为设置互斥锁，LOCK_UN为解锁，LOCK_NB为执行非阻塞操作，无论对文件的访问模式是只读，只写或是读写都可以在上面放置共享锁和互斥锁，该函数的操作单位为整个文件，并且flock的锁转换非原子操作，它是先解锁，然后上锁，在解锁和上锁之间可能会有其他进程的上锁请求成功执行，此时该函数会阻塞，并且原本拥有的锁丢失
 * madvise(addr,length,flags) flags = MADV_NORMAL|MADV_RANDOM|MADV_SEQUENTIAL|MADV_WILLNEED|MADV_DONTNEED
 * mincore(addr,length,char vec[]) 无论是产生何种映射，包括私人匿名映射(堆分配)，并不会立即为这些映射分配相应的内存，需要访问相应的虚拟内存产生缺页错误后才会进行分配
 * munlockall(void)
 * mlockall(flags) flags = MCL_CURRENT|MCL_FUTURE MCL_CURRENT将进程的虚拟内存中当前所有映射的分页全部锁进内存，MCL_FUTURE将后续映射到虚拟内存中的所有分页锁进内存
 * munlock(addr,length) 解锁以页为单位，当对同一页进行多次上锁也只会产生一次效果，某页的上锁属性应该保存在进程的该页的映射数据结构中，如果多个进程共享映射同一组分页时，只要还存在一个进程持有这些分页上的内存锁，那么这些分页就会保持被锁进内存的状态
 * mlock(addr,length) 当调用完成后，即使映射的地址区域当前不在区域内，也会在该函数返回前将该区域换进内存，而不需要等待发生缺页
 * mprotect(addr,length,flags) flags = prot = PROT_NONE|PROT_READ|PROT_WRITE|PROT_EXEC 用于更改保护位
 * msync(addr,length,flags) 将页写回硬盘，flags = MS_SYNC|MS_ASYNC|MS_INVALIDATE 分别为同步更新，异步更新，通知其他进程该共享区域已经更改了(不懂有什么意义)
 * munmap(addr,length) 解除映射区
 * mmap(addr,length,prot,flags,fd|-1,offset) prot = PROT_NONE|PROT_READ|PROT_WRITE|PROT_EXEC 如果要写文件，则应该设置PROT_READ|PROT_WRITR并且打开文件时应该指定标记O_RDWR，映射文件时size不能超过文件的大小(可用lseek加write或者ftruncate增加文件大小) flags = MAP_PRIVATE|MAP_SHARED|MAP_ANONYMOUS|MAP_FIXED|MAP_NORESERVE PROT_NONE表示区域无法访问，MAP_PRIVATE表示创建私人映射，MAP_SHARED表示创建共享映射，MAP_ANONYMOUS表示创建匿名映射，私人匿名映射类似堆分配(但是没有堆分配时块与块之间的联系)，共享匿名映射就是共享内存分配，MAP_FIXED表示不对addr参数进行处理，否则会将addr参数向上取整为分页大小的倍数，此时会对addr地址强行进行映射，还能覆盖该地址之前的映射
 * shmctl(shmid,cmd,shmid_ds *) cmd = IPC_RMID|IPC_STAT|IPC_SET
 * shmdt(addr)
 * shmat(shmid,addr,flags) flags = SHM_RND|SHM_RDONLY 分别为将addr的值自动四舍五入到页面大小的倍数，将内存块以只读方式装载到调用进程的虚拟内存，如果addr为空则不需要用SHM_RND，反之加上
 * shmget(key,size,flags) flags = IPC_CREAT|IPC_EXCL
 * semctl(semid,semnum,cmd,...union semun) cmd = IPC_RMID|IPC_STAT|IPC_SET|GETVAL|SETVAL|GETALL|GETPIC|GETNCNT|GETZCNT IPC_SET用semun->semid_ds的属性更新该信号量关联的数据结构，GETVAL返回由semid指定的第semnum个信号量的值，SETVAL将第semnum个信号量设置为semnu->val，GETALL将信号量集中的值设置为semun->array[]，SETALL为设置
 * semop(semid,sembuf *,flags) sembuf{sem_num,sem_op,sem_flg} sem_flg = IPC_NOWAIT|SEM_UNDO 当该操作阻塞时，即减少信号量值导致信号量小于0时，此时如果被信号中断，该操作不会自动重启
 * semget(key,nsems,flags) flags = IPC_CREAT|IPC_EXCL
 * msgctl(msqid,cmd,msqid_ds *) cmd = IPC_RMID|IPC_STAT|IPC_SET 分别为删除消息队列，获取属性，设置属性
 * msgrcv(msqid,void *,maxmsgsize,msgtype,flags) flags = IPC_NOWAIT|MSG_NOERROR msgtype==0则接受队列中第一条消息，大于0则接受队列中消息类型等于msgtype的消息，返回值为对应msgsnd第三个参数大小
 * msgsnd(msqid,void *,msgsize,flags) flagss = IPC_NOWAIT 发送的消息类型不能为0，第三个参数为除了type项之外的数据大小之和，mac上的管道容量为2048个字节
 * msgget(key,flags) flags = IPC_CREAT|IPC_EXCL key |= IPC_PRIVATE
 * ftok(pathname,char)
 * mkfifo(pathname,mode)  命名管道，即该管道实际上为一文件，程序需要打开该文件进行通信，一端以只读方式打开，另一端以只写方式打开，先打开的一端会阻塞，直到另一端打开，或者设置O_NONBLOCK，设置O_NONBLOCK后需要先打开读取端
 * pclose(FILE *)
 * popen(cmd,mode)
 * pipe(int [2]) 如果某管道的写入端未关闭，且当前管道内无数据，此时进行读取会阻塞；即管道的写入端如果已关闭，此时进行读取且管道内无数据会直接返回0，fork会复制pipe产生的文件描述符
 * pututxline(utmpx *)
 * getutxline(utmpx *)
 * getutxid(utpmx *)
 * getutxent(void)
 * utmpxname(filepath)
 * endutxent(void)
 * setutxent(void)
 * setpriority(which,who,value)
 * getpriority(which,who) which = PRIO_PROCESS|PRIO_PGRP|PRIO_USER
 * tcgetsid(fd) 获取会话首进程的进程组id
 * tcsetpgrp(fd,pid) 将fd关联终端的前台组id设置为会话中的另一个进程组id
 * tcgetpgrp(fd) fd为终端关联的文件描述符，返回前台进程组id
 * setsid(pid) 创建一个新会话
 * getsid() 获取进程的会话id
 * setpgid(pid,pgid) 如果pid为0，则等价于getpid()，如果pgid为0，也等于getpid()
 * setpgrp() 将调用进程的进程组id设置为调用进程的进程id
 * getpgid(pid) 获取进程id为pid的进程组id，如果pid为0，则为调用进程
 * getpgrp() 获取调用进程的进程组id
 * 线程与信号：每个线程都有自己的信号屏蔽字，但是信号的处理是进程中所有线程共享的，这意味着线程可以阻止某些信号，但当某个线程修改了信号处理程序后，所有的线程都必须共享这个处理行为的改变，进程中的信号是传递到单个线程的，如果一个信号与硬件故障相关，那么该信号一般会被发送到引起该时间的信号中去，而其他的信号则被发送到任意一个线程
 * pthread_kill(pthread_t,signo) 线程级的kill，可以通过发送0查看线程是否存在，如果信号的默认处理动作是终止该进程，那么发送到任意一个线程都会终止该线程
 * sigwait(sigset_t * set,int * signop) 先解除信号的阻塞状态，如果set中的信号集包含有被阻塞的信号，移除那些被阻塞的信号，函数立刻返回，否则阻塞直到收到集合中的信号(无论信号是否被阻塞)，此函数返回后不会改变原来的信号掩码
 * pthread_sigmask(int how,sigset_t * new,sigset_t * old) 线程级的sigprocmask，失败时返回错误码，而不是设置errno并返回-1
 * pthread_testcancel(void) 设置取消点，到达此函数时，如果有挂起的取消请求，并且取消状态不为DISABLE，那么线程会被取消，否则此函数无效
 * pthread_setcanceltype(type,oldtype) type = PTHREAD_CANCEL_ASYNCHRONOUS|PTHREAD_CANCEL_DEFERRED 设置可取消类型，type分别为异步取消和推迟取消，默认为推迟取消，则需要到达取消点时才可取消，而设置异步取消时，线程可以在任意时间取消
 * pthread_setcancelstate(state,oldstate) type = PTHREAD_CANCEL_DISABLE|PTHREAD_CANCEL_ENABLE 设置可取消状态，默认状态为ENABLE，如果在ENABLE状态时接收到了取消请求，挂起请求,在到达取消点时线程会取消，如果为DISABLE状态，收到的取消请求会挂起，直到由DISABLE变为ENABLE时，才会在下一个取消点处理取消请求
 * pthread_cleanup_pop(0|!0) 如果为0，线程退出处理函数将不会被调用，如果非0则立即调用，mac上这两个函数用宏实现，如果使用最好同时调用
 * pthread_cleanup_push(void (*func)(void *),void * arg) 设置线程退出处理程序，等同于进程的atexit，但如果线程正常退出则不会调用(return)
 * pthread_getspecific(pthread_key_t)
 * pthread_setspecific(pthread_key_t,void *)
 * pthread_key_create(pthread_key_t *,void (*destructor)(void *)) 创建一个键，用于获取对线程特定数据的访问
 * pthread_condattr_setpshared(pthread_condattr_t *,int attr) 控制着条件变量是可以被单个进程的多个线程使用，还是可以被多进程的线程使用
 * pthread_condattr_getpshared(pthread_condattr_t *,int * attr) 获取条件变量的的进程同步属性
 * pthread_once(pthread_once_t *,void (*init)(void))
 * pthread_cond_broadcast(pthread_cond_t *) 唤醒所有等待该条件的线程
 * pthread_cond_signal(pthread_cond_t *) 将条件变为真，并至少唤醒一个等待该条件的线程
 * pthread_cond_timedwait(pthread_cond_t *,pthread_mutex_t *,timespec *) 指定所需要等待的时间，当超出时间后还未满足条件则返回错误码，并且不会将释放掉的互斥锁再次上锁，这里的timespec是当前时间加成等待时间
 * pthread_cond_wait(pthread_cond_t *,pthread_mutex_t *) 选定某个已上锁的互斥量，然后阻塞并等待条件变量变为真，运行期间会释放互斥锁，当满足条件返回时会再次申请上锁
 * pthread_cond_destroy(pthread_cond_t *) 释放条件变量所在的内存空间前对条件变量进行反初始化
 * pthread_cond_init(pthread_cond_t *,pthread_condattr_t *) 动态分配条件变量
 * static pthread_cond_t cond = PTHREAD_COND_INITIALIZER 静态分配条件变量
 * pthread_rwlockattr_setpshared(pthread_rwlockattr_t *,int attr) 设置读写锁进程共享属性
 * pthread_rwlockattr_getpshared(pthread_rwlockattr_t *,int * attr) 获取读写锁进程共享属性
 * pthread_rwlock_trywrlock(pthread_rwlock_t *) 获取写锁成功时，返回0，否则返回EBUSY
 * pthread_rwlock_tryrdlock(pthread_rwlock_t *) 获取读锁成功时，返回0，否则返回EBUSY
 * pthread_rwlock_unlock(pthread_rwlock_t *) 解锁读写锁
 * pthread_rwlock_wrlock(pthread_rwlock_t *) 使用写模式锁定读写锁，一个锁上只能有一个写锁，申请上其他锁时都会产生阻塞
 * pthread_rwlock_rdlock(pthread_rwlock_t *) 使用读模式锁定读写锁，可对一个锁同时上多个读锁，可能会因为系统实现而对读写锁有次数限制，所以应进行返回值检查
 * pthread_rwlock_destroy(pthread_rwlock_t *) 在使用完读写锁后需要进行释放
 * pthread_rwlock_init(pthread_rwlock_t *,pthread_rwlockattr_t *) 对读写锁进行初始化，如需要默认属性可以传递NULL给第二个参数
 * pthread_mutexattr_settype(pthread_mutexattr_t *,flag) flag = PTHREAD_MUTEX_NORMAL|PTHREAD_MUTEX_ERRORCHECK|PTHREAD_MUTEX_RECURSIVE NORMAL一种标准互斥量类型，不进行错误检查或死锁检测，ERRORCHECK为互斥量提供死锁检测，RECURSIVE运行同一线程在互斥量解锁之前对该互斥量多次加锁，在解锁状态和加锁状态不相同的情况下，不会释放该锁
 * pthread_mutexattr_gettype(pthread_mutexattr_t *,int * type) 获取线程的互斥量锁定特性
 * pthread_mutexattr_setpshared(pthread_mutexattr_t *,int attr) attr = PTHREAD_PROCESS_PRIVATE|PTHREAD_PROCESS_SHARED PRIVATE为默认行为，多个线程可以访问同一个互斥量，SHARED为进程可以访问同一个互斥量
 * pthread_mutexattr_getpshared(pthread_mutexattr_t *,int * attr) 获取互斥量进程共享属性
 * pthread_mutexattr_destroy(pthread_mutexattr_t *) 反初始化
 * pthread_mutexattr_init(pthread_mutexattr_t *) 初始化互斥量属性
 * pthread_mutex_timedlock(pthread_mutex_t *,timespec *) mac os没有实现此函数，请求加锁，如果阻塞，则等待一定时间，如果在时间内未成功开锁，则返回错误
 * pthread_mutex_unlock(pthread_mutex_t *) 对互斥量解锁
 * pthread_mutex_trylock(pthread_mutex_t *) 如果互斥量已经上锁，不会阻塞，会直接返回失败，并且设置EBUSY错误码
 * pthread_mutex_lock(pthread_mutex_t *) 对互斥量进行加锁，如果互斥量已经上锁，调用线程将阻塞直到互斥量被解锁
 * pthread_mutex_destroy(pthread_mutex_t *) 释放动态互斥量的内存
 * pthread_mutex_init(pthread_mutex_t *,pthread_mutexattr_t *) 动态分配互斥量
 * pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER 静态分配互斥量
 * pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
 * pthread_attr_setguardsize(pthread_attr_t *,int guardsize) 设置线程栈末尾之后避免栈溢出的拓展内存大小，如果设置为0，则取消此特征
 * pthread_attr_getguardsize(pthread_attr_t *,int * guardsize) 获取线程栈末尾之后避免栈溢出的拓展内存大小
 * pthread_attr_setstacksize(pthread_attr_t *,int stacksize) 设置属性对象中线程栈的大小，不需要处理分配地址
 * pthread_attr_getstacksize(pthread_attr_t *,int * stacksize) 获取属性对象中线程栈的大小
 * pthread_attr_setstack(pthread_attr_t *,void * addr,int size) 设置属性对象中线程栈的大小和地址，地址需要与边界对齐
 * pthread_attr_getstack(pthread_attr_t *,void ** addr,int * size) 获取属性对象中线程栈的大小和地址
 * pthread_attr_setdetachstate(pthread_attr_t *,int * detachstate) detachstate = PTHREAD_CREATE_DETACHED|PTHREAD_CREATE_JOINABLE，设置PTHREAD_CREATE_DETACHED后，线程在运行时就会直接处理分离阶段，设置PTHREAD_CREATE_JOINABLE的线程会正常启动
 * pthread_attr_getdetachstate(pthread_attr_t *,int * detachstate) 获取属性对象的detachstat值
 * pthread_attr_destroy(pthread_attr_t *) 对属性对象进行反初始化
 * pthread_attr_init(pthread_attr_t *) 对属性对象进行初始化
 * pthread_detach(pthread_t) 分离指定的线程，分离后线程占用的资源会在终止时立即释放，不能用pthread_join获取一个分离线程的退出状态
 * pthread_cancel(pthread_t) 取消同一进程内的其他进程，仅仅提出请求，分离的线程也可取消
 * pthread_join(pthread_t tid,void * &rval) 类似进程级的waitpid，阻塞，直到tid指定的线程调用pthread_exit(rval等于pthread_exit的参数值)，通过return正常返回(rval会等于tid线程的返回值)，或者被取消(rval会等于PTHREAD_CANCELED(1))
 * pthread_equal(pthread_t,pthread_t) 判断两个线程id是否相等
 * pthread_self(void) 类似进程级的getpid，获取自身线程id
 * pthread_exit(void *) 退出当前线程，返回值可以由pthread_join接收，或者用return，如果用exit的三个函数退出，会直接终止整个进程，当main结束时，子线程结束运行
 * pthread_create(pthread_t * tid,pthread_attr_t *,void *(*start)(void *),void * arg) 类似进程级的fork，*tid为线程创建成功后返回的线程id，线程从start函数开始运行，如果有超过一个以上的参数，则可以将这些参数放入某个结构，将结构的地址用arg参数传入，新线程会继承调用线程的浮点环境(文件描述符，环境变量，默认权限掩码等)和信号屏蔽字，不会继承原线程挂起的信号
 * fexecve(fd,char ** argv,char ** env)
 * execl(pathname,char * argv,...)
 * execv(pathname,char ** argv)
 * execlp(filename,char * argv,...)
 * execvp(filename,char ** argv)
 * execle(pathname,char * argv,...,char ** env)
 * execve(pathname,char ** argv,char ** env) 倒数第二位为'v'代表参数类型为数组，为'l'则为列表，最后一位为'p'则会通过路径列表查找文件，最后一位为'e'允许带环境参数，带环境参数后不会继承原进程环境变量,如果不带环境参数则继承原进程环境变量
 * wait4(pid,status,options,rusage *)
 * wait3(status,options,rusage *)
 * waitid(idtype_t,pid,siginfo_t *,options) options = WEXITED|WSTOPED|WCONTINUED|WNOHANG|WNOWAIT
 * WIFCONTINUED(status) mac上无效
 * WIFSTOPPED(status) status值应由WSTOPSIG(status)处理，返回引起停止的信号值
 * WIFSIGNALED(status) status值应由WTERMSIG(status)处理，返回引起杀死的信号值
 * WIFEXITED(status) status值应由WEXITSTATUS(status)处理，返回退出值
 * waitpid(pid,status,options) options = WUNTRACED|WCONTINUED|WNOHANG WCONTINUED在mac上无效，由停止状态转变为运行态并不会使该系统调用返回
 * wait(status) 调用时如果此时没有僵死进程，则会阻塞，如果有没回收的僵死进程，则立刻返回
 * atexit(void (*func)(void)) 如果使用_exit()来退出不会执行被登记过的函数
 * _exit(status) 丢弃缓冲区的io数据，直接终止
 * exit(status) 对每个打开流调用fclose()函数，并调用登记过的终止处理函数后终止
 * vfork(void) 因为fork会复制父进程的页表，如果fork后马上就执行exec，那么这个复制是不必要的，所以vfork不会复制父进程的页表，如果vfork后没有立即执行exec，那么子进程实际是在操作父进程的进程空间，vfork会保证子进程先运行,并且在它执行exit或者_exit后父进程才可以被调度
 * fork(void) 当执行fork之后，子进程会复制进程文件描述符表，但不会复制全局文件打开表，因为该表为内核级，当子进程或者父进程其一使用close关闭了该描述符后，另一个仍然可以进行IO操作，子进程一定要以exit退出，特别是在socket并发服务器里，很重要
 * clock_settime(clockid_t,timespec *) 设置时钟值
 * clock_getres(clockid_t,timespec *) 将timespec结构体初始化为clockid_t参数对应的时钟精度，如果精度为1毫秒，则tv_sec字段就是0，tv_nsec字段就是1000000
 * clock_gettime(clockid_t,timespec *) 获取指定时钟的时间 clockid_t = CLOCK_REALTIME|CLOCK_MONOTONIC|CLOCK_PROCESS_CPUTIME_ID|CLOCK_THREAD_CPUTIME_ID 分别表示实时系统时间，不带负跳数的系统实时时间，调用进程的CPU时间，调用线程的CPU时间
 * clock_nanosleep(clockid_t,flags,timespec *,timespec *) flags = 0|TIMER_ABSTIME mac上不可用
 * nanosleep(timespec *,timespec *) 更高精度的睡眠，如果被中断，则在第二个参数中返回未休眠完的时间
 * sleep(seconds) 休眠一段时间，可被信号中断
 * alarm(seconds) 定时器超时后会产生SIGALRM信号，如果seconds为0，并且此前有注册过且还未到期的闹钟，则取消该闹钟并返回剩余时间
 * setitimer(which,itimerval * new,itimerval * old)
 * getitimer(which,itimerval *) which = ITIMER_REAL|ITIMER_VIRTUAL|ITIMER_PROF REAL代表现实时间，VIRTUAL代表用户态时间，PROF为用户态加内核态时间
 *
 *
 * sigvec(sig,sigvec *,sigvec *)
 * sigmask(sig) 将信号值进行转换，变成可以"与"操作的形式
 * sigpause(mask)
 * sigsetmask(mask)
 * sigblock(mask) 写mask的就是要通过sigmask对信号进行转换
 * sigignore(sig)
 * sigrelse(sig)
 * sighold(sig)
 * signalfd(fd,sigset_t *,flags)
 * sigwait(sigset_t * set,int * signop) 如果set中的信号集包含有被阻塞的信号，移除那些被阻塞的信号，函数立刻返回，否则阻塞直到收到集合中的信号(无论信号是否被阻塞)，返回后也不会取消对该信号的阻塞
 * sigsuspend(sigset_t *) 一般在两个sigprocmask之间调用，解除非sigset里所包含信号的阻塞和pause(两个函数为原子操作)，然后函数阻塞直到接收到一个信号(中断sigsuspend里的pause，如果有经sigsuspend调用而解除阻塞的信号，则会立即返回)，之后将信号掩码该为调用sigsuspend之前的掩码，由于信号在被解除阻塞后会立即发送给进程，则如果在调用sigprocmask后想解除阻塞使信号被接收然后调用pause，但这个信号并不会打断pause，因为他在pause运行之前就已经被信号处理程序接收
 * sigqueue(pid,sig,union sigval value) mac不支持
 * sigaltstack(stack_t * new,stack_t * old)
 * abort() 产生SIGABRT信号，设置了信号处理函数也会终止进程，阻塞和忽略该信号也无用
 * setlongjmp(sigjmp_buf,val)
 * sigsetjmp(sigjmp_buf,mode) 如果mode为0，等价于setjmp 在mac os下setjmp可以代替sigsetjmp，会恢复信号掩码，linux则不会
 * pause(void) 阻塞直到接收到一个信号
 * sigaction(signum,sigaction * new,sigaction * old) 切记初始化，将sa_mask设置为空，sa_flags设置为0，尤其是SIGINT sigaction.sa_flags = SA_RESTART|SA_NODEFER|SA_SIGINFO|SA_INTERRUPT 设置SA_RESTART后可在部分文件io被信号中断后进行重启(文件io只有对低速设备操作时才会被中断)，SA_INTERRUPT关闭自动重启(有些操作系统默认中断后自动重启)，SA_SIGINFO让信号处理函数变成void (int,siginfo *,char *)形式
 * sigpending(sigset_t *) 返回当前被阻塞的信号
 * sigprocmask(flag,sigset_t * new,sigset_t * old) flag = SIG_BLOCK|SIG_UNBLOCK|SIG_SETMASK SIG_BLOCK是或操作，SIG_UNBLOCK是&~操作，SIG_SETMASK是赋值操作
 * sigisemptyset(sigset_t *)
 * sigorset(sigset_t * result,sigset_t *,sigset_t *)
 * sigandset(sigset_t * result,sigset_t *,sigset_t *)
 * sigismember(sigset_t *,signum)
 * sigdelset(sigset_t *,signum) 将信号集中的一个信号删除
 * sigaddset(sigset_t *,signum) 向信号集中增加一个信号
 * sigfillset(sigset_t *) 将信号集填充入所有类型的信号
 * sigemptyset(sigset_t *) 将信号集设置为空
 * psignal(signum,meg)
 * strsignal(signum) 返回对该信号描述的字符串指针
 * killpg(gid,signum) == kill(-gid,signum)
 * raise(signum) == kill(getpid(),signum)
 * kill(pid,signum)
 * signal(signum,function) function = SIG_DEL | SIG_IGN | function 调用信号处理程序过程中将阻塞一切信号
 * basename(pathname)
 * dirname(pathname)
 * realpath(pathname) 解析出绝对路径名
 * chroot(pathname)
 * fchdir(fd)
 * chdir(newpath) 改变当前工作目录，会对路径中的符号链接解引用
 * getcwd(buf,size)
 * nftw(dirpath,function,num_of_fd,flags) int funciton(pathname,stat*,typeflag,FTW *)
 * dirfd(DIR *)
 * closedir(DIR *)
 * rewinddir(DIR *)
 * readdir(DIR *)//返回dirent *
 * fdopendir(fd)
 * opendir(dirpath)//返回DIR *
 * remove(pathname)//需要为绝对地址
 * rmdir(pathname)
 * mkdirat(fd,pathname,,pde)
 * mkdir(pathname,mode)
 * readlink(path,buf,size) 直接读符号链接文件的数据，buf中返回的符号链接内容不以null字符结尾
 * symlinkat(filepath,fd,linkpath)
 * symlink(filepath,linkpath)
 * renameat(ofd,oldpath,nfd,newpath)
 * rename(oldpath,newpath) 不对符号链接解引用
 * unlinkat(fd,path,flags) flags = AT_REMOVEDIR 设置该标签可以对目录进行操作
 * unlink(path) 如果path是符号链接，则直接对符号链接起作用
 * linkat(ofd,oldpath,efd,newpath,flags) flags = AT_SYMLINK_FOLLOW 如果设置会对符号链接解引用，不设置会对软链接直接失败
 * link(oldpath,newpath) 等同于ln -n oldpath newpath 该函数会解引用符号链接
 * flistxattr(fd,list,size)
 * llistxattr(path,list,size)
 * listxattr(path,list,size)
 * fremovexatte(fd,name)
 * lremovexatte(path,name)
 * removexatte(path,name)
 * fgetxattr(fd,name,value,size,flag)
 * lgetxattr(path,name,value,size,flag)
 * getxattr(path,name,value,size,flag)//只能在linux下使用，下同
 * fsetxattr(fd,name,value,size,flag)
 * lsetxattr(path,name,value,size,flag)
 * setxattr(path,name,value,size,flag)//只能在linux下使用，下同
 * faccessat(fd,filename,mode,flags) flags = AT_EACCESS 如果设置这个标志则使用有效用户id和有效组id检测访问权限
 * access(path,mode) mode = F_OK|R_OK|W_OK|X_OK 以实际用户id和实际组id检测访问权限，四个选项分别为是否存在，是否有读权限，写权限，执行权限，会对符号链接解引用，使用faccessat并设置AT_SYMLINK_NOFOLLOW也无效
 * fchmodat(fd|-1,filename|pathname,mode,flags) flsgs = AT_SYMLINK_NOFOLLOW 设置该标签不会解引用符号链接
 * fchmod(fd,mode)
 * chmod(pathname,mode) 会对符号链接解引用
 * fchownat(fd|-1,filename|pathname,uid,gid,flags) flags = AT_SYMLINK_NOFOLLOW 设置该标签不会解引用，也就是直接改变符号链接的uid和gid
 * lchown(pathname,uid,gid)
 * fchown(pathfd,uid,gid)
 * chown(pathname,uid,gid) 如果uid或者gid中的任意一个参数是-1，则对应的id不变
 * futimens(fd,timespec [2])
 * utimensat(dirfd,path,timespec [2],flag)
 * lutimes(path,timeval [2]) 不会对符号链接解引用
 * futimes(fd,timeval [2])
 * utimes(path,timeval [2]) 更改访问时间(st_atim)和修改时间(st_mtim), 不能改变st.ctim，因为调用这个函数时，该字段就会自动更新
 * utime(path,utimbuf *)
 * fstatat(fd|-1,filename|pathname,stat *,flags) 如果flags = AT_SYMLINK_NOFOLLOW，等同于lstat，如果fd = AT_FDCWD，并且filename是相对路径名，则fd等同于进程当前工作目录fd
 * fstat(fd,stat * )
 * lstat(path,stat *)//不会对符号链接解引用
 * stat(path,stat *) 检查文件属性，类型，大小，链接数，用户id，组id，最后修改时间，最后访问时间，inode号，占用字节块数量(这里的字节块大小在mac上是512字节，因为一个数据块大小是4K(根据文件系统决定)，所以一个一字节的文件也会占用8个字节块)
 * umount2(target,flag)
 * umount(target)
 * mount(path,target)
 * clearerr(FILE *) 消除FILE中的两个错误标志
 * feof(FILE *) 检测是否已读到文件结尾
 * ferror(FILE *)
 *
 * fseek(fd,offset,whence) whence = SEEK_SET|SEEK_CUR|SEEK_END 改变当前偏移量
 * ftell(FILE *) 返回当前偏移量
 * fwrite(addr,size,num,FILE *) 将地址addr开始的num个size大小的数据写入FILE *流，可用mmap(NULL,40,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0) 加上memcpy实现针对fd的版本
 * fread(addr,size,num,FILE *)
 * puts(buf) 将buf中的数据写到标准输出，并追加一个换行符
 * fputs(buf,FILE *) 将buf中的数据写到指定的流中，数据要以null字符结尾，但是不会向流写入空字符
 * gets(buf) 已经废弃，从标志输入读取并且会在尾部删除换行符
 * fgets(buf,size,FILE *) 一次读取一行数据
 * putchar(char) 等同于putc(char,stdout)
 * fputc(char,FILE *)
 * putc(char,FILE *)
 * ungetc(char,FILE *) 将字符压送回流的最前端
 * getchar(void) 等同于getc(stdin)
 * fgetc(FILE *)
 * getc(FILE *)
 * fclose(FILE *) 关闭一个打开流，关闭之前冲刷缓冲区的数据
 * fdopen(fd,mode) 为fd返回一个流标识符
 * fileno(FIEL *)
 * fmemopen(buf,size,type) 内存流，返回一个文件指针指向这个buf缓冲区，标准io对文件的操作实际上是对磁盘中数据的操作，而这个并不绑定实际的文件，可将buf视为一个文件
 * freopen(pathname,type,FILE *) 在一个指定的流上打开一个指定的文件
 * fopen(FILE *,pathname,type) type = "r+w+a"
 * posix_fadvise(fd,offset,len,advice)
 * fdatasync(fd) 将fd所指文件中被修改过的块缓冲区写入磁盘，等待写入完成后返回
 * fsync(fd) 将fd所指文件中被修改过的块缓冲区和被修改过的文件属性写入磁盘，等待写入完成后返回
 * sync(void) 将修改过的块缓冲区排入写队列，并不等待数据写会磁盘
 * setbuffer(FILE *,buf,size)
 * setbuf(FILE *,buf) 可以用来打开和关闭标准io缓冲，默认是全缓冲模式
 * setvbuf(FILE *,buf,mode,size) mode = _IOFBF|_IOLBF|_IONBF 分别为全缓冲，行缓冲和不带缓冲
 * gethostname(name,len) 返回主机名，等于在终端运行hostname
 * uname(utsname *) 返回主机和操作系统的相关信息
 * fpathconf(fd,name) 获取运行时的系统限制值，与文件和目录有关 name = _PC_*
 * pathconf(path,name) 获取运行时的系统限制值，与文件和目录有关 name = _PC_*
 * sysconf(name) 获取运行时的系统限制值，与文件和目录无关 name = _SC_* _SC_CLK_TCK为每秒滴答数，可用于转换clock_t(times返回值)
 * clock(void)
 * times(struct tms *) tms{tms_utime,tms_stime,tms_cutime,tms_cstime} 分别为用户CPU时间，系统CPU时间，子进程中执行的用户CPU时间，子进程中执行的系统CPU时间，获取各值应该需要调用两次times，用两个tms结构体中对应的各个数相减可得到，可用两次times的返回值相减获取进程实际生存时间，单位为clock_t，可除以_SC_CLK_TCK的值获取实际秒数
 * setpriority(which,who)
 * getpriority(which,who) which = PRIO_PROCESS|PRIO_PGRP|PRIO_USER 分别表示进程，进程组，用户，如果who为0，则表示调用进程的相应which
 * nice(incr) 将insr参数增加到进程的nice值上，nice值越小，优先级越高
 * strptime(buf,format,tm *) strftime的逆函数，将buf中的字符串根据format转换成相应的tm结构
 * strftime(buf,len,format,tm *) 将tm格式化输出
 * asctime(tm *) 将tm转换成人们可读取的时间日期字符串，不会进行本地化处理，所以可用localtime()的返回值作为参数
 * mktime(tm *) 将tm结构中的年月日为参数，转化为time_t值
 * localtime(time_t *) 将日历时间转换成分解的时间结构tm，以本地时间为标准，所以会在对日历时间处理时考虑本地时区和夏令时标志
 * gmtime(time_t *) 将日历时间转换成分解的时间结构tm，以格林时间GMT为标准，返回值为指针类型，说明该函数是不可重入的，tm{tm_sec(0-60),tm_min(0-59),tm_hour(0-23),tm_mday(1-31),tm_mon(0-11),tm_year(>= 1900),tm_wday(0-6),tm_yday(0-365),tm_isdst(夏令时标志)}
 * ctime(time_t *) 将日历时间(time_t)转换成人们可读取的时间日期字符串，会进行本地化处理
 * time(time_t *) 返回自epoch到现在GMT时间的秒数
 * gettimeofday(timeval *,NULL) 与time()功能相似，但是精度更高，timeval.tv_sec和time()的返回值相同，而timeval.tv_nsec提供微秒级精度
 * initgroups
 * setgroups(size,gid_t []) 为调用进程设置附属组id
 * getgroups(size,gid_t []) 将调用进程所属用户的各附属组id写入到数组中，最多写入size个附属组id
 * setfsgid(fsgid)
 * setfsuit(fsuid)
 * getresgid(&uid,&euid,&suid)
 * getresuid(&uid,&euid,&suid) mac上无法使用
 * setregid(gid,egid)
 * setreuid(uid,euid) 如果是特权进程，将实际用户id设置为uid，有效用户id和保存的设置用户id设置为euid，参数取-1对应id可保存不变
 * setegid(egid)
 * seteuid(euid) 如果是特权进程，只更改有效用户id为uid，非特权进程可以将有效用户id改为实际用户id或保存的设置用户id
 * setgid(uid)
 * setuid(uid) 如果进程拥有特权进程权限，则可以将实际用户id，有效用户id和保存的设置用户id改为uid，如果非特权进程，而uid等于实际用户id或者保存的设置用户id，则可以将有效id也改为uid，比如某些设置了set-user-id为root的程序，当进程运行后，有效id为root，保存的设置用户id也为root，如果不进行某些操作，这个程序会一直以特权进程运行，此时可以用setuid(getuid())将有效用户先设为实际用户id，以用户权限运行，等到运行需要某些特权的命令时再用setuid(程序刚运行时geteuid()的有效用户id)，调用完命令后再将有效用户id恢复，保证最小权限原则
 * getegid() 返回有效组id
 * getgid() 返回实际组id
 * geteuid() 返回有效用户id
 * getuid() 返回实际用户id
 * getlogin() 返回登陆名，可以用getpwuid(getuid())得到，不过如果一个用户有多个登录名(多用登录名对应一个uid)，则可能不会得到想要的结果
 * crypt(pass,salt)
 * endspent(void)
 * setspent(void)
 * getspend(name)
 * getspname(name)
 * getgrent(void) 关闭打开的/etc/group文件
 * setgrent(void) 从初始处开始遍历，即重置指针，或者说将偏移量设为0
 * endgrent(void) 遍历/etc/group，每次调用后会指向下一条记录，会在第一次调用的时候打开/etc/group文件
 * endpwent(void) 关闭打开的/etc/passwd文件
 * setpwent(void) 从初始处开始遍历，即重置指针，或者说将偏移量设为0
 * getpwent(void) 遍历/etc/passwd，每次调用后会指向下一条记录，会在第一次调用的时候打开/etc/passwd文件
 * getgrgid(uid) 通过uid进行匹配
 * getgrnam(name) 返回group *，获取/etc/group中匹配name的信息
 * getpwuid(uid) 通过uid进行匹配
 * getpwnam(name) 返回passwd *，获取/etc/passwd中匹配name的信息
 * alloc(size)
 * memalign(boundary,size)
 * realloc(ptr,size)
 * calloc(num,size)
 * malloc(size)
 * brk(void *)
 * sbrk(size)
 * brk(void * position)
 * longjmp(jum_buf,val) 调用时会跳转到setjmp函数处，不会回滚全局变量和自动变量的值，如果值保存在寄存器中，则值最后会回滚到调用第一次setjmp时的值，如果不想其回滚，则设置修饰符volatile
 * setjmp(jum_buf) 参数应该为全局变量，第一次调用返回0，第二次调用会返回longjmp里的val参数
 * clearenv(void)
 * unsetenv("name") 删除环境变量
 * setenv("name","value",overwrite) overwrite = TRUE|FALSE 等于true则覆盖，否则不覆盖
 * putenv("name=value") 参数为真实的环境变量，不是副本，如果采用char []保存字符串，则可以通过该指针进行后续更改，如使用静态分配，则不可更改
 * getenv("name") 返回真实地址，不是拷贝
 * tmpfile(void) 返回创建的临时文件的流指针
 * mkdtemp(buf[] = "nameXXXXXX") 创建的是目录
 * mkstemp(buf[] = "nameXXXXXX") 不能传递静态分配的参数，程序结束后不会自动删除该文件
 * ftruncate(fd,len) 可用于增大文件大小，然后用memcpy复制mmap的数据
 * truncate(path,len) 如果len大于文件大小，则会形成文件空洞
 * writev(fd,struct iovec *,len)
 * readv(fd,struct iovec *,len)
 * pwrite(fd,buf,len,offset) 不更新当前的文件偏移量
 * pread(fd,buf,len,offset) 从fd的第offset的偏移量处读取len个字节的数据，不更新当前的文件偏移量
 * dup2(oldfd,newfd) 复制oldfd到newfd，如果newfd以及被占用，则会先用close关闭它，复制后文件描述符设置的close-on-exec位会消失
 * fcntl(fd,cmd,attr) cmd = F_GETFL|F_SETFL|F_GETFD|F_SETFD|F_DUPFD|F_F_DUPFD_CLOEXEC|F_GETOWN|F_SETOWN F_SETFD是设置文件描述符标志(进程文件描述符表中,FD_CLOEXEC标志)，F_SETFL是设置文件状态标志(全局文件打开表中)，F_DUPDF是复制文件描述符但不会复制F_CLOEXEC标志，F_DUPDF_CLOEXEC则会设置F_CLOEXEC
 * lseek(fd,offset,position)
 * write(fd,buf,len) 可以对文件写大量的0，并且会占用空间，而如果是偏移后写数据，中间的空洞不会占据空间(视系统而定，mac占用)，但是如果复制这个文件，复制的空洞部分会被0填充，因为read函数读取空洞部分读出的数据是0，利用文件空洞可以实现多线程下载
 * aio_read(aiocb *)
 * read(fd,buf,len) 文件空洞是可以读的，只不过读到的数据是0
 * close(fd) 只是进程文件描述符中对应的记录，并将fd所对应的全局文件打开表表项中的标记减一，当标记为0是文件关闭
 * openat(fd|-1,filename|pathname,flags,mode) fd指向filename的目录，或者等于AT_FDCWD，则fd等同于进程当前工作目录fd
 * open(path,flag,mode) flag = O_RDONLY|O_WRONLY|O_RDWR|O_APPEND|O_CLOEXEC|O_CREAT|O_DIRECTORY|O_EXCL|O_NOCTTY|O_NOFOLLOW|O_NONBLOCK|O_SYNC|O_TRUNC|O_DSYNC|O_FSYNC
 *
 *
 * 开头为l为不对符号链接解引用，直接操控符号链接文件的inode目录项
 */
