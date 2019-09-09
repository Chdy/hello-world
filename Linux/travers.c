//
// Created by 邓岩 on 27/04/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(int argc,char ** argv) {
    int fd1,fd2;
    int num = 0;
    int line[1000];
    int l = 0;
    char a;
    if((fd1 = open("/Users/dengyan/exam",O_RDONLY)) == EOF)
        exit(-1);
    if((fd2 = open("/Users/dengyan/exam.c",O_WRONLY)) == EOF)
        exit(-1);
    while(read(fd1,&a,1)==1)
    {
        num++;
        if(a == '\n')
        {
            line[l++] = num;
        }
    }
    line[l] = num;
    while(l--)
    {
        lseek(fd1,line[l],SEEK_SET);
        for (int i = 0; i < line[l+1]-line[l]; ++i) {
            read(fd1,&a,1);
            write(fd2,&a,1);
        }
    }
    lseek(fd1,0,SEEK_SET);
    for (int i = 0; i < line[0]; ++i) {
        read(fd1,&a,1);
        write(fd2,&a,1);
    }
    return 1;
}