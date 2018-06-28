//
// Created by 邓岩 on 08/09/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(void)
{
    int i;
    char buf[100];
    struct sockaddr_un sock;
    sock.sun_family = AF_UNIX;
    strcpy(sock.sun_path,"/Users/dengyan/sock");
    int sockfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(connect(sockfd,(struct sockaddr *)&sock, sizeof(struct sockaddr_un))==-1)
        exit(-1);
    else
    {
        while(i = read(STDIN_FILENO,buf,100))
        {
            if(i == -1)
            {
                printf("EOF\n");
                exit(-1);
            }
            write(sockfd,buf,i);
        }
    }
    return 0;
}