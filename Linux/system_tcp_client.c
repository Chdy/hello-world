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

int main(void)
{
    char buf[100];
	int i;
	printf("请输入需要连接的ip地址:\n");
	i = read(STDIN_FILENO,buf,100);
	buf[i-1] = 0;
    struct sockaddr_in svaddr;
    inet_aton(buf,&svaddr.sin_addr);
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(59999);
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    connect(sockfd,(struct sockaddr *)&svaddr, sizeof(struct sockaddr_in));
    for (;;) {
        i = read(STDIN_FILENO,buf,100);
        write(sockfd,buf,i);
        while(i = read(sockfd,buf,100))
        {
            if(i==1)
                if(*buf==0)
                    break;
            write(STDOUT_FILENO,buf,i);
        }
    }
}
