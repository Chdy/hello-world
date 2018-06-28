/*
 --------------------------------------------------
 编写内容：链表
 功能：
    创建
    长度计算
    遍历
    插入
    删除
 时间：2016.03.24
 --------------------------------------------------
 */

# include <stdio.h>
# include <stdlib.h>


typedef struct node
{
    int date;
    struct node * pNext;
}Node,*pNode;

pNode create_list();
void traverse_list(pNode);
void length_list(pNode);
int insert_list(pNode,int ,int);
int delete_list(pNode,int);

int main(void)
{
    int i,j,k;
    pNode pHead;
    pHead = create_list();
    traverse_list(pHead);
    printf("请输入想要插入的结点:");
    scanf("%d",&i);
    printf("请输入想要插入的数:");
    scanf("%d",&j);
    if( insert_list(pHead,i,j) )
        printf("插入成功!\n");
    else
        printf("删除失败!\n");
    traverse_list(pHead);
    printf("请输入想要删除的结点:");
    scanf("%d",&k);
    if( delete_list(pHead,k) )
        printf("删除成功!\n");
    else
        printf("删除失败!\n");
    length_list(pHead);
    traverse_list(pHead);
    return 0;
}

pNode create_list()
{
    int len;
    int val;
    int i;
    pNode pHead = (Node *)malloc(sizeof(Node));
    if(pHead == NULL)
    {
        printf("创建失败！");
        exit(-1);
    }
    pNode pTail;
    pTail = pHead;
    printf("请输入链表的长度:\n");
    scanf("%d",&len);
    for(i=0; i<len; i++)
    {
        printf("请输入第%d个数的值",i+1);
        scanf("%d",&val);
        pNode pNew = (Node *)malloc(sizeof(Node));
        pNew->date = val;
        pTail->pNext = pNew;
        pTail = pNew;
    }
    return pHead;
}

void traverse_list(pNode pHead)
{
    pNode p;
    int i = 1;
    p = pHead->pNext;
    printf("遍历:\n");
    while(p != NULL)
    {
        printf("链表第%d个数为:%d\n",i,p->date);
        i++;
        p = p->pNext;
    }
    
}

void length_list(pNode pHead)
{
    pNode p;
    int i = 0;
    p = pHead->pNext;
    while(p != NULL)
    {
        i++;
        p = p->pNext;
    }
    printf("该链表长度为%d\n",i);
}

int insert_list(pNode pHead,int pos,int val)
{
    int i = 0;
    pNode p;
    p = pHead;
    while(p != NULL && i<pos-1)
    {
        i++;
        p = p->pNext;
    }
    if(p == NULL || i>pos-1)
        return 0;
    pNode pNew = (Node *)malloc(sizeof(Node));
    pNode r;
    pNew->date = val;
    r = p->pNext;
    p->pNext = pNew;
    pNew->pNext = r;
    
    return 1;
}

int delete_list(pNode pHead, int pos)
{
    int i = 0;
    pNode p;
    p = pHead;
    pNode r;
    while(p->pNext != NULL && i<pos-1)
    {
        i++;
        p = p->pNext;
    }
    if(p->pNext == NULL || i>pos-1)
        return 0;
    r = p->pNext;
    p->pNext = p->pNext->pNext;
    free(r);
    
    return 1;
}










