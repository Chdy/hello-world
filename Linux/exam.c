# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include <GLUT/GLUT.h>
# include "unix_socket_api.h"

int main(int argc, char *argv[]) {
    struct sockaddr_un sv;
    int fd = socket(AF_UNIX,SOCK_DGRAM,0);
    strcpy(sv.sun_path,"/Users/dengyan/sock");
    sv.sun_family = AF_UNIX;
    if(bind(fd,(struct sockaddr *)&sv,__offsetof(struct sockaddr_un,sun_path) + strlen(sv.sun_path)) < 0)
    {
        printf("bind error");
        unlink("/Users/dengyan/sock");
        exit(-1);
    }
    printf("Unix domain socket bind");
    unlink("/Users/dengyan/sock");
    return 0;
}