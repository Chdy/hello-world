//
// Created by 邓岩 on 2018/10/20.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include <aio.h>
static jmp_buf env;

extern char ** environ;

void printSigset(FILE * io,const char * prestr,const sigset_t * sigset);
void printSigmask(FILE * io,const char * msg);
void printPending(FILE * io,const char * msg);

void handle(int sig)
{
    static int count = 0;
    if(sig == SIGINT)
    {
        count++;
        printf("Signal interrupt %d\n",count);
        return;
    }
    printf("Caugnt Quit\n");
    exit(EXIT_SUCCESS);
}

struct aiocb kbcbuf;

void sig_handler(int sig)
{
    if(aio_return(&kbcbuf)==1) {
        char *c = kbcbuf.aio_buf;
        printf("\nreceive sigio:");
        printf("%s\n", c);
        fflush(stdout);
    }
}

void hander(int sig)
{
    printSigmask(stdout,"in hander :\t\t");
    printf("catch %s\n",strsignal(sig));
}

int readline(int fd,char * buf)
{
    char c;
    int i,n = 0;
    while((i = read(fd,&c,1))&&c!='\n')
    {
        buf[n++] = c;
    }
    if(buf[n-1] == '\n')
        buf[n] = 0;
    else
    {
        buf[n] = '\n';
        buf[++n] = 0;
    }
    return n;
}

int main(void)
{
    int i;
    sigset_t sig,pensig;
    sigaddset(&sig,SIGINT);
    setbuf(stdout,NULL);
    struct sigaction siga;
    siga.sa_mask = 0;
    siga.sa_flags = 0;
    siga.__sigaction_u.__sa_handler = hander;
    sigaction(SIGINT,&siga,NULL);
    printf("pid = %d\n",getpid());
    sigemptyset(&pensig);
    sigaddset(&pensig,SIGINT);
    sigprocmask(SIG_BLOCK,&pensig,NULL);
    printSigmask(stdout,"brfore :\t\t\n");
    //raise(SIGINT);
//    sigset_t mask,empty;
//    sigemptyset(&mask);
//    sigemptyset(&empty);
//    sigaddset(&mask,SIGINT);
//    sigprocmask(SIG_BLOCK,&mask,NULL);
//    raise(SIGINT);
//    sigprocmask(SIG_SETMASK,&empty,NULL);
    sigwait(&pensig,&i);
    printSigmask(stdout,"after :\t\t");

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