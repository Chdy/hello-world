//
// Created by 邓岩 on 10/10/2017.
//

void hand(int sig)
{
    int i;
    if(sig == SIGIO)
        printf("receive\n");
    //while(i = read(fd,sbuf,100))
    //    write(STDOUT_FILENO,sbuf,i);
}

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pipe(pipefd);
    if(fork())
    {
        setbuf(stdout,NULL);
        struct sigaction sigv;
        sigv.sa_flags = SA_RESTART;
        sigemptyset(&sigv.sa_mask);
        sigv.__sigaction_u.__sa_handler = hand;
        sigaction(SIGIO,&sigv,NULL);
        close(pipefd[1]);
        fcntl(pipefd[0],F_SETOWN,getpid());
        fcntl(pipefd[0],F_SETFL,fcntl(pipefd[0],F_GETFL)|O_ASYNC);
        int i = read(pipefd[0],sbuf,100);
        write(STDOUT_FILENO,sbuf,i);
    } else
    {
        close(pipefd[0]);
        sleep(5);
        write(pipefd[1],"dengzhewo",9);
        exit(-1);
    }

}