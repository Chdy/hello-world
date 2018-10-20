//
// Created by 邓岩 on 09/09/2017.
//
//接受由客户端发送过来的字符，并将其处理成为大写形式后发送给客户端

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(int argc,char ** argv)
{
    int i,len;
    setbuf(stdout,NULL);
    char buf[100];
    struct sockaddr_un addr,clientaddr;
    addr.sun_family = AF_UNIX;
    unlink("/Users/dengyan/sock");
    strcpy(addr.sun_path,"/Users/dengyan/sock");
    int sockfd = socket(AF_UNIX,SOCK_DGRAM,0);
    if((bind(sockfd,(struct sockaddr *)&addr, sizeof(struct sockaddr_un))) == -1)
        exit(-1);
    for(;;)
    {
        len = sizeof(struct sockaddr_un);
        i = recvfrom(sockfd,buf,100,0,(struct sockaddr *)&clientaddr, &len);
        for (int j = 0; j < i; ++j) {
            buf[j] = toupper(buf[j]);
        }
        sendto(sockfd,buf,i,0,(struct sockaddr *)&clientaddr,len);
    }
    return 0;
}