//
// Created by 邓岩 on 06/09/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

//上锁函数和解锁函数本身就像是操作互斥量一样，对文件本身并不会产生影响

int main(int argc,char ** argv)
{
    char buf[100];
    int i;
    int fd = open("/Users/dengyan/exam",O_RDONLY);
    flock(fd,LOCK_SH);//在文件描述符fd指向的全局文件打开表中放置共享锁
    if(fork())//父进程
    {
        printf("I am parent process:\n");
        i = read(fd,buf,100);//读取数据
        write(STDOUT_FILENO,buf,i);//写入标准输出
        wait(NULL);//等待子进程终止
    } else//子进程
    {
        printf("I am children process:\n");
        close(fd);//关闭从父进程继承的文件描述符
        int fd = open("/Users/dengyan/exam",O_RDONLY);//重新打开问价
        if(flock(fd,LOCK_EX|LOCK_NB)==-1)//为文件设置互斥锁并且为非阻塞操作，失败立即返回
        {
            if(errno == EAGAIN)//由于此时父进程拥有该文件的共享锁，所以设置互斥锁失败
                printf("this file already locked by other process\n");
        }
        else{
            i = read(fd,buf,100);
            write(STDOUT_FILENO,buf,i);
        }
        exit(EXIT_SUCCESS);
    }
    return 0;
}
