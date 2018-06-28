/*
 --------------------------------------------------
 编写内容：循环队列
 功能：
    创建
    遍历
    入队
    出队
 时间：2016.03.26
 --------------------------------------------------
 */
# include <stdio.h>
# include <stdlib.h>

typedef struct queue
{
    int * pBase;
    int front;
    int rear;
}QUEUE;

void init_queue(QUEUE *);
void en_queue(QUEUE *,int);
int full_queue(QUEUE *);
int empty_queue(QUEUE *);
void traverse_queue(QUEUE *);
int delete_queue(QUEUE *,int *);

int main(void)
{
    int val;
    QUEUE Q;
    init_queue(&Q);
    en_queue(&Q,1);
    en_queue(&Q,2);
    en_queue(&Q,3);
    en_queue(&Q,4);
    en_queue(&Q,5);
    en_queue(&Q,6);
    en_queue(&Q,7);
    traverse_queue(&Q);
    if ( delete_queue(&Q,&val) )
        printf("出队成功！出队的值为:%d\n",val);
    else
        printf("失败!队列为空\n");
    traverse_queue(&Q);
    
    
    return 0;
}

void init_queue(QUEUE * pQ)
{
    pQ->pBase = (int *)malloc(sizeof(int) * 6);
    if( pQ->pBase == NULL )
    {
        printf("分配失败！");
        exit(-1);
    }
    pQ->front = 0;
    pQ->rear = 0;
    return;
}

int full_queue(QUEUE * pQ)
{
    if( (pQ->rear+1)%6 == pQ->front )
        return 1;
    else
        return 0;
}

int empty_queue(QUEUE *pQ)
{
    if( pQ->rear == pQ->front )
        return 1;
    else
        return 0;
}

void en_queue(QUEUE * pQ,int val)
{
    if( full_queue(pQ) )
        return;
    pQ->pBase[pQ->rear] = val;
    pQ->rear = (pQ->rear+1)%6;
    return;
}

void traverse_queue(QUEUE * pQ)
{
    int p = pQ->front;
    while( p%6 != pQ->rear )
    {
        printf("---%d\n",pQ->pBase[p]);
        p++;
    }
        return;
}

int delete_queue(QUEUE * pQ,int * val)
{
    if( empty_queue(pQ) )
        return 0;
    *val = pQ->pBase[pQ->front];
    pQ->front = (pQ->front+1)%6;
    return 1;
}








