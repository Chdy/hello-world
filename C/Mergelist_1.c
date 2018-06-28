/*
 --------------------------------------------------
 编写内容：链表
 功能：
 创建
 排序
 合并两个链表
 时间：2016.04.03
 --------------------------------------------------
 */
# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    int data;
    struct node * pNext;
}Node,*pNode;

pNode create_list(void);
void traverse_list(pNode);
pNode merge_list(pNode,pNode);
void sort_list(pNode);


int main(void)
{
    pNode pA = create_list();
    printf("遍历A：\n");
    sort_list(pA);
    traverse_list(pA);
    pNode pB = create_list();
    traverse_list(pB);
    sort_list(pB);
    printf("遍历B：\n");
    pNode pC= merge_list(pA,pB);
    printf("遍历C：\n");
    traverse_list(pC);
    return 0;
}

void sort_list(pNode pHead)
{
    int i;
    pNode q = pHead->pNext;
    while(q != NULL)
    {
        pNode p = q->pNext;
        while(p != NULL)
        {
            if(q->data>p->data)
            {
                i = q->data;
                q->data = p->data;
                p->data = i;
                p = p->pNext;
            }
            else
                p = p->pNext;
        }
        q = q->pNext;
    }
}

pNode merge_list(pNode pA,pNode pB)
{
    pNode pC;
    pNode ha;
    pNode hb;
    pNode hc;
    pC = hc = pA;
    ha = pA->pNext;
    hb = pB->pNext;
    while(ha && hb)
    {
        if(ha->data<=hb->data)
        {
            hc->pNext = ha;
            hc = ha;
            ha = ha->pNext;
        }
        else
        {
            hc->pNext = hb;
            hc = hb;
            hb = hb->pNext;
        }
    }
    if(ha == NULL)
        hc->pNext = hb;
    else
        hc->pNext = ha;
    free(pB);
    return pC;
}

pNode create_list(void)
{
    pNode pHead = (pNode)malloc(sizeof(Node));
    if(pHead == NULL)
        exit(-1);
    int i;
    int k;
    int t;
    printf("请输入需要的元素个数：\n");
    scanf("%d",&k);
    pNode pTail = pHead;
    for(i=0; i<k; i++)
    {
        printf("请输入第%d个元素的值:\n",i+1);
        scanf("%d",&t);
        pNode pNew = (pNode)malloc(sizeof(Node));
        pNew->data = t;
        pNew->pNext = NULL;
        pTail->pNext = pNew;
        pTail = pNew;
    }
    return pHead;
}

void traverse_list(pNode pHead)
{
    int i = 1;
    pNode p = pHead->pNext;
    while(p != NULL)
    {
        printf("该链表第%d个元素为：%d\n",i++,p->data);
        p = p->pNext;
    }
}











