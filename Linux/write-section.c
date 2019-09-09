//
// Created by 邓岩 on 2018/11/21.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

// 修改Cmake

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    char buf[1000];
    int wfd = open("/Users/dengyan/Documents/Parallels/Maple.pvm/Maple-0.hdd/Maple-0.hdd.0.{5fbaabe3-6958-40ff-92a7-860e329aab41}.hds", O_WRONLY);
    if (wfd == -1){
        printf("open wfd error %d", wfd);
        return -1;
    }
    int rfd = open("/Users/dengyan/Documents/x86-assambly/nasm/boot.bin", O_RDONLY);
    if (rfd == -1) {
        printf("open rfd error %d", wfd);
        return -1;
    }
    int i = read(rfd, buf , 1000);
    write(wfd,buf,i);
    return 0;
}