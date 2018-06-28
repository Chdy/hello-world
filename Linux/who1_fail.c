//
// Created by 邓岩 on 07/03/2017.
//

# include <stdio.h>
# include <stdlib.h>
# include <utmp.h>//保存用户登录信息的数据结构，utmp文件的路径
# include <utmpx.h>
# include <fcntl.h>
# include <unistd.h>

# define SHOWHOST
void show_info(struct utmp *);

int main(void)
{
    int i = 0;
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);
    if((utmpfd = open(UTMPX_FILE,O_RDONLY))==EOF)
        perror(UTMPX_FILE);
    if(read(utmpfd,&current_record,reclen)==reclen)
        while(read(utmpfd,&current_record,reclen)==reclen)
        {
            i++;
            show_info(&current_record);
        }
    printf("i = %d",i);
    return 0;
}

void show_info(struct utmp * umptr)
{
    if(umptr->ut_line==0)
        return;
    printf("%-10s",umptr->ut_name);
    printf("%-10s",umptr->ut_line);
    printf("\n");

    //printf(" ");
    //printf("%10ld",umptr->ut_);
}