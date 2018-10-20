//
// Created by 邓岩 on 2018/10/3.
//

# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    double x;//系数
    int y;
    struct node * next;
}Node,*pNode;

void print_ploy(pNode head);
void init_ploy(pNode * head);
void evaluate_ploy(pNode,pNode,pNode *);
pNode find_y(pNode,int y);
void free_ploy(pNode * head);

int main(void)
{
    char c;
    pNode ploy1;
    pNode ploy2;
    pNode result;
    printf("请输入第一个多项式:\n");
    init_ploy(&ploy1);
    printf("请输入第二个多项式:\n");
    init_ploy(&ploy2);
    evaluate_ploy(ploy1,ploy2,&result);
    print_ploy(result);
    free_ploy(&ploy1);
    free_ploy(&ploy2);
    free_ploy(&result);
    return 0;
}

void free_ploy(pNode * head)
{
    pNode p = *head;
    *head = NULL;
    pNode q;
    while(p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

pNode find_y(pNode T,int y)
{
   while(T->next!=NULL)
   {
       T = T->next;
       if(T->y == y)
           return T;
   }
   return NULL;
}

void evaluate_ploy(pNode L,pNode R,pNode * result)
{
    *result = (pNode)malloc(sizeof(Node));
    pNode head = *result;
    head->y = INT16_MAX;//去掉这样插入后是无序的
    pNode tmp;
    pNode RR = R;
    head->next = NULL;
    while(L->next!=NULL)
    {
        L = L->next;
        double lx = L->x;
        int ly = L->y;
        while(R->next!=NULL)
        {
            R = R->next;
            double rx = R->x;
            int ry = R->y;
            if(lx * rx != 0)
            {
                if((tmp = find_y(*result,ly+ry)) != NULL)
                    tmp->x += lx * rx;
                else
                {
                    tmp = (pNode)malloc(sizeof(Node));
                    tmp->x = lx * rx;
                    tmp->y = ly + ry;
                    tmp->next = NULL;
                    pNode index = head->next;
                    while(head!=NULL)
                    {
                        if(head->y > tmp->y && head->next && head->next->y < tmp->y)
                        {
                            index = head;
                            break;
                        }
                        index = head;
                        head = head->next;
                    }
                    tmp->next = index->next;
                    index->next = tmp;
                    head = *result;
                }
            }
        }
        R = RR;
    }
}

void init_ploy(pNode * head)
{
    char c;
    *head = (pNode)malloc(sizeof(Node));//设置一个头节点
    pNode end = *head;//方便使用尾插法
    end->next = NULL;
    pNode tmp;
    while(1)
    {
        if((c = getchar()) == '(')
        {
            tmp = (pNode)malloc(sizeof(Node));
            tmp->next = NULL;
            end->next = tmp;
            end = tmp;
            scanf("%lf",&(tmp->x));
            getchar();//抛弃空格
            scanf("%d",&(tmp->y));
        }
        else if(c == '$')
            break;
    }
}

void print_ploy(pNode head)
{
    if(head->next!=NULL)//对第一个输出特殊处理
    {
        head = head->next;
        if(head->x==0)
            ;
        else
            printf("%.1lf",head->x);
        head->y?printf("x^%d",head->y):0;
    }
    while(head->next!=NULL)
    {
        head = head->next;
        if(head->x==0)
            continue;
        else if(head->x > 0)
            printf("+%.1lf",head->x);
        else
            printf("%.1lf",head->x);
        head->y?printf("x^%d",head->y):0;
    }
}