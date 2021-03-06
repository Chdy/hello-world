/*
 --------------------------------------------------
 编写内容：静态链表
 功能：
 创建和初始化
 取两个补集的并集
 分配结点
 释放结点
 时间：2016.04.05
 --------------------------------------------------
 */
# include <stdio.h>
# include <stdlib.h>

# define maxsize 100

typedef struct node
{
    int data;
    int cur;
}Node,*pNode;

void init_list(pNode);
int malloc_list(pNode);
void traverse_list(pNode);
void free_list(pNode,int);

int main(void)
{
    int i;
    int j;
    int k;
    int val;
    int p;
    int q;
    int S;//头结点位序
    int r;//尾结点位序
    Node space[maxsize];
    init_list(space);
    S = malloc_list(space);
    r = S;
    printf("请输入所需结点的个数：\n");
    scanf("%d",&j);
    for(i=1;i<=j;i++)
    {
        printf("请输入第%d个值",i);
        scanf("%d",&val);
        k = malloc_list(space);
        space[k].data = val;
        space[r].cur = k;
        r = k;
    }
    space[r].cur = 0;
    printf("请输入你想输入元素的个数：\n");
    scanf("%d",&j);
    printf("如过输入的值已拥有,则删除原本的值，否者加入该值！\n");
    for(i=0;i<j;i++)
    {
        p = S;
        k = space[S].cur;
        printf("请输入你想要输入的值：\n");
        scanf("%d",&val);
        while(space[k].cur != 0 && space[k].data != val)
        {
            p = k;
            k = space[k].cur;
        }
        if(space[k].cur == 0)
        {
            q = malloc_list(space);
            space[q].data = val;
            space[q].cur = space[r].cur;
            space[r].cur = q;
        }
        else
        {
            space[p].cur = space[k].cur;
            free_list(space,k);
            if(k == r)
                r = p;
        }
    }
    traverse_list(space);
    
    return 0;
}

void traverse_list(pNode space)
{
    int i = 1;
    int n = 1;
    while(space[i].cur != 0)
    {
        i = space[i].cur;
        printf("第%d个值为：%d\n",n,space[i].data);
        n++;
    }
}

void free_list(pNode space,int k)
{
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

int malloc_list(pNode space)
{
    int i = space[0].cur;
    if(space[0].cur != 0)
        space[0].cur = space[i].cur;
    return i;
}

void init_list(pNode space)
{
    int i;
    for(i=0; i<maxsize-1; i++)
    {
        space[i].cur = i+1;
    }
    space[maxsize-1].cur = 0;
}











