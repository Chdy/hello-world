//
// Created by 邓岩 on 01/11/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(void)//使子进程先运行
{
    int a = 0;
    int fd = open("/Users/dengyan/exam",O_RDONLY);
    int i = fcntl(fd,F_GETFD);
    printf("%d\n",i);
    fcntl(fd,F_SETFD,FD_CLOEXEC);
    i = fcntl(fd,F_GETFD);
    printf("%d\n",i);
    int fd2 = fcntl(fd,F_DUPFD_CLOEXEC,3);//查找文件描述符>3的可用描述符，复制文件描述符并且不消除close-on-exec标志
    i = fcntl(fd2,F_GETFD);
    printf("%d\n",i);
}