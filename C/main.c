# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <curses.h>
# include <unistd.h>
# include <fcntl.h>
# include <curses.h>


# define MazeLength 5

typedef int m[MazeLength];

typedef struct node
{
	int a;
	int b;
}Node,*pNode;

char* convert(char* s, int numRows);

int main(void)
{
    char sex;
    int id, age;
    double yw, sx, yy, zh, ty;
    printf("请输入学号，年龄, 性别，语文成绩，数学成绩，英语成绩，综合成绩，体育成绩\n");
    scanf("%d %d %c %lf %lf %lf %lf %lf", &id, &age, &sex, &yw, &sx, &yy, &zh, &ty);
    printf("%d %d %c %lf", id, age, sex, (yw+sx+yy+zh+ty)/5);
    return 0;
}
/*
int fd = open("/dev/tty",O_RDWR);
    if(fd == EOF)
        exit(-1);
   char c;
    read(fd,&c,1);
    printf("%c",c);
 */

char* convert(char* s, int numRows) {
    int half;
    int off = numRows + 1;
    if(numRows&1==1)
        half = (numRows + 1)/2;
    else
        half = numRows/2 + 1;
    int len = 1;
    char * p = s;
    while(*p++)
    {
        len++;
    }
    p--;
    char * buf = (char *)malloc(len);
    char * q = buf;
    for(int i = 0;i != numRows;i++)
    {
        char * tmp = s + i;
        if(i==half-1)
            while(tmp<p)
            {
                *q++ = *tmp;
                if(tmp+half<p)//改
                    *q++ = *(tmp + half);//改 对于偶数行需要更换处理
                tmp+=off;
            }
        else
            while(tmp<p)
            {
                *q++ = *tmp;
                tmp+=off;
            }
    }
    buf[len-1] = 0;
    return buf;
}
