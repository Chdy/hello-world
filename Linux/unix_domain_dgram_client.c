//
// Created by 邓岩 on 09/09/2017.
//
//向服务器发送数据，然后接受处理后的数据

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(void)
{
    int i;
    char buf[100];
    struct sockaddr_un clientaddr,serveraddr;
    serveraddr.sun_family = AF_UNIX;
    strcpy(serveraddr.sun_path,"/Users/dengyan/sock");
    clientaddr.sun_family = AF_UNIX;
    unlink("/Users/dengyan/clientaddr");
    strcpy(clientaddr.sun_path,"/Users/dengyan/clientaddr");
    int sockfd = socket(AF_UNIX,SOCK_DGRAM,0);
    if(bind(sockfd,(struct sockaddr *)&clientaddr, sizeof(struct sockaddr_un)) == -1)
        exit(-1);
    for(;;)
    {
        i = read(STDIN_FILENO,buf,100);
        sendto(sockfd,buf,i,0,(struct sockaddr *)&serveraddr,sizeof(struct sockaddr_un));
        i = recvfrom(sockfd,buf,100,0,NULL,NULL);
        write(STDOUT_FILENO,buf,i);
    }
    return 0;
}