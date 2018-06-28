//
// Created by Vain loser on 26/11/2016.
//

# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
//open(char *,int,mode_t) 文件名，进程访问权限，文件固有权限
//终端控制符 command + d
/*
 * STDIN_FILENO 0
 * STDOUT_FILENO 1
 * STDERR_FILENO 2
 */
# define DEF_UMASK S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
# define DEF_MODE S_IWGRP|S_IWOTH
int main(void)
{
    umask(DEF_UMASK);
    int fd = open("/Users/dengyan/ClionProjects/C/test.txt",O_RDWR|O_APPEND|O_CREAT,DEF_MODE);
    int io = open("/Users/dengyan/ClionProjects/C/io.txt",O_RDWR|O_CREAT|O_APPEND,DEF_MODE);
    int io2 = open("/Users/dengyan/ClionProjects/C/io2.txt",O_RDWR|O_CREAT|O_APPEND,DEF_MODE);
    char c[51];
    char b[5] = "},{";
    int i;
    write(io,&c,i);
    while(i = read(fd,c,51))
    {
        write(io,c,i);
        write(io,b,3);
    }
    close(fd);
    return 0;
}