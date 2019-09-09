//
// Created by 邓岩 on 12/03/2017.
//
// mac是小端机器，实验方法，在int中存入一个较大的数字，如Ox1f2f3f4f，然后定义一个指针指向该整形，将指针强制转换为char *后将后三个字节写为0，再次输出该数字，输出79，说明4f被存入最低地址的内存
# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include "unix_socket_api.h"
//# include <GLUT/GLUT.h>

static jmp_buf env;

extern char ** environ;

void printWaitStatus(char * msg,int status);
void printSigset(FILE * io,const char * prestr,const sigset_t * sigset);
void printSigmask(FILE * io,const char * msg);
void printPending(FILE * io,const char * msg);
int lock_reg(int fd,int cmd,int type,off_t offset,int whence,off_t len);


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
    signal(SIGTSTP,SIG_DFL);//将信`号处理程序恢复成默认处理
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
    if(sig == SIGPIPE)
        printf("sigpipe receive\n");
    //while(i = read(fd,sbuf,100))
    //    write(STDOUT_FILENO,sbuf,i);
}

sigset_t mask;
int quitflag;

void * f1(void * arg)
{
    int err,signo;
    for(;;)
    {
        err = sigwait(&mask,&signo);
        if(err != 0)
            exit(-1);
        switch (signo)
        {
            case SIGINT:
                printf("\n interrupt \n");
                break;
            case SIGQUIT:
                pthread_mutex_lock(&mutex);
                quitflag = 1;
                pthread_mutex_unlock(&mutex);
                pthread_cond_signal(&cond);
                break;
            default:
                printf("unexpected signal %d\n",signo);
                exit(1);
        }
    }
}

struct {
    int a:1;
};

#define SOCK_PATH "/Users/dengyan/"

void alarm_handler(int a)
{
    return;
}

#define	CMGROUP_MAX 16

struct cmsgcred {
    pid_t	cmcred_pid;		/* PID of sending process */
    uid_t	cmcred_uid;		/* real UID of sending process */
    uid_t	cmcred_euid;		/* effective UID of sending process */
    gid_t	cmcred_gid;		/* real GID of sending process */
    short	cmcred_ngroups;		/* number or groups */
    gid_t	cmcred_groups[CMGROUP_MAX];	/* groups */
};

//Todo:--------------------------------------------------------------------------main----------------------------------------------------------------------
int main(int argc, char *argv[]) {
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/Users/dengyan/serve");
    struct ifconf a;
    struct ifreq b;

    int p[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, p);

    struct cmsgcred cred;
    struct msghdr msg;
    struct iovec iov[1];
    int controllen = CMSG_LEN(sizeof(int));
    char controlbuf[controllen];
    printf("%d\n", controllen);

    bzero(&msg, sizeof(msg));
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iovlen = 1;
    msg.msg_iov = iov;
    msg.msg_control = controlbuf;
    msg.msg_controllen = controllen;
    msg.msg_flags = 0;

    struct cmsghdr * cmptr = controlbuf;
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS;
    cmptr->cmsg_len = controllen;
    *(int *)CMSG_DATA(cmptr) = fd;

    iov[0].iov_base = "1";
    iov[0].iov_len = 1;

    //if (connect(fd, (struct sockaddr *)&addr, SUN_LEN(&addr)) < 0)
    //    err_sys("connect error");

    //pause();
    int n = sendmsg(p[0], &msg, 0);
    printf("%d, %s", n, strerror(errno));
    return 0;
}
//Todo:--------------------------------------------------------------------------main----------------------------------------------------------------------


/*
 *     setbuf(stdout, NULL);
    struct msghdr mv;
    struct sockaddr_un un;
    char buf[1000];
    int fd[2];
    int pid;
    char maze[20][20];
    socketpair(AF_UNIX, SOCK_DGRAM, 0, fd);
    if((pid = fork()) == 0) {
        if (dup2(fd[0],0) != 0) {
            printf("error %s",strerror(errno)); //0读
            exit(-1);
        }
        close(fd[0]);
        if (dup2(fd[1],1) != 1) {
            printf("error %s",strerror(errno)); //1写
            exit(-1);
        }
        close(fd[1]);
        execlp("/Users/dengyan/PycharmProjects/Py/Maze.py",(char *)(0));
    } else { //1写 0读
        int i;
        int n = 0;
        while (i = read(fd[0], buf, 100)) {
            if(!strncmp(buf,"Please enter any key to exit",i))
                break;
            memcpy(maze[n++],buf,i - 1);
        }
        for (int j = 0; j < 20; ++j) {
            for (int k = 0; k < 20; ++k) {
                printf("%c ", maze[j][k]);
            }
            printf("\n");
        }
        getchar();
        write(fd[1],"w\n",2);
    }
 */

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
 * ((int)&((struct sockaddr_un *)0)->sun_path) 可用于计算结构体内成员偏移量，等价于offsetof
 * aio系列函数，已跳过
 * fcntl(int fd,F_SETFL,flags|O_ASYNC) 设置信号IO，通过fcntl(fd,F_SETOWN,pid)设置接收SIGIO的进程，不能对终端设备使用
 * poll(pollfd[],int nfds,int timeout) pollfd{int fd,short events,short revents} events = POLLIN|POLLRDNORM|POLLRDBAND||POLLPRI|POLLOUT|POLLWRNORM|POLLWRBAND，POLLERR|POLLHUP|POLLNVAL这三个值即使不设置在events中，也可能出现在revents ，nfds指数组元素的个数，timeout为-1时永久等待，为0时测试后立即返回，其余值时为等待timeout毫秒， POLLIN可以不阻塞的读取高优先级数据以外的数据，POLLRDNORM。可以不阻塞的读取普通数据，POLLRDBAND，可以不阻塞的读取优先级数据，可以不阻塞的读取高优先级的数据，POLLOUT，可以不阻塞的写普通数据，POLLWRNORM，同POLLOUT，POLLWRBAND，可以不阻塞的写优先级数据，POLLERR，已出错，POLLHUP，已挂断，POLLNVAL，描述符没有引用一个打开文件
 * FD_ZERO(fdset * fdset) 将一个fdset的所有位置为0
 * FD_SET(int fd,fdset * fdset) 将fd加入fdset
 * FD_CLR(int fd,fdset * fdset) 将fd从fdset中移除
 * FD_ISSET(fd,fd_set * fdset) 若fd在fdset中，返回非0，否则返回0，可用于当select返回后判断fd的状态
 * pselect(nfds,fd_set * readset,fd_set * writeset,fd_set * errorset,timespec * intval,sigset_t * sigmask) 行为类似于select，但提供了sigmask参数用于当函数调用期间设定的信号屏蔽字，当返回时恢复屏蔽信号字
 * select(int nfds,fd_set * readset,fd_set * writeset,fd_set * errorset,timeval * intval) io多路复用，等待一定长的时间，返回已准备好的文件描述符个数，nfds为当前最大的文件描述符加1，这样就只会检查小于nfds的文件描述符状态，intval等于NULL时，永远等待，直到指定中的一个文件描述符已准备好或者捕捉到一个信号终端此进程，intval->tv_sec==0&&intval->tv_usec==0，不等待，测试所有文件描述符后立即返回，当intval有其他值时，等待指定的描述和微妙数，当指定描述符中的一个文件描述符准备好时，或者超过指定时间，则立即返回，readset，writeset，errorset分别返回所关心描述符状态的结果，每一个位对应一个描述符，当调用完成后，若对应位为1，则表示该下标对应的描述符为准备好状态，如设置为NULL，则表示对该状态不关心
 * ttyname(fd) 返回这个文件描述符相关联的终端名称
 * isatty(fd) 判断文件描述符是否同一个终端相关联
 * ctermid(buf) 返回进程控制终端的名称
 * ioctl(fd,TIOCGWINSZ,winsize *)
 * tcsetattr(fd,option,termios *) option = TCSANOW|TCSADRAIN|TCSAFLUSH 分别为修改立即生效，等处理完终端输出缓冲区的数据后生效，抛弃终端输入缓冲区的数据然后生效
 * tcgetattr(fd,termios *)
 * ioctl(fd,FIONREAD,&cnt) 获取接收缓冲区中的未读取字节数(套接字，文件，管道，终端)
 * ----------终端IO----------
 *
 * CMSG_DATA(struct cmsghdr * cp)->(unsigned char *) 返回一个指针，指向与cmsghdr相关联的数据，内部实现就是(unsigned char *)cp + sizeof(struct cmsghdr)
 * CMSG_FIRSTHDR(struct msghdr * mp)->(struct cmsghdr *) 返回一个指针，指向与msghdr结构相关联的第一个cmsghdr结构，若无这样的结构，返回NULL
 * CMSG_NXTHDR(struct msghdr * mp, struct cmsghdr * cp)->(struct cmsghdr *) 返回一个指针，指向与msghdr结构相关联的下一个cmsghdr结构，若当前的cmsghdr已是追后一个，返回NULL
 * CMSG_LEN(unsigned int nbytes)->(unsigned int) 返回头部加nbytes的空间大小，内部实现就是sizeof(struct cmsghdr) + nbytes
 * recvmsg(int sockfd,msghdr * msg,int flag) 可以看作是使用套接字的readv, 接受数据后，msghdr中的msg_flags元素的可能值有MSG_CTRUNC|MSG_EOR|MSG_ERRQUEUE|MSG_OOB|MSG_TRUNC MSG_CTRUNC表示控制数据被截断，MSG_EOR表示接受记录结束符，MSG_ERRQUEUE表示接受错误信息作为辅助数据，MSG_OOB表示接受带外数据，MSG_TRUNC表示一般数据被截断
 * sendmsg(int sockfd,msghdr * msg,int flag) 可以看作是使用套接字的writev，msghdr{void * msg_name(地址); socklen_t msg_namelen(地址字节数); iovec * msg_iov IO(缓冲数组); int msg_iovlen(数组中的元素个数); void * msg_control(指向控制信息头); socklen_t msg_controllen(控制信息的长度); int msg_flags(接受数据的标志)}，msghdr.control实际上是一个指向cmsghdr的指针，cmsghdr{socklen_t cmsg_len; int cmsg_level; int cmsg_type} 为了发送文件描述符，将cmsg_len设置为cmsghdr结构的长度加一个整形的长度(描述符的长度)，cmsg_level字段设置为SOL_SOCKET，cmsg_type设置为SCM_RIGHTS，用以表明在传送访问权(SCM是套接字级控制信息的缩写)，访问权限仅能通过UNIX域套接字发送，描述符仅随cmsg_type后存储
 * setsockopt(int sockfd,int level,int optname,&optval,len) 如果针对的是通用的套接字，将level指定为SO_SOCKET，optname = SO_REUSEADDR 这里我只写了一个常用用法，地址复用，能让服务器重启时立即再次绑定同一个地址，optval此时可以是一个指向整数的指针，len表示optval指向数据的大小
 * getsockopt(sockfd,level,optname,&optval,&len) level = SOL_SOCKET optname = SO_REUSEADDR 获取套接字属性
 * getpeername(int sockfd,sockaddr * addr,&len) 获取套接字socket对端主机的地址信息并写到addr中，len表示缓冲区的大小，函数返回后len的值会变为向addr写入的字节数
 * getsockname(int sockfd,sockaddr * addr,&len) 获取套接字socket所绑定的地址信息并写到addr中，len表示缓冲区的大小，函数返回后len的值会变为向addr写入的字节数
 * sendfile(fd,sockfd,&offset,len) mac上未成功，且mac上有六个参数
 * gethostbyaddr() 已过时
 * gethostbyname(port,char * protocal) 已过时
 * getservbyhost(char * name,char * protocal)
 *
 * getnameinfo(sockaddr *,addrlen,char * host,hostlen,char * service,servlen,flags) flags = NI_DGRAM|NI_NAMEREQD|NI_NOFQDN|NI_NUMERICHOST|NI_NUMERICSERV NI_DGRAM服务基于流而非数据报，NI_NAMEREQD如果找不到主机名，将其作为一个错误对待，NI_NUMERICHOST返回主机地址的数字形式，NI_NUMERICSERV返回服务地址的数字形式(即端口号)
 * gai_strerror(int error) 如果getaddrinfo失败，使用此函数将getaddrinfo的返回值转换成错误信息
 * freeaddrinfo(addrinfo *) 一般用于释放getaddrinfo第四个参数指向的addrinfo结构
 * getaddrinfo(char * host,char * service,addrinfo * hint,addrinfo ** res) 需要提供主机名，服务名或者两者都提供，如果仅仅提供一个，另一个必须是一个空指针，主机名可以是一个节点名或者点分形式，addrinfo{int ai_flags; int ai_family; int ai_socktype; int ai_protocol; int ai_addrlen; int ai_canonname; sockaddr * ai_addr,addrinfo * ai_next} ai_family = AF_INET|AF_INET6|AF_UNSPEC 意义为获取哪种地址结构 ai_flags = AI_ADDRCONFIG|AI_ALL|AI_NUMERICHOST|AI_NUMERICSERV|AI_PASSIVE|AI_V4MAPPED  AI_ADDRCONFIG表示查询配置的地址类型，AI_ALL表示查找IPC4和IPV6(IPV6需要指定AI_V4MAPPED)，AI_NUMERICHOST表示以数字格式指定主机地址，AI_NUMERICSERV表示以数字形式(端口号)指定服务
 *
 *
 * endservent() 关闭文件
 * getservent()->(struct servent *) 获取文件下一条目
 * setservent(int stayopen) 打开端口绑定的服务名和端口号信息文件，mac上即/etc/services文件
 * getservbyport(int port,char * proto)->(struct servent *) port表示端口号，proto表示协议名，根据端口名(如23，需要使用网络序)和协议名(tcp)查询信息
 * getservbyname(char * name,char * proto)->(struct servent *) servent(char * s_name; char ** s_aliases; int s_port(网络序); char * s_proto) name表示服务名，proto表示协议名，根据服务名(如ssh)和协议名(如tcp)查询信息
 * ----------端口名和端口号信息文件----------
 *
 * endprotoent() 关闭文件
 * getprotoent()->(struct protoent *) 获取文件下一条目
 * setprotoent(int stayopen) 打开网络协议和网络号信息文件
 * getprotobynumber(int proto)->(struct protoent *) 根据协议号获取协议相关信息
 * getprotobyname(char * name)->(struct protoent *) protoent{char * p_name; char ** p_aliases; int p_proto} 根据协议名获取协议相关信息，如参数为"ip"
 * ----------协议名和协议号信息文件----------
 *
 * endnetent(void)
 * getnetent()->(struct netent *)
 * setnentent(int stayopen)
 * getnetbyname(char * name)->(struct netent *)
 * getnetbyaddr(uint32_t net,int type)->(struct netent *) netent{char * n_name; char ** n_aliases; int n_addrtype; uint32_t n_net(网络序)} 以下五个函数应该是针对本机上ip地址名和ip地址，如LOOPBACK和7f(这里是网络序)
 * ----------IP别名和IP地址信息文件----------
 *
 * endhostent(void) 关闭网络配置信息文件
 * gethostent(void)->(struct hostent *) 返回文件中的下一个条目 hostent{int h_addrtype;char * h_name;char ** h_addr_list;char ** h_aliases;int h_length}
 * sethostent(int statopen) 打开文件网络配置信息文件，如果已打开文件，会将读取的偏移量置为0，如果statopen非0，调用gethostent后文件仍然保持打开状态，mac上打开的是/etc/hosts文件，返回的地址为网络字节序
 * ----------主机网络配置信息文件----------
 *
 * inet_ntop(int domain,in_addr|in6_addr *,char * str,socklen_t addrlen)->(char *) domain = AF_INET|AF_INET6 有网络形式转换成表现形式，即整形数字转换成点分十进制字符串，注意：此函数将参数视为网络字节序转换成字符串，所以对于小端法机器，如果你想要提供自己的参数给它，可以先使用htonl再进行传递
 * inet_pton(int domain,char * str,in_addr|in6_addr *) domain = AF_INET|AF_INET6 由表现形式转换成网络形式，即点分十进制字符串转换成二进制数字，注意：此函数转换时会考虑本机的大小端特性
 * inet_ntoa(char *,in_addr *) 只能用于IPv4，已过时
 * inet_aton(in_addr) 只能用于IPv4，已过时
 * ----------网络序和点分十进制之间的转换----------
 *
 * ntohl(int)
 * ntohs(short)
 * htonl(int)
 * htons(short) h代表主机(host)，n代表网络(network)，l代表32位，s代表16位，表示在主机字节序与网络字节序之间进行转换
 * ----------网络序和主机序转换----------
 *
 * socketpair(domain,type,protocal,int [2]) 前三个参数类似socket，第四个参数类似于pipe，生成两个连接着的unix域的socket套接字，domain = AF_UNIX|AF_INET|AF_INET6 虽然结构足够通用，允许socketpair用于其他域，但一般来说操作系统仅对unix域提供支持，type = SOCK_STREAM|SOCK_DGRAM 分别为字节流和报文，unix域的数据报是可靠的，既不会丢失报文也不会传递出错，unix域套接字更像是套接字和管道的结合，一对相互连接的套接字可以起到全双工管道的作用，两端对读和写开放，由于创建的套接字没有名字，所以不能在无关进程中使用，如需要不同进程间通讯需要使用socket函数
 * recvfrom(int sockfd,void buf,size_t length,int flags,sockaddr * addr,&addrlen) 带有获取发送者信息功能的recv，将发送者的地址信息写入addr，addrlen表示缓冲区的大小，当函数返回时将len改为向缓冲区写入的字节数
 * sendto(int sockfd,void * buf,size_t length,int flags,sockaddr * addr,addrlen) 可用于发送报文，通过addr指定目标地址，如过sockfd有连接，那么无视addr
 * recv(int sockfd,void * buf,size_t len,int flags) flags = MSG_DONTWAIT|MSG_OOB|MSG_PEEK|MSG_WAITALL MSG_DONTWAIT此次调用不会阻塞，MSG_PEEK获取sockfd缓冲区中数据的一份副本，不会将数据从缓冲区移除，MSG_WAITALL直到等待接受到len个字节后才会返回
 * send(int sockfd,void * buf,size_t len,int flags) 使用时套接字必须已经连接，类似于write，但可以指定标志来改变处理传输数据的方式 flags = MSG_DONTWAIT，MSG_DONTWAIT使用非阻塞操作
 * shutdown(sockfd,flags) flags = SHUT_RD|SHUT_WR|SHUT_RDWR SHUT_RD为关闭读端，那么无法从套接字读取数据，SHUT_WR为关闭写端，表示无法用套接字发送数据，SHUT_RDWR则既无法读取也无法发送，由于套接字的close命令并不一定能直接关闭socket(比如通过dup复制了描述符)所以使用shutdown可以避免这个问题，而且使用shutdown能够使用单向通讯
 * connect(sockfd,sockaddr *,addrlen) 如果要处理一个面向连接的网络服务(SOCK_STREAM或SOCK_SEQPACKET)，那么在开始交换数据之前，需要在请求服务的进程套接字和提供服务的进程套接字之间建立一个连接，如果sockfd没有绑定到一个地址，connect会给调用者绑定一个默认地址，如果connect失败，在部分系统上套接字会变成未定义的，最好是关闭套接字，新建一个套接字后再进行connect操作，当在一个数据报socket上使用connect后，可以使用read和write操作描述符
 * accept(int sockfd,sockaddr * addr,&addrlen) 获得sockfd监听的连接请求并建立连接，返回一个套接字描述符，此描述符连接到客户端调用connect的进程，并将请求连接端的地址信息写入addr中，len参数为缓冲区的大小，函数返回时，会将len改为向缓冲区写入的字节数，如果不关心对端机器的地址信息，可以将addr和len置为NULL，如果sockfd是非阻塞且当前没有连接请求，accept会退出并返回-1，否则将阻塞直到收到一个连接请求(阻塞模式)
 * listen(int sockfd,int backlog) 将sockfd指定为监听套接字，此后此套接字能接收到连接请求，backlog用于限制发起请求连接的数量，一旦未处理连接等于backlog，系统就会拒绝多余的连接请求
 * bind(int sockfd,sockaddr * addr,int addrlen) sockaddr = sockaddr_un(AF_UNIX)|sockaddr_in(AF_INET)|sockaddr_in6(AF_INET6) addrlen要根据使用的sockaddr来确定，不能使用sizeof(struct sockaddr)，sockaddr{unsigned char sa_len;sa_family_t sa_family; char sa_data[14]} sockaddr_un{unsigned char sun_len; sa_family_t sun_family; char sun_path[104](用于创建套接字的文件名，该文件仅用于向客户客户进程告示套接字名字，无法打开，也不能由应用程序进行通讯)}当sun_path指定的文件已存在时，bind会失败，也就是说该文件是一次性的，程序结束时就应该删除该文件，每次bind时都要保证该文件不存在， sockaddr_in{unsigned char sin_len; sa_family_t sin_family; in_port_t sin_port; struct in_addr sin_addr; unsigned char sin_zero[8]} struct sin_addr{in_addr_t(无符号32位整形) s_addr}
 * socket(domain,type,protocal) domain = AF_UNIX|AF_INET|AF_INET6 分别为UNIX域，Ipv4因特网域，Ipv6因特网域 type = SOCK_STREAM|SOCK_DGRAM|SOCK_SEQPACKET|SOCK_RAW 分别为流(TCP),报文(UDP),可靠传输的UDP,IP协议的数据报接口 protocal通常为0，INADDR_LOOPBACK(0x7f000001)为IPV4回环地址，INADDR_ANY(0x0)为IPV4通配地址，均为整形数据，IN6ADDR_LOOPBACK_INIT为IPV6回环地址，IN6ADDR_ANY_INIT为IPV6通配地址，为结构体类型
 * ----------套接字API----------
 *
 * fcntl(fd,cmd,flock *) cmd = F_SETLK|F_SETLKW|F_GETLK 分别为设置锁，非阻塞操作设置锁，检测锁，flock{l_type,l_whence,l_start,l_len,l_pid} l_type = F_RDLCK|F_WRLCK|F_UNLCK 分别为设置读锁(共享锁)，写锁(互斥锁)，解锁，该函数放置锁需要与文件的打开模式相对应，即需要放置两种锁时，文件的打开模式应该为O_RDWR l_start = SEEK_SET|SEEK_CUR|SEEK_END l_whence为偏移量 l_len为长度，,当len为0时，表示锁的范围可以拓展到最大可能偏移量(无论此后追加写入了多少数据)，l_pid当cmd为F_GETLK时有效，返回拥有该锁的进程id，单个进程在某一时刻只能对一个文件区间拥有一把锁。多次加锁会覆盖上个锁
 * flock(fd,flags) flags = LOCK_SH|LOCK_EX|LOCK_UN|LOCK_NB LOCK_SH为设置共享锁，LOCK_EX为设置互斥锁，LOCK_UN为解锁，LOCK_NB为执行非阻塞操作，无论对文件的访问模式是只读，只写或是读写都可以在上面放置共享锁和互斥锁，该函数的操作单位为整个文件，并且flock的锁转换非原子操作，它是先解锁，然后上锁，在解锁和上锁之间可能会有其他进程的上锁请求成功执行，此时该函数会阻塞，并且原本拥有的锁丢失
 * madvise(addr,length,flags) flags = MADV_NORMAL|MADV_RANDOM|MADV_SEQUENTIAL|MADV_WILLNEED|MADV_DONTNEED
 * mincore(addr,length,char vec[]) 无论是产生何种映射，包括私人匿名映射(堆分配)，并不会立即为这些映射分配相应的内存，需要访问相应的虚拟内存产生缺页错误后才会进行分配
 * munlockall(void)
 * mlockall(flags) flags = MCL_CURRENT|MCL_FUTURE MCL_CURRENT将进程的虚拟内存中当前所有映射的分页全部锁进内存，MCL_FUTURE将后续映射到虚拟内存中的所有分页锁进内存
 * munlock(addr,length) 解锁以页为单位，当对同一页进行多次上锁也只会产生一次效果，某页的上锁属性应该保存在进程的该页的映射数据结构中，如果多个进程共享映射同一组分页时，只要还存在一个进程持有这些分页上的内存锁，那么这些分页就会保持被锁进内存的状态
 * mlock(addr,length) 当调用完成后，即使映射的地址区域当前不在区域内，也会在该函数返回前将该区域换进内存，而不需要等待发生缺页
 * mprotect(addr,length,flags) flags = prot = PROT_NONE|PROT_READ|PROT_WRITE|PROT_EXEC 用于更改保护位，addr必须是系统页长的整数倍
 * msync(addr,length,flags) 将页写回硬盘，flags = MS_SYNC|MS_ASYNC|MS_INVALIDATE 分别为同步更新，异步更新，通知系统丢弃那些与底层存储器没有同步的页
 * munmap(addr,length) 解除映射区，如果是私人映射，那么映射区的数据会被丢弃
 * mmap(addr,length,prot,flags,fd|-1,offset) prot = PROT_NONE|PROT_READ|PROT_WRITE|PROT_EXEC PROT_NONE表示映射区不可访问，PROT_READ表示映射区可读，PROT_WRITE表示映射区可写，PROT_EXEC表示映射区可执行，如果要写文件，则应该设置PROT_READ|PROT_WRITR并且打开文件时应该指定标记O_RDWR，映射文件时size不能超过文件的大小(可用lseek加write或者ftruncate增加文件大小) flags = MAP_PRIVATE|MAP_SHARED|MAP_ANONYMOUS|MAP_FIXED|MAP_NORESERVE PROT_NONE表示区域无法访问，MAP_PRIVATE表示创建私人映射，会创建一份副本，对数据的改变不会影响源文件，MAP_SHARED表示创建共享映射，存储操作等于对文件调用write，MAP_ANONYMOUS表示创建匿名映射，私人匿名映射类似堆分配(但是没有堆分配时块与块之间的联系)，共享匿名映射就是共享内存分配，MAP_FIXED表示不对addr参数进行处理，否则会将addr参数向上取整为分页大小的倍数，此时会对addr地址强行进行映射，还能覆盖该地址之前的映射
 * ----------内存映射----------
 *
 * shmctl(shmid,cmd,shmid_ds *) cmd = IPC_RMID|IPC_STAT|IPC_SET  IPC_RMID用于删除此共享内存段，标示符会立即删除，所以不能再用shmat进行该段的连接，但是该内存段不会立即删除，只有当引用此共享内存段的计数变为0后才会真正删除该段，IPC_STAT用于获取此段的属性，IPC_SET为设置，shmid_ds{shm_perm(权限设置) shm_segsz(共享存储的段大小); shm_lpid(最后进行op操作的pid); shm_cpid(创建者的pid?); shm_nattch(当前共享此区域的进程数量); shm_atime(最后一次访问的时间); shm_dtime(最后一次分离此内存段的时间); shm_ctime(最后一次改变的时间)}
 * shmdt(addr) 接触对addr开始的内存共享段的映射，并将共享内存段的引用计数减一
 * shmat(shmid,addr,flags) flags = SHM_RND|SHM_RDONLY 分别为将addr的值自动四舍五入到页面大小的倍数，将内存块以只读方式装载到调用进程的虚拟内存，如果addr为0则不需要用SHM_RND，系统会自动将共享内存块映射到可用的地址上
 * shmget(key,size,flags) flags = IPC_CREAT|IPC_EXCL|0755 当创建一个新段时，size指定需要的大小，当引用一个已经存在的段时，则指定为0
 * ----------共享内存----------
 *
 * semctl(semid,semnum,cmd,...union semun) 注意：联合体参数不是指针类型，semnum表示第几个信号量，从0开始，部分cmd操作对此参数没有要求，cmd = IPC_RMID|IPC_STAT|IPC_SET|GETVAL|SETVAL|GETALL|GETPIC|GETNCNT|GETZCNT semun{int val(用于SETVAL); semid_ds * buf(用于IPC_STAT以及IPC _SET); unsigned short * array(用于GETALL以及SETALL)} IPC_RMID用于删除信号量集，IPC_STAT用于获取获取该信号量集关联的数据结构，IPC_SET用semun->semid_ds的属性更新该信号量集关联的数据结构，GETVAL返回由semid指定的第semnum个信号量的值，SETVAL将第semnum个信号量设置为semnu->val，GETALL将信号量集中的值设置为semun->array[]，SETALL为设置，semid_ds{sem_perm(权限信息); sem_nsems(信号量的个数); semds.sem_otime(最后一次op操作的时间); semds.sem_ctime(最后一次修改时间)}
 * semop(semid,sembuf *,flags) sembuf{unsigned short sem_num(指定信号),short sem_op(进行的操作),short sem_flg} sem_flg = IPC_NOWAIT|SEM_UNDO SEM_UNDO用于如果某进程占用了信号量的资源，但是当它结束时，进程占用的信号量值并不会释放，指定SEM_UNDO可以解决这个问题，当进程结束时，将其占用的信号量恢复 若sem_op为正值，则将此值加到对应的信号量上，若sem_op为负值，则表示要获取由该信号量控制的资源，如果该信号量的值大于等于sem_op的绝对值，则直接从信号量值中减去，否则，若指定了IPC_NOWAIT，则直接出错返回EAGIN，若没有指定，则该信号量的semncnt值+1，然后调用进程被挂起知道以下行为发生，此信号量的值变成大于了sem_op的绝对值，则从该信号量值减去sem_op的绝对值，然后继续运行，收到信号，并从信号处理程序返回，semncnt减1，函数出错并设置EINTR，或者此信号量被删除，出错返回EIDRM，若sem_op等于0，则表示调用进程希望等待该信号量变为0，具体情况类似于sem_op小于0，当该操作阻塞时，即减少信号量值导致信号量小于0时，此时如果被信号中断，该操作不会自动重启，
 * semget(key,nsems,flags) flags = IPC_CREAT|IPC_EXCL|O755 nsems是该集合中的信号量数，如果是创建新集合，就必须指定nsems，否则将其指定为0，表示引用一个已经存在的集合，注意：创建时需要指定权限，信号量使用一个未命名结构体 struct{unsigned short semval(信号量的值); pid_t sempid(最后操作此信号量的pid); semncnt(等待此信号量的值大于针对此信号调用semop时所指定sem_op绝对值的进程数量，可以直接理解为阻塞在该信号量的数量); semzcnt(等待此信号量变为0的进程数量)}
 * ----------信号量----------
 *
 * msgctl(int msqid,cmd,msqid_ds *) cmd = IPC_RMID|IPC_STAT|IPC_SET 分别为删除消息队列以及其中的数据，获取msqid对应的msqid_ds属性，设置msqid对应的msqid_ds属性，msqid_ds{ipc_perm msg_perm; msgqnum_t msg_qnum(剩余消息数量); msglen_t msg_qbytes(队列容量);msglen_t cbytes(当前队列存在的数据量); pid_t msg_lspid(最后发送消息进程的pid); pid_t msg_lrpid(最后接受消息进程的pid); time_t msg_stime(最后发送消息的时间); time_t msg_rtime(最后接受消息的时间); time_t msg_ctime(队列最后改变的时间)}
 * msgrcv(int msqid,void *,maxmsgsize,msgtype,flags) flags = IPC_NOWAIT|MSG_NOERROR IPC_NOWAIT如果没有消息可读，则直接返回-1，MSG_NOERROR用于当maxsize参数小于接收到的消息长度时，截断超过maxsize长度后的数据，如果不指定，返回-1，并且消息仍然留在队列当中， msgtype==0则接受队列中第一条消息，大于0则接受队列中消息类型等于msgtype的消息，返回值为类似于read，等于接收到数据的字节数
 * msgsnd(int msqid,void *,msgsize,flags) flagss = IPC_NOWAIT 将新消息添加到队列尾端，发送的消息类型不能为0，第三个参数为除了type项之外的数据大小之和，mac上的管道容量为2048个字节
 * msgget(key,flags) flags = IPC_CREAT|IPC_EXCL|0755 key |= IPC_PRIVATE 注意：创建时一定要指定权限，消息队列已经很少使用了，新程序尽量不要使用它，IPC_CREAT创建一个新的消息队列或者打开一个现有队列，IPC_CREAT|IPC_EXCL若已存在对应的消息队列，则退出，否则创建，返回一个消息队列id
 * ----------消息队列----------
 *
 * ftok(char * pathname,int id) 使用路径名和一个项目id产生一个键
 * XSL IPC: 每个内核中的IPC结构都用一个非负整数的标示符加以引用，例如要向一个消息队列发送消息或者从一个消息队列读取消息，只需要知道其消息队列，标示符是IPC对象的内部名，为了使多个进程能作用在同一个IPC对象上，需要提供一个外部名，因此每个IPC对象都会与一个键相关联，将这个键作为IPC对象的外部名，每一个IPC结构都会关联一个ipc_perm结构，ipc_perm{uid_t uid(拥有者id); gid_t gid; uid_t cuid(创建者id); gid_t cgid; mode_t mode}
 *
 * mkfifo(char * pathname,mode_t mode)  命名管道，即该管道实际上为一文件，程序需要打开该文件进行通信，一端以只读方式打开，另一端以只写方式打开，先打开的一端会阻塞，直到另一端打开，或者设置O_NONBLOCK以非阻塞方式打开，设置O_NONBLOCK后需要先打开读取端，当以非阻塞方式打开管道后，如果写端已打开，但read时但无数据读取，则返回-1，如果写端已关闭，则返回0，如果读取端已关闭，进行write操作时会触发sigpipe信号，对阻塞方式打开的读写管道即使另一端已关闭进行操作时也会阻塞
 * pclose(FILE *) 若成功则返回cmd的退出状态，否则返回-1
 * popen(char * cmd,char * mode) 本质上是先创建一个pipe，然后调用fork，子进程调用exec运行cmd，因为cmd命令有可能需要输入数据，所以mode可能是"r"或者是"w"，如果返回的文件指针是可读的，那么使用"r"，如果使用的文件指针是可写的，那么使用"w"
 * pipe(int [2]) 如果某管道的写入端未关闭，且当前管道内无数据，此时进行读取会阻塞；即管道的写入端如果已关闭，此时进行读取且管道内无数据会直接返回0，如果写一个读端已经关闭的管道，则产生信号SIGPIPE，如果选择忽略此信号，则write函数返回-1，并且设置errno为EPIPE，fork会复制pipe产生的文件描述符，历史上，该管道是半双工的(即同一时刻只能有一端发送，一端接受)，mac上目前还是半双工的，某些系统支持全双工管道
 * ----------管道----------
 *
 * pututxline(utmpx *)m
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
 * setsid() 创建一个新会话，会话id为调用进程的进程id
 * getsid() 获取进程的会话id
 * setpgid(pid,pgid) 如果pid为0，则等价于getpid()，如果pgid为0，也等于getpid()
 * setpgrp() 将调用进程的进程组id设置为调用进程的进程id
 * getpgid(pid) 获取进程id为pid的进程组id，如果pid为0，则为调用进程
 * getpgrp() 获取调用进程的进程组id
 * ----------进程id相关----------
 *
 * pthread_atfork(void (*prepare)(void),void(*parent)(void),void(*child)()) 锁清理函数，在线程fork时进行锁清理，prepare用于在调用fork前获取父进程定义的所有锁，parent用于在fork生成子进程后返回前释放父进程中prepare中获取的所有锁，child函数同parent函数一样，不过是作用于子线程中
 * 线程与fork：当线程调用fork时，就为子进程创建了整个地址空间的副本，在子进程内部，只存在一个进程，它是由父进程中调用fork的线程的副本构成的，由于写时复制的原因，除非是fork后立即调用exec，否则父进程和子进程还可以共享内存页，如果父进程中的线程占有锁，那么子进程也将同样占有这些锁，可是子线程并不包含那些占有锁线程的副本(包含线程代码的副本，但是这些线程代码并不会自动运行)，所以子进程没有办法知道它占有了哪些锁，需要释放哪些锁
 * 线程与信号：每个线程都有自己的信号屏蔽字，但是信号的处理是进程中所有线程共享的，这意味着线程可以阻止某些信号，但当某个线程修改了信号处理程序后，所有的线程都必须共享这个处理行为的改变，进程中的信号是传递到单个线程的，如果一个信号与硬件故障相关，那么该信号一般会被发送到引起该事件的线程中去，而其他的信号则被发送到任意一个线程
 * pthread_kill(pthread_t,signo) 线程级的kill，可以通过发送0查看线程是否存在，如果信号的默认处理动作是终止该进程，那么发送到任意一个线程都会终止整个进程
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
 * pthread_cond_signal(pthread_cond_t *) 将条件变为真，并至少唤醒一个等待该条件的线程(即那些用pthread_cond_wait将cond绑定到互斥量的线程)
 * pthread_cond_timedwait(pthread_cond_t *,pthread_mutex_t *,timespec *) 指定所需要等待的时间，当超出时间后还未满足条件则返回错误码，并且不会将释放掉的互斥锁再次上锁，这里的timespec是当前时间加成等待时间
 * pthread_cond_wait(pthread_cond_t *,pthread_mutex_t *) 选定某个已上锁的互斥量，然后阻塞并等待条件变量变为真(即等待其他线程运行pthread_cond_signal或者pthread_cond_broadcast)，运行期间会释放互斥锁，当满足条件返回时(即被pthread_cond_signal或者pthread_cond_broadcast取消阻塞后)会再次申请上锁，因为当它阻塞时释放了互斥锁
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
 * ----------线程----------
 *
 * fexecve(fd,char ** argv,char ** env)
 * execl(pathname,char * argv,...) 无法调用自己写的脚本
 * execv(pathname,char ** argv)
 * execlp(filename,char * argv,...) 可以调用自己写的脚本，而且filename必须为完整路径
 * execvp(filename,char ** argv)
 * execle(pathname,char * argv,...,char ** env)
 * execve(pathname,char ** argv,char ** env) 倒数第二位为'v'代表参数类型为数组，为'l'则为列表，第一个参数一般设置为命令的文件名,最后一位为'p'则会通过路径列表查找文件，最后一位为'e'允许带环境参数，带环境参数后不会继承原进程环境变量,如果不带环境参数则继承原进程环境变量
 * ----------执行程序----------
 *
 * wait4(pid,status,options,rusage *)
 * wait3(status,options,rusage *)
 * waitid(idtype_t,pid,siginfo_t *,options) options = WEXITED|WSTOPED|WCONTINUED|WNOHANG|WNOWAIT
 * WIFCONTINUED(status) mac上无效
 * WIFSTOPPED(status) status值应由WSTOPSIG(status)处理，返回引起停止的信号值
 * WIFSIGNALED(status) status值应由WTERMSIG(status)处理，返回引起杀死的信号值
 * WIFEXITED(status) status值应由WEXITSTATUS(status)处理，返回退出值
 * waitpid(int pid,int * status,options) options = WUNTRACED|WCONTINUED|WNOHANG WCONTINUED在mac上无效，由停止状态转变为运行态并不会使该系统调用返回
 * wait(status) 调用时如果此时没有僵死进程，则会阻塞，如果有没回收的僵死进程，则立刻返回
 * ----------等待子进程终止----------
 *
 * atexit(void (*func)(void)) 如果使用_exit()来退出不会执行被登记过的函数
 * _exit(status) 丢弃缓冲区的io数据，直接终止
 * exit(status) 对每个打开流调用fclose()函数，并调用登记过的终止处理函数后终止
 * vfork(void) 因为fork会复制父进程的页表，如果fork后马上就执行exec，那么这个复制是不必要的，所以vfork不会复制父进程的页表，如果vfork后没有立即执行exec，那么子进程实际是在操作父进程的进程空间，vfork会保证子进程先运行,并且在它执行exit或者_exit后父进程才可以被调度
 * fork(void) 当执行fork之后，子进程会复制进程文件描述符表，但不会复制全局文件打开表，因为该表为内核级，当子进程或者父进程其一使用close关闭了该描述符后，另一个仍然可以进行IO操作，子进程一定要以exit退出，特别是在socket并发服务器里，很重要
 * ----------生成子进程----------
 *
 * clock_settime(clockid_t,timespec *) 设置时钟值
 * clock_getres(clockid_t,timespec *) 将timespec结构体初始化为clockid_t参数对应的时钟精度，如果精度为1毫秒，则tv_sec字段就是0，tv_nsec字段就是1000000
 * clock_gettime(clockid_t,timespec *) 获取指定时钟的时间 clockid_t = CLOCK_REALTIME|CLOCK_MONOTONIC|CLOCK_PROCESS_CPUTIME_ID|CLOCK_THREAD_CPUTIME_ID 分别表示实时系统时间，不带负跳数的系统实时时间，调用进程的CPU时间，调用线程的CPU时间
 *  struct timespec t;
    clock_gettime(CLOCK_REALTIME,&t);
    printf("%s",ctime(&t.tv_sec));
    获取当前系统时间

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
 * sigprocmask(flag,sigset_t * new,sigset_t * old) flag = SIG_BLOCK|SIG_UNBLOCK|SIG_SETMASK SIG_BLOCK是或操作，SIG_UNBLOCK是&~操作，SIG_SETMASK是赋值操作，处于信号集中的信号会被阻塞
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
 * ----------信号----------
 *
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
 * writev(int fd,struct iovec *,int len) 聚集写，向fd写数据，按iovec数组下标从小到大写缓冲区的iov_len个数据到fd中，也就是说如果iovec[0]指向的缓冲区写到fd后，然后写入iovec[1]指向的缓冲区，如果自己要设置某种信息协议，比如发送的数据以某特定数据开头，特定数据结尾，则此时可以设置三个iovec，分别用于头部数据，中间数据，尾部数据
 * readv(int fd,struct iovec *,int len) iovec{void * iov_base,size_t iov_len} iov_base指向缓冲区，iov_len表示缓冲区大小，iovec * 指向一个数组结构，len表示数组长度，散布读，从fd读取数据，按iovec数组下标从小到大读取数据到数组元素中所指向的缓冲区中，也就是说如果iovec[0]指向的缓冲区装满后，然后存入iovec[1]指向的缓冲区
 * pwrite(fd,buf,len,offset) 从fd的第offset的偏移量处写入buf的前len个字节的数据，不更新当前的文件偏移量，在多线程环境下有很大的作用
 * pread(fd,buf,len,offset) 从fd的第offset的偏移量处读取len个字节的数据到buf，不更新当前的文件偏移量，在多线程环境下有很大的作用
 * dup2(oldfd,newfd) 复制oldfd到newfd，如果newfd以及被占用，则会先用close关闭它，复制后文件描述符设置的close-on-exec位会消失
 * fcntl(fd,cmd,attr) cmd = F_GETFL|F_SETFL|F_GETFD|F_SETFD|F_DUPFD|F_F_DUPFD_CLOEXEC|F_GETOWN|F_SETOWN F_SETFD是设置文件描述符标志(进程文件描述符表中,FD_CLOEXEC标志)，F_SETFL是设置文件状态标志(全局文件打开表中，可设置O_NONBLOCK)，F_DUPDF是复制文件描述符但不会复制F_CLOEXEC标志，F_DUPDF_CLOEXEC则会设置F_CLOEXEC
 * lseek(fd,offset,position)
 * write(fd,buf,len) 可以对文件写大量的0，并且会占用空间，而如果是偏移后写数据，中间的空洞不会占据空间(视系统而定，mac占用)，但是如果复制这个文件，复制的空洞部分会被0填充，因为read函数读取空洞部分读出的数据是0，利用文件空洞可以实现多线程下载
 * aio_read(aiocb *)
 * read(fd,buf,len) 文件空洞是可以读的，只不过读到的数据是0，对于一般的文本文件读取，如果文件为空会返回0，而对于一般的慢速设备比如socket，如果当前socket缓冲区内无数据，则会阻塞，如果设置为非阻塞模式，当无数据时，则会返回-1，并且将错误码设置为EAGAIN，如果另一段已经关闭，则返回0，read会读取换行符
 * close(fd) 只是进程文件描述符中对应的记录，并将fd所对应的全局文件打开表表项中的标记减一，当标记为0是文件关闭
 * openat(fd|-1,filename|pathname,flags,mode) fd指向filename的目录，或者等于AT_FDCWD，则fd等同于进程当前工作目录fd
 * open(const char *path, int flag, int mode) flag = O_RDONLY|O_WRONLY|O_RDWR|O_APPEND|O_CLOEXEC|O_CREAT|O_DIRECTORY|O_EXCL|O_NOCTTY|O_NOFOLLOW|O_NONBLOCK|O_SYNC|O_TRUNC|O_DSYNC|O_FSYNC
 *
 *
 * 开头为l为不对符号链接解引用，直接操控符号链接文件的inode目录项
 */
