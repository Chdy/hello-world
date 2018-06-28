/*--------------------------------------------------
 2016年七月三日
 十字链表处理矩阵:
 1：插入值
 2：摧毁矩阵
 3：矩阵相加
 4：矩阵相减
 5：矩阵相乘
 6：矩阵转置
 7：矩阵形式输出
 8：表格形势输出
 -------------------------------------------------*/
# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    int i;
    int j;
    int e;
    struct node * right;
    struct node * down;
}Node;

typedef struct Slist
{
    int m;
    int n;
    int t;
    Node ** rhead;
    Node ** dhead;
}Slist;

void init_Slist(Slist *);
void init_Clist(Slist *);
void create_Slist(Slist *);
void insert_Slist(Slist *,Node *);
void print_matrics(Slist *);
void print_list(Slist *);
void destroy_Slist(Slist *);
void copy_Slist(Slist *,Slist *);
void add_Slist(Slist *,Slist *,Slist *);
void sub_Slist(Slist *,Slist *,Slist *);
void mul_Slist(Slist *,Slist *,Slist *);
void trans_Slist(Slist *,Slist *);
int comp_Node(int,int);

int main(void)
{
    Slist S;
    Slist T;
    Slist Q;//相加矩阵
    Slist V;//相减矩阵
    Slist M;//相乘矩阵
    Slist P;//转置矩阵
    init_Slist(&S);
    init_Slist(&T);
    init_Slist(&Q);
    init_Slist(&V);
    init_Slist(&M);
    create_Slist(&S);
    printf("S矩阵；\n");
    print_list(&S);
    printf("--------------\n");
    print_matrics(&S);
    printf("复制矩阵：\n");
    copy_Slist(&S,&T);
    print_matrics(&T);
    destroy_Slist(&T);
    printf("--------------\n");
    printf("T矩阵：\n");
    create_Slist(&T);
    print_matrics(&T);
    printf("--------------\n");
    printf("Q=S+T矩阵\n");
    add_Slist(&S,&T,&Q);
    print_matrics(&Q);
    printf("--------------\n");
    printf("V=Q-S矩阵\n");
    sub_Slist(&Q,&S,&V);
    print_matrics(&V);
    printf("--------------\n");
    printf("M=Q*V矩阵\n");
    mul_Slist(&Q,&V,&M);
    print_matrics(&M);
    printf("--------------\n");
    printf("P转置矩阵\n");
    trans_Slist(&M,&P);
    print_matrics(&P);
}

void mul_Slist(Slist * S,Slist * T,Slist * Q)
{
    int i,j,e=0;
    Node * pm,* pn,* pq;;
    if(S->n!=T->m)
        exit(-1);
    Q->m = S->m;
    Q->n = T->n;
    init_Clist(Q);
    for(i=1;i<=Q->m;i++)
        for(j=1;j<=Q->n;j++)
        {
            pm = S->rhead[i];
            pn = T->dhead[j];
            while(pm && pn)
            {
                switch(comp_Node(pm->j,pn->i))
                {
                    case 1:
                        pn = pn->down;
                        break;
                    case 0:
                        e += pm->e * pn->e;
                        pm = pm->right;
                        pn = pn->down;
                        break;
                    case -1:
                        pm = pm->right;
                }
            }
            if(e!=0)
            {
                pq = (Node *)malloc(sizeof(Node));
                pq->i = i;
                pq->j = j;
                pq->e = e;
                e = 0;
                insert_Slist(Q,pq);
            }
        }
    if(Q->t == 0)
        destroy_Slist(Q);
}

void trans_Slist(Slist * S,Slist * T)
{
    int i;
    Node * p,* q;
    T->m = S->n;
    T->n = S->m;
    init_Clist(T);
    for(i=1;i<=S->n;i++)
    {
        p = S->dhead[i];
        while(p)
        {
            q = (Node *)malloc(sizeof(Node));
            q->i = p->j;
            q->j = p->i;
            q->e = p->e;
            insert_Slist(T,q);
            p = p->down;
        }
    }
}

void add_Slist(Slist * S,Slist * T,Slist * Q)
{
    int i;
    Node * ps, * pt, * pq;
    if(S->m!=T->m || S->n!=T->n)
        exit(-1);
    Q->m = S->m;
    Q->n = S->n;
    init_Clist(Q);
    for(i=1;i<=S->m;i++)
    {
        ps = S->rhead[i];
        pt = T->rhead[i];
        while(ps && pt)
        {
            switch(comp_Node(ps->j,pt->j))
            {
                case -1:
                    pq = (Node *)malloc(sizeof(Node));
                    *pq = *ps;
                    insert_Slist(Q,pq);
                    ps = ps->right;
                    break;
                case 0:
                    if((ps->e + pt->e)!=0)
                    {
                        pq = (Node *)malloc(sizeof(Node));
                        *pq = *ps;
                        pq->e = ps->e + pt->e;
                        insert_Slist(Q,pq);
                        ps = ps->right;
                        pt = pt->right;
                    }
                    else
                    {
                        ps = ps->right;
                        pt = pt->right;
                    }
                    break;
                case 1:
                    pq = (Node *)malloc(sizeof(Node));
                    *pq = *pt;
                    insert_Slist(Q,pq);
                    pt = pt->right;
            }
        }
        while(ps)
        {
            pq = (Node *)malloc(sizeof(Node));
            *pq = *ps;
            insert_Slist(Q,pq);
            ps = ps->right;
        }
        while(pt)
        {
            pq = (Node *)malloc(sizeof(Node));
            *pq = *pt;
            insert_Slist(Q,pq);
            pt = pt->right;
        }
    }
    if(Q->t == 0)
        destroy_Slist(Q);
}

void sub_Slist(Slist * S,Slist * T,Slist * Q)
{
    int i;
    Node * ps, * pt, * pq;
    if(S->m!=T->m || S->n!=T->n)
        exit(-1);
    Q->m = S->m;
    Q->n = S->n;
    init_Clist(Q);
    for(i=1;i<=S->m;i++)
    {
        ps = S->rhead[i];
        pt = T->rhead[i];
        while(ps && pt)
        {
            switch(comp_Node(ps->j,pt->j))
            {
                case -1:
                    pq = (Node *)malloc(sizeof(Node));
                    *pq = *ps;
                    insert_Slist(Q,pq);
                    ps = ps->right;
                    break;
                case 0:
                    if((ps->e - pt->e)!=0)
                    {
                        pq = (Node *)malloc(sizeof(Node));
                        *pq = *ps;
                        pq->e = ps->e - pt->e;
                        insert_Slist(Q,pq);
                        ps = ps->right;
                        pt = pt->right;
                    }
                    else
                    {
                        ps = ps->right;
                        pt = pt->right;
                    }
                    break;
                case 1:
                    pq = (Node *)malloc(sizeof(Node));
                    *pq = *pt;
                    pq->e = -pt->e;
                    insert_Slist(Q,pq);
                    pt = pt->right;
            }
        }
        while(ps)
        {
            pq = (Node *)malloc(sizeof(Node));
            *pq = *ps;
            insert_Slist(Q,pq);
            ps = ps->right;
        }
        while(pt)
        {
            pq = (Node *)malloc(sizeof(Node));
            *pq = *pt;
            insert_Slist(Q,pq);
            pt = pt->right;
        }
    }
    if(Q->t == 0)
        destroy_Slist(Q);
}


void insert_Slist(Slist * S,Node * n)
{
    Node * q = S->rhead[n->i];
    if(!q||n->j<q->j)
    {
        n->right = S->rhead[n->i];
        S->rhead[n->i] = n;
    }
    else
    {
        while(q->right&&q->right->j<n->j)
        {
            q = q->right;
        }
        n->right = q->right;
        q->right = n;
    }
    q = S->dhead[n->j];
    if(!q||n->i<q->i)
    {
        n->down = S->dhead[n->j];
        S->dhead[n->j] = n;
    }
    else
    {
        while(q->down&&q->down->i<n->i)
        {
            q = q->down;
        }
        n->down = q->down;
        q->down = n;
    }
    S->t++;
}

void copy_Slist(Slist * S,Slist * T)
{
    int i;
    Node * p, *q;
    T->m = S->m;
    T->n = S->n;
    init_Clist(T);
    for(i=1;i<=S->m;i++)
    {
        p = S->rhead[i];
        while(p)
        {
            q = (Node *)malloc(sizeof(Node));
            *q = *p;
            insert_Slist(T,q);
            p = p->right;
        }
    }
}

void init_Clist(Slist * S)
{
    int i;
    S->rhead = (Node **)malloc(sizeof(Node *) * (S->m + 1));
    S->dhead = (Node **)malloc(sizeof(Node *) * (S->n + 1));
    if(!S->rhead || !S->dhead)
        exit(-1);
    for(i=1;i<=S->m;i++)
    {
        S->rhead[i] = NULL;
    }
    for(i=1;i<=S->n;i++)
    {
        S->dhead[i] = NULL;
    }
}

void create_Slist(Slist * S)
{
    int i,k;
    Node * q;
    printf("请依次输入行数，列数，以及非零元的个数：");
    scanf("%d,%d,%d",&S->m,&S->n,&i);
    init_Clist(S);
    printf("请依次输入%d个元素的行，列，和元素值：\n",i);
    for(k=1;k<=i;k++)
    {
        q = (Node *)malloc(sizeof(Node));
        scanf("%d,%d,%d",&q->i,&q->j,&q->e);
        insert_Slist(S,q);
    }
}

void print_matrics(Slist * S)
{
    int i,j;
    Node * p;
    for(i=1;i<=S->m;i++)
    {
        p = S->rhead[i];
        for(j=1;j<=S->n;j++)
        {
            if(p==NULL || j!=p->j)
            {
                printf(" 0");
            }
            else
            {
                printf("%2d",p->e);
                p = p->right;
            }
        }
        printf("\n");
    }
}

void print_list(Slist * S)
{
    int x,i;
    Node * q;
    printf("请选在按行输出还是按列输出，按行输出请按1，按列输出请按2:");
    scanf("%d",&x);
    switch(x)
    {
        case 1:
            printf("行  列    值\n");
            for(i=1;i<=S->m;i++)
            {
                q = S->rhead[i];
                while(q)
                {
                    printf("%2d%4d%6d\n",q->i,q->j,q->e);
                    q = q->right;
                }
            }
            break;
        case 2:
            printf("行  列    值\n");
            for(i=1;i<=S->n;i++)
            {
                q = S->dhead[i];
                while(q)
                {
                    printf("%2d%4d%6d\n",q->i,q->j,q->e);
                    q = q->down;
                }
            }
    }
}

void destroy_Slist(Slist * S)
{
    int i;
    Node * p,* q;
    for(i=1;i<=S->m;i++)
    {
        p = S->rhead[i];
        while(p)
        {
            q = p->right;
            free(p);
            p = q;
        }
    }
    free(S->rhead);
    free(S->dhead);
    init_Slist(S);
}

void init_Slist(Slist * S)
{
    S->m = 0;
    S->n = 0;
    S->t = 0;
    S->rhead = NULL;
    S->dhead = NULL;
}

int comp_Node(int a,int b)
{
    if(a<b)
        return -1;
    if(a==b)
        return 0;
    return 1;
}