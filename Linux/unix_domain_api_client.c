//
// Created by 邓岩 on 2018/10/20.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include "unix_socket_api.h"

int main(int argc, char *argv[]) {
    setbuf(stdout,NULL);
    int clifd = cli_conn("/Users/dengyan/serve");
    char buf[100] = "hello";
    buf[5] = 0;
    strcpy(buf + 6,"world");
    write(clifd,buf,11);
    /*int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un un;
    struct sockaddr_un sv;
    unlink("/Users/dengyan/client");
    strcpy(un.sun_path, "/Users/dengyan/client");
    un.sun_family = AF_UNIX;
    int len = __offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
    int i = bind(fd, (struct sockaddr *)&un, len);
    printf("%d\n",i);
    strcpy(sv.sun_path, "/Users/dengyan/serve");
    sv.sun_family = AF_UNIX;
    len = __offsetof(struct sockaddr_un, sun_path) + strlen(sv.sun_path);
    connect(fd, (struct sockaddr *)&sv, len);
    printf("%s",strerror(errno));*/
    return 0;
}