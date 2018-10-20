/*
 --------------------------------------------------
 编写内容：链表
 功能：
    创建
    长度计算
    遍历
    插入
    删除
    查找
 时间：2016.03.24
 --------------------------------------------------
 */

# include <stdio.h>
# include <stdlib.h>


typedef struct node
{
    int date;
    struct node * next;
}Node,*pNode;

pNode create_list_tail();//尾插法
pNode create_list_head();//头插法
void traverse_list(pNode);
void length_list(pNode);
int insert_list(pNode,int ,int);
int delete_list(pNode,int);
int find_elem(pNode,int);
int link_list(pNode,pNode);
void unique_list(pNode);

int main(void)
{
    setbuf(stdout,NULL);
    int i,j,k;
    printf("请输入第一个数组\n");
    pNode pHead;
    pHead = create_list_head();
    traverse_list(pHead);
    /*printf("请输入想要插入的位置:");
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
    printf("请输入你想要查找的元素:\n");
    int n;
    scanf("%d",&n);
    find_elem(pHead,n)?printf("元素存在"):printf("未找到");
    printf("删除多余元素\n");
    unique_list(pHead);
    traverse_list(pHead);*/

    return 0;
}

void unique_list(pNode L)//本质上就是使用两两元素进行比较
{
    if(L == NULL || L->next == NULL) //判断是否为空链表
        return;
    pNode p;
    L = L->next;
    while(L!=NULL && L->next!=NULL)//这里必须要增加L!=NULL，因为如果含有连续的相同的数一直到结尾，那么此时在内部循环结束后进行判断时L本身会为空，对L->next的访问会造成程序终止
    {
        pNode end = L->next;
        p = L;
        while(end != NULL)
        {
            if(L->date == end->date)
            {
                p->next = end->next;
                free(end);
                end = p->next;
            }
            else {
                p = end;
                end = end->next;
            }
        }
        L = L->next;//判断下一个元素
    }
}

int find_elem(pNode T,int n)//找到返回1，没有返回0
{
    if(T->next == NULL)
        return 0;
    pNode p = T->next;
    while(p)
    {
        if(p->date == n)
           return 1;
        p = p->next;
    }
    return 0;
}

int link_list(pNode L,pNode R)
{
    if(L==NULL || R->next==NULL)
        return -1;
    pNode LL = L;
    while(LL)
    {
        L = LL;
        LL = LL->next;
    }
    L->next = R->next;
    R->next = NULL;
    return 0;
}

pNode create_list_head()//头插法
{
    int i ,len,val;
    pNode tmp;
    pNode head = (pNode)malloc(sizeof(Node));
    if(head == NULL)
        return 0;
    head->next = NULL;
    printf("请输入链表的长度:\n");
    scanf("%d",&len);
    for(i=0; i<len; i++)
    {
        printf("请输入第%d个数的值",i+1);
        scanf("%d",&val);
        pNode tmp = (pNode)malloc(sizeof(Node));
        tmp->date = val;
        tmp->next = head->next;
        head->next = tmp;
    }
    return head;
}

pNode create_list_tail()//尾插法
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
        pTail->next = pNew;
        pTail = pNew;
    }
    return pHead;
}

void traverse_list(pNode pHead)
{
    pNode p;
    int i = 1;
    p = pHead->next;
    printf("遍历:\n");
    while(p != NULL)
    {
        printf("链表第%d个数为:%d\n",i,p->date);
        i++;
        p = p->next;
    }
    
}

void length_list(pNode pHead)
{
    pNode p;
    int i = 0;
    p = pHead->next;
    while(p != NULL)
    {
        i++;
        p = p->next;
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
        p = p->next;
    }
    if(p == NULL || i>pos-1)
        return 0;
    pNode pNew = (Node *)malloc(sizeof(Node));
    pNode r;
    pNew->date = val;
    r = p->next;
    p->next = pNew;
    pNew->next = r;
    
    return 1;
}

int delete_list(pNode pHead, int pos)
{
    int i = 0;
    pNode p;
    p = pHead;
    pNode r;
    while(p->next != NULL && i<pos-1)
    {
        i++;
        p = p->next;
    }
    if(p->next == NULL || i>pos-1)
        return 0;
    r = p->next;
    p->next = p->next->next;
    free(r);
    
    return 1;
}










