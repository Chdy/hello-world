/*-----------------------------------------
 树的孩子-兄弟表示法
 ------------------------------------------*/
//
// Created by Vain loser on 14/11/2016.
//
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct node
{
    char data;
    struct node * child,* sibling;
}node;

typedef struct qn
{
    struct node * p;
    struct qn * next;
}qn;

void create_tree(node **);
void traverse_layer(node *);
void print_tree(node * S)
{
    if(S)
    {
        printf("%2c",S->data);
        if(S->child)
        {
            //printf("child:\n");
            print_tree(S->child);
        }
        if(S->sibling)
        {
            //printf("sibling");
            print_tree((S->sibling));
        }
    }
}

int main(void)
{
    node * S;
    create_tree(&S);
    traverse_layer(S);
    //print_tree(S);
    return 0;
}

void create_tree(node ** S)
{
    int i;
    size_t l;
    char c[20];
    qn * first;
    qn * rear;
    node * p;
    qn * q;
    printf("请输入根结点:");
    scanf("%c%*c",&c[0]);
    if(c[0] != ' ')
    {
        *S = (node *)malloc(sizeof(node));
        (*S)->data = c[0];
        (*S)->sibling = NULL;
        first = rear = (qn *)malloc(sizeof(qn));
        first->p = *S;
        first = (qn *)malloc(sizeof(qn));
        rear->next = first;
        while(first!=rear)
        {
            p = rear->p;
            q = rear;
            rear = rear->next;
            free(q);
            printf("请输入结点%c的子结点:",p->data);
            gets(c);
            if(c[0]==' ')
            {
                p->child = NULL;
                continue;
            }
            l = strlen(c);
            p->child = (node *)malloc(sizeof(node));
            p = p->child;
            p->data = c[0];
            p->child = NULL;
            for(i=1;i<l;i++)
            {
                p->sibling = (node *)malloc(sizeof(node));
                first->p = p;
                q = (qn *)malloc(sizeof(qn));
                first->next = q;
                first = q;
                p->sibling->data = c[i];
                p = p->sibling;
            }
            p->sibling = NULL;
            first->p = p;
            q = (qn *)malloc(sizeof(qn));
            first->next = q;
            first = q;
        }
    }
    else
        *S = NULL;
}

void traverse_layer(node * S)
{
    qn * q;
    node * p;
    qn * first,* rear;
    if(S)
    {
        printf("%c",S->data);
        rear = (qn *)malloc(sizeof(qn));
        rear->p = S;
        first = (qn *)malloc(sizeof(qn));
        rear->next = first;
        while(first!=rear)
        {
            p = rear->p;
            q = rear;
            rear = rear->next;
            free(q);
            p = p->child;
            while(p)
            {
                printf("%c",p->data);
                q = (qn *)malloc(sizeof(qn));
                first->p = p;
                first->next = q;
                first = q;
                p = p->sibling;
            }
        }
    }
}
