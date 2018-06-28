//
// Created by 邓岩 on 16/09/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(void)
{
    int i;
    char buf[100];
    struct sockaddr_in svaddr;
    inet_pton(AF_INET,"127.0.0.1",&(svaddr.sin_addr.s_addr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(50000);
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    connect(sockfd,(struct sockaddr *)&svaddr,sizeof(struct sockaddr_in));
    i = read(STDIN_FILENO,buf,100);
    write(sockfd,buf,i);
    i = read(sockfd,buf,100);
    write(STDOUT_FILENO,buf,i);
    return 0;
}