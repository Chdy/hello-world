# include <stdio.h>
# include <stdlib.h>

# define maxsize 100
typedef int Mazetype[maxsize][maxsize];
Mazetype m;
int x,y;

typedef struct postype
{
    int x;
    int y;
}postype;

postype start,end;
int curstep = 1;

void init_maze(int);
void printf_maze(void);
void path_maze(postype,int);
int pass_maze(postype);

int main(void)
{
    init_maze(-1);
    m[start.x][start.y] = 1;
    printf("该迷宫通路如下：\n");
    path_maze(start,1);
    return 0;
}

void path_maze(postype curpose,int curstep)
{
    int i;
    postype next;
    postype direct[4] = { {0,1},{1,0},{0,-1},{-1,0} };
    for(i=0;i<4;i++)
    {
        next.x = curpose.x + direct[i].x;
        next.y = curpose.y + direct[i].y;
        if( m[next.x][next.y] == -1)
        {
            m[next.x][next.y] = ++curstep;
            if(next.x!=end.x || next.y!=end.y)
                path_maze(next,curstep);
            else
            {
                printf_maze();
                printf("\n");
            }
        m[next.x][next.y] = -1;
        curstep--;
        }
    }
}

int pass_maze(postype c)
{
    if( m[c.x][c.y] == -1 )
        return 1;
    else
        return 0;
}

void init_maze(int k)
{
    int i,j;
    int x1,y1;
    printf("请输入迷宫的行数！\n");
    scanf("%d",&x);
    printf("请输入迷宫的列数！\n");
    scanf("%d",&y);
    for(i=0;i<y;i++)
    {
        m[0][i] = 0;
        m[x-1][i] = 0;
    }
    for(j=0;j<x-1;j++)
    {
        m[j][0] = 0;
        m[j][y-1] = 0;
    }
    for(i=1;i<x-1;i++)
        for(j=1;j<y-1;j++)
            m[i][j] = k;
    printf("请输入迷宫内墙的个数：\n");
    scanf("%d",&j);
    for(i=0;i<j;i++)
    {
        printf("请输入第%d个墙的坐标：\n",i+1);
        scanf("%d,%d",&x1,&y1);
        m[x1][y1] = 0;
    }
    printf("请输入迷宫的起点坐标：\n");
    scanf("%d,%d",&start.x,&start.y);
    printf("请输入迷宫的终点坐标：\n");
    scanf("%d,%d",&end.x,&end.y);
    printf("当前迷宫结构为：\n");
    printf_maze();
}

void printf_maze(void)
{
    int i,j;
    for(i=0;i<x;i++)
    {
        for(j=0;j<y;j++)
        {
            printf("%3d",m[i][j]);
        }
        printf("\n");
    }
}













