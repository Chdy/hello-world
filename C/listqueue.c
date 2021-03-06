# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    int data;
    struct node * pNext;
}Node,*pNode;

typedef struct queue
{
    struct node * front;
    struct node * rear;
}Queue,*pQueue;

void init_queue(pQueue);
void insert_queue(pQueue,int);
int delete_queue(pQueue,int *);
void traverse_queue(pQueue);
void destroy_queue(pQueue);

int main(void)
{
    int val;
    Queue T;
    init_queue(&T);
    insert_queue(&T,12);
    insert_queue(&T,2);
    insert_queue(&T,5);
    traverse_queue(&T);
    if( delete_queue(&T,&val) )
    {
        printf("删除成功！删除的值为%d\n",val);
    }
    traverse_queue(&T);
    destroy_queue(&T);
    traverse_queue(&T);
    return 0;
}

void destroy_queue(pQueue p)
{
    pNode r = p->rear;
    while(p->rear != p->front)
    {
        p->rear = r->pNext;
        free(r);
        r = p->rear;
    }
    free(r);
}

void traverse_queue(pQueue p)
{
    int i = 1;
    pNode q = p->rear;
    while(q != p->front)
    {
        printf("第%d个数为%d\n",i++,q->data);
        q = q->pNext;
    }
}

int delete_queue(pQueue p,int * val)
{
    if( p->front == p->rear )
    {
        printf("队列为空，删除失败！\n");
        return 0;
    }
    *val = p->rear->data;
    pNode r = p->rear;
    p->rear = p->rear->pNext;
    free(r);
    return 1;
}

void insert_queue(pQueue p,int val)
{
    pNode pNew = (pNode)malloc(sizeof(Node));
    p->front->data = val;
    p->front->pNext = pNew;
    p->front = pNew;
}

void init_queue(pQueue p)
{
    p->front = (pNode)malloc(sizeof(Node));
    if(p->front == NULL)
    {
        printf("分配失败！\n");
        exit(-1);
    }
    p->front->pNext = NULL;
    p->rear = p->front;
}