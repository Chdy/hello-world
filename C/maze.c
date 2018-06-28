# include <stdio.h>
# include <stdlib.h>

# define size 100
# define extend 10
# define Mazesize 25

typedef struct postype
{
    int x;
    int y;
}postype;

typedef struct SElem
{
    int ord;
    postype seat;
    int di;
}SElem,*pSElem;

typedef struct steak
{
    struct SElem * pTop;
    struct SElem * pBottom;
    int steaksize;
}Steak,*pSteak;

int curstep = 1;
int x;
int y;
postype start,end;
typedef int MazeType[Mazesize][Mazesize];
MazeType m;

void init_steak(pSteak);//初始化栈
void push_steak(pSteak,SElem);
void pop_steak(pSteak,pSElem);
int empty_steak(pSteak);
void init_maze(int k);//k为通道值
void foot_maze(postype);
void print_maze(void);
void mark_maze(postype);
void next_maze(postype *curpos,int di);
int MazePath(postype,postype);
int pass_maze(postype);

int main(void)
{
    init_maze(1);
    if( MazePath(start,end) )
    {
        printf("迷宫有解：\n");
        print_maze();
    }
    else
        printf("迷宫无解：\n");
    return 0;
}

int MazePath(postype start,postype end)
{
    Steak S;
    init_steak(&S);
    postype curpos = start;
    SElem e;
    do
    {
        if( pass_maze(curpos) )//路通
        {
            foot_maze(curpos);
            e.seat = curpos;
            e.ord = curstep;
            e.di = 0;
            push_steak(&S,e);
            curstep++;
            if(curpos.x == end.x && curpos.y == end.y)
                return 1;
            next_maze(&curpos,e.di);
        }
        else//路不通
        {
            if( !empty_steak(&S) )
            {
                pop_steak(&S,&e);
                curstep--;
                while(e.di == 3 && !empty_steak(&S))
                {
                    mark_maze(e.seat);
                    pop_steak(&S,&e);
                    curstep--;
                }
                if(e.di < 3)
                {
                    e.di++;
                    push_steak(&S,e);
                    curstep++;
                    curpos = e.seat;
                    next_maze(&curpos,e.di);
                }
            }
        }
    }while(!empty_steak(&S));
    return 0;
}

void foot_maze(postype curpos)
{
    m[curpos.x][curpos.y] = curstep;
}

void mark_maze(postype curpos)
{
    m[curpos.x][curpos.y] = -1;
}

int pass_maze(postype curpos)
{
    if( m[curpos.x][curpos.y] == 1)
        return 1;
    else
        return 0;
}

void next_maze(postype *curpos,int di)
{
    postype direct[4] = { {0,1},{1,0},{0,-1},{-1,0} };
    curpos->x += direct[di].x;
    curpos->y += direct[di].y;
}

void init_maze(int k)
{
    int i,j,x1,y1;
    printf("请输入迷宫的行数，列数：\n");
    scanf("%d,%d",&x,&y);
    for(i=0;i<y;i++)
    {
        m[0][i] = 0;
        m[x-1][i] = 0;
    }
    for(i=0;i<x-1;i++)
    {
        m[i][0] = 0;
        m[i][y-1] = 0;
    }
    for(i=1;i<x-1;i++)
        for(j=1;j<y-1;j++)
            m[i][j] = k;
    printf("请输入迷宫内墙的个数：\n");
    scanf("%d",&j);
    for(i=0;i<j;i++)
    {
        printf("请输入第%d块墙的坐标：\n",i+1);
        scanf("%d,%d",&x1,&y1);
        m[x1][y1] = 0;
    }
    printf("迷宫结构如下：\n");
    print_maze();
    printf("请输入迷宫的起点坐标：\n");
    scanf("%d,%d",&start.x,&start.y);
    printf("请输入迷宫的终点坐标：\n");
    scanf("%d,%d",&end.x,&end.y);
}

void print_maze()
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

void pop_steak(pSteak S,pSElem e)
{
    *e = *--S->pTop;
}

void push_steak(pSteak S,SElem e)
{
    if(S->pTop-S->pBottom == S->steaksize)
    {
        S->pBottom = (pSElem)realloc(S->pBottom,sizeof(SElem)*(S->steaksize+extend));
        S->pTop = S->pBottom + S->steaksize;
        S->steaksize += extend;
    }
    *S->pTop = e;
    S->pTop++;
}

void init_steak(pSteak S)
{
    S->pBottom = (pSElem)malloc(sizeof(SElem)*size);
    S->pTop = S->pBottom;
    S->steaksize = size;
}

int empty_steak(pSteak S)
{
    if(S->pTop == S->pBottom)
        return 1;
    else
        return 0;
}








