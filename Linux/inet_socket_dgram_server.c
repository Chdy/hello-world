//
// Created by 邓岩 on 13/09/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(int argc,char ** argv)
{
    int len,i;
    char buf[100];
    struct sockaddr_in6 server,client;
    server.sin6_family = AF_INET6;
    server.sin6_addr = in6addr_any;
    server.sin6_port = htons(50000);
    int sockfd = socket(AF_INET6,SOCK_DGRAM,0);
    bind(sockfd,(struct sockaddr *)&server, sizeof(struct sockaddr_in6));
    for(;;) {
        len = sizeof(struct sockaddr_in6);
        i = recvfrom(sockfd,buf,100,0,(struct sockaddr *)&client,&len);
        for (int j = 0; j < i; ++j) {
            buf[j] = toupper(buf[j]);
        }
        sendto(sockfd,buf,i,0,(struct sockaddr *)&client,len);
    }
}