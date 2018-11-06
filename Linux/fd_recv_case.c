//
// Created by 邓岩 on 2018/10/21.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include "send_fd.h"

int main(void)
{
    int i, fd, rfd;
    char buf[100];
    struct sockaddr_un un;

    setbuf(stdout,NULL);
    unlink("/Users/dengyan/client");
    strcpy(un.sun_path,"/Users/dengyan/client");
    un.sun_family = AF_UNIX;
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(bind(fd,(struct sockaddr *)&un, sizeof(struct sockaddr_un)) < 0)
    {
        printf("bind error: %s\n",strerror(errno));
        exit(-1);
    }
    rfd = recv_fd(fd, write);
    while (i = read(rfd,buf,100))
        write(STDOUT_FILENO, buf, i);
    return 0;
}