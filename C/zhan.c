/*
 --------------------------------------------------
 编写内容：栈
 功能：
    创建并初始化
    压栈
    遍历
    删除
    出栈
 时间：2016.03.25
 --------------------------------------------------
 */

# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    int data;
    struct node * pNext;
}NODE,*PNODE;

typedef struct stack
{
    PNODE pTop;
    PNODE pBottom;
}STACK,*PSTACK;

int init_zhan(PSTACK);
void push_zhan(PSTACK,int);
int traverse_zhan(PSTACK);
int empty_zhan(PSTACK);
int delete_zhan(PSTACK,int *);
void clear_zhan(PSTACK);

int main(void)
{
    int val;
    PSTACK pS;
    init_zhan(pS);
    traverse_zhan(pS);
    push_zhan(pS,8);
    push_zhan(pS,5);
    push_zhan(pS,2);
    push_zhan(pS,6);
    printf("栈顶元素为:%d\n", top_zhan(pS));
    traverse_zhan(pS);
    if ( delete_zhan(pS,&val) )
    {
        printf("删除成功！删除的值为：%d\n",val);
    }
    else
        printf("栈为空！删除失败\n");
    traverse_zhan(pS);
    printf("清空栈\n");
    clear_zhan(pS);
    if( traverse_zhan(pS) )
        printf("\n");
    else
        printf("为空！\n");
    push_zhan(pS,6);
    traverse_zhan(pS);
    return 0;
}

int init_zhan(PSTACK pS)
{
    PNODE pHead = (PNODE)malloc(sizeof(NODE));
    pHead->pNext = NULL;
    if(pHead == NULL)
    {
        printf("分配失败！");
        exit(-1);
    }
    pS->pTop = pHead;
    pS->pBottom = pHead;
    
    return 0;
}

void push_zhan(PSTACK pS,int val)
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    pNew->data = val;
    pNew->pNext = pS->pTop;
    pS->pTop = pNew;
    printf("%d 入栈成功\n", val);
    return;
}

int traverse_zhan(PSTACK pS)
{
    if( empty_zhan(pS) )
        return 0;
    printf("遍历:");
    PNODE p;
    p = pS->pTop;
    while(p != pS->pBottom)
    {
        printf("%d ",p->data);
        p = p->pNext;
    }
    printf("\n");
    return 1;
}

int empty_zhan(PSTACK pS)
{
    if(pS->pTop == pS->pBottom)
        return 1;
    else
        return 0;
}

int delete_zhan(PSTACK pS,int * val)
{
    if( empty_zhan(pS) )
        return 0;
    *val = pS->pTop->data;
    PNODE p;
    p = pS->pTop;
    pS->pTop = p->pNext;
    free(p);
    return 1;
}

int top_zhan(PSTACK pS)
{
    if( empty_zhan(pS) )
        return 0;
    return pS->pTop->data;
}


void clear_zhan(PSTACK pS)
{
    PNODE p;
    p = pS->pTop;
    while(pS->pTop->pNext != NULL)
    {
        p = pS->pTop;
        pS->pTop = pS->pTop->pNext;
        free(p);
    }
    return;
}











