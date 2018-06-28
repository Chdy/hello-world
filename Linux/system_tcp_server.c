//
// Created by 邓岩 on 19/09/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

void hand(int sig)
{
    while((sig = waitpid(-1,NULL,WNOHANG))>0)
    {
        printf("reap the process %d\n",sig);
        continue;
    }
}

int main(int argc,char ** argv)
{
    setbuf(stdout,NULL);
    struct sigvec sigv;
    struct sockaddr_in claddr;
    sigv.sv_handler = hand;
    sigv.sv_flags = 0;
    sigv.sv_mask = 0;
    sigvec(SIGCHLD,&sigv,NULL);
    signal(SIGPIPE,SIG_IGN);
    int len,fd;
    struct addrinfo hints,* result,* p;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_NUMERICSERV|AI_PASSIVE|AI_ADDRCONFIG;
    if(getaddrinfo(NULL,"59999",&hints,&result)!=0)
        exit(-1);
    len = bind(sockfd,result->ai_addr, sizeof(struct sockaddr_in));
    getsockname(sockfd,(struct sockaddr *)&claddr,&len);
    printf("httpd opened using port %d ip %s\n",claddr.sin_port,inet_ntoa(claddr.sin_addr));
    //printf("%d",((struct sockaddr_in *)(result->ai_addr))->sin_addr);
    freeaddrinfo(result);
    /*struct sockaddr_in server;
    inet_aton("127.0.0.1",&(server.sin_addr));
    server.sin_port = htons(59999);
    server.sin_family = AF_INET;*/
    listen(sockfd,10);
    for (;;) {
        len = sizeof(struct sockaddr_in);
        fd = accept(sockfd,NULL,NULL);
        if(fork())
        {
            close(fd);
        }
        else//子进程最后一定要用exit退出，不然会有严重bug
        {
            close(sockfd);
            int i;
            int count;
            char buf[100];
            dup2(fd,STDOUT_FILENO);
            dup2(fd,STDERR_FILENO);
            for(;;) {
                if ((i = read(fd, buf, 100)) <= 0)
                    exit(-1);
                buf[i - 1] = 0;
                system(buf);
                write(STDOUT_FILENO,"\0",1);
            }
        }
    }

    return 0;
}