//
// Created by 邓岩 on 08/09/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(int argc,char ** argv)
{
    char buf[100];
    int fd,len,i;
    len = sizeof(struct sockaddr);
    unlink("/Users/dengyan/sock");
    struct sockaddr_un sock,recv;
    sock.sun_family = AF_UNIX;
    strcpy(sock.sun_path,"/Users/dengyan/sock");
    int sockfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(bind(sockfd,(struct sockaddr *)&sock,sizeof(struct sockaddr_un))==-1)
    {
        exit(-1);
    }
    listen(sockfd,5);
    for (;;) {
        if((fd = accept(sockfd,&recv,&len))==-1)
            exit(-1);
        while(i = read(fd,buf,100))
            write(STDOUT_FILENO,buf,i);
    }
    return 0;
}