/*
 --------------------------------------------------
 编写内容：双向链表
 功能：
 创建
 遍历
 插入
 删除
 时间：2016.04.04
 --------------------------------------------------
 */
# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    int data;
    struct node * pLast;
    struct node * pNext;
}Node,*pNode;

pNode create_list(void);
void traverse_list(pNode);
int insert_list(pNode,int,int);
int empty_list(pNode);
int delete_list(pNode,int,int *);

int main(void)
{
    int val;
    pNode pHead = create_list();
    traverse_list(pHead);
    if( insert_list(pHead,1,5) )
        printf("插入成功!\n");
    traverse_list(pHead);
    if( delete_list(pHead,1,&val) )
        printf("删除成功！删除的值为：%d\n",val);
    traverse_list(pHead);
    return 0;
}

int empty_list(pNode pHead)
{
    if(pHead->pNext == NULL)
        return 1;
    else
        return 0;
}

int delete_list(pNode pHead,int pos,int * val)
{
    if( empty_list(pHead) )
        return 0;
    int i = 0;
    pNode p = pHead;
    while(p->pNext != NULL && i<pos-1)
    {
        p = p->pNext;
        i++;
    }
    if(p->pNext == NULL || i>pos-1)
        return 0;
    else
    {
        if(p->pNext == NULL)
        {
            *val = p->pNext->data;
            free(p->pNext);
            p->pNext = NULL;
        }
        else
        {
            *val = p->pNext->data;
            pNode q;
            q = p->pNext;
            p->pNext = p->pNext->pNext;
            q->pNext->pLast = p;
            free(q);
        }
    }
    return 1;
    
}

int insert_list(pNode pHead, int pos, int val)
{
    int i = 0;
    pNode p = pHead;
    while(p != NULL && i<pos-1)
    {
        p = p->pNext;
        i++;
    }
    if(p == NULL || i>pos-1)
        return 0;
    pNode pNew = (pNode)malloc(sizeof(Node));
    if(p->pNext == NULL)
    {
        pNew->data = val;
        pNew->pLast = p;
        p->pNext = pNew;
    }
    else
    {
        pNew->data = val;
        pNew->pNext = p->pNext;
        p->pNext->pLast = pNew;
        p->pNext = pNew;
        pNew->pLast = p;
    }
    return 1;
}

void traverse_list(pNode pHead)
{
    pNode p = pHead;
    int i = 1;
    while(p->pNext != NULL)
    {
        printf("该链表第%d个数为：%d\n",i++,p->pNext->data);
        p = p->pNext;
    }
}

pNode create_list(void)
{
    int n;
    int i;
    int val;
    pNode pHead = (pNode)malloc(sizeof(Node));
    if(pHead == NULL)
    {
        printf("内存分配失败！\n");
        exit(-1);
    }
    pNode p = pHead;
    printf("请输入链表的长度：\n");
    scanf("%d",&n);
    for(i=1; i<=n; i++)
    {
        printf("请输入第%d个结点的值：\n",i);
        scanf("%d",&val);
        pNode pNew = (pNode)malloc(sizeof(Node));
        pNew->pNext = NULL;
        pNew->data = val;
        p->pNext = pNew;
        pNew->pLast = p;
        p = pNew;
    }
    return pHead;
}












