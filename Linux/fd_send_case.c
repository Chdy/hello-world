//
// Created by 邓岩 on 2018/10/21.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include "send_fd.h"

int main(void)
{
    struct sockaddr_un un;
    unlink("/Users/dengyan/serve");
    strcpy(un.sun_path, "/Users/dengyan/serve");
    un.sun_family = AF_UNIX;
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(bind(fd,(struct sockaddr *)&un, sizeof(struct sockaddr_un)) < 0)
    {
        printf("bind error: %s\n",strerror(errno));
        exit(-1);
    }
    struct sockaddr_un rv;
    rv.sun_family = AF_UNIX;
    strcpy(rv.sun_path, "/Users/dengyan/client");

    connect(fd, (struct sockaddr *)&rv, sizeof(struct sockaddr_un)); //对报文传输使用连接，则可以在传输时不指定目的地址

    int fd_to_send = open("/Users/dengyan/exam.c", O_RDWR);
    printf("the open file fd is %d \n", fd_to_send);
    send_fd(fd, fd_to_send);
    return 0;
}