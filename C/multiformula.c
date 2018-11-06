/*
 --------------------------------------------------
 编写内容：多项式链表
 功能：
 创建
 遍历
 多项式相加
 时间：2016.04.07
 --------------------------------------------------
 */
# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    int xs;
    int zs;
    struct node * pNext;
}Node,*pNode;

pNode create_list();
void traverse_list(pNode);
void add_list(pNode,pNode);
void print_ploys(pNode head);

int main(void)
{
    pNode pA = create_list();
    printf("遍历表A：\n");
    print_ploys(pA);
    pNode pB = create_list();
    printf("遍历表B：\n");
    print_ploys(pA);
    add_list(pA,pB);
    printf("遍历表C：\n");
    print_ploys(pA);
    return 0;
}

void add_list(pNode pA,pNode pB)
{
    pNode ha = pA;
    pNode hb = pB;
    pNode pa = ha->pNext;
    pNode pb = hb->pNext;
    pNode q;
    while(pa && pb)
    {
        printf("运行38行！\n");
        if(pa->zs < pb->zs)
        {
            printf("运行40行！\n");
            ha->pNext = pa;
            ha = pa;
            pa = pa->pNext;
        }
        else if(pa->zs == pb->zs)
        {
            if( (pa->xs+pb->xs) == 0)
            {
                printf("运行50行！\n");
                q = pa;
                pa = pa->pNext;
                free(q);
                q = pb;
                pb = pb->pNext;
                free(q);
            }
            else
            {
                printf("运行60行！\n");
                pa->xs += pb->xs;
                ha->pNext = pa;
                ha = pa;
                pa = pa->pNext;
                q = pb;
                pb = pb->pNext;
                free(q);
            }
        }
        else
        {
            printf("运行72行！\n");
            ha->pNext = pb;
            ha = pb;
            pb = pb->pNext;
        }
    }
    if(pa == NULL)
    {
        printf("运行80\n");
        ha->pNext = pb;
    }
    else
    {
        printf("运行85\n");
        ha->pNext = pa;
    }
    free(pB);
    return;
}

void print_ploys(pNode head)
{
    if(head->pNext!=NULL)//对第一个输出特殊处理
    {
        head = head->pNext;
        if(head->xs==0)
            ;
        else
            printf("%d",head->xs);
        head->zs?printf("x^%d",head->zs):0;
    }
    while(head->pNext!=NULL)
    {
        head = head->pNext;
        if(head->xs==0)
            continue;
        else if(head->xs > 0)
            printf("+%d",head->xs);
        else
            printf("%d",head->xs);
        head->zs?printf("x^%d",head->zs):0;
    }
    printf("\n");
}

void traverse_list(pNode pHead)
{
    int i = 1;
    pNode p = pHead->pNext;
    while(p != NULL)
    {
        printf("第%d项的系数：%d",i,p->xs);
        printf("指数：%d\n",p->zs);
        p = p->pNext;
        i++;
    }
}

pNode create_list()
{
    int n;
    int i;
    int xs;
    int zs;
    pNode pHead = (pNode)malloc(sizeof(Node));
    if(pHead == NULL)
    {
        printf("分配失败！\n");
        exit(-1);
    }
    pHead->pNext = NULL;
    pNode pTail = pHead;
    printf("请输入你需要的结点个数：\n");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        pNode pNew = (pNode)malloc(sizeof(Node));
        pNew->pNext = NULL;
        printf("请输入第%d项的系数：",i);
        scanf("%d",&xs);
        pNew->xs = xs;
        printf("------------指数：");
        scanf("%d",&zs);
        pNew->zs = zs;
        while(pTail && pTail->pNext && pTail->pNext->zs < zs) //找到合适的插入点
            pTail = pTail->pNext;
        pNew->pNext = pTail->pNext;
        pTail->pNext = pNew;
        pTail = pHead;
    }
    return pHead;
}














