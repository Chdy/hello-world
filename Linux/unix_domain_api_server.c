//
// Created by 邓岩 on 2018/10/20.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include "unix_socket_api.h"

int main(int argc, char *argv[]) {
    setbuf(stdout,NULL);
    uid_t uid;
    unlink("/Users/dengyan/serve");
    int servfd = serv_listen("/Users/dengyan/serve");
    printf("waiting...\n");
    int fd = serv_accept(servfd,&uid);
    printf("link uid: %d\n",uid);
    char buf[100];
    int i = read(fd,buf,100);
    buf[5] = '_';
    buf[i] = 0;
    printf("%d %s\n",i,buf);
    buf[read(fd,buf,100)] = 0;
    printf("%s\n",buf);
    return 0;
}