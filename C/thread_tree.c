//
// Created by 邓岩 on 2018/11/20.
//

# include <stdio.h>
# include <stdlib.h>


# define leaf 1

typedef struct node
{
    struct node * left,* right;
    char data;
    int ltag;
    int rtag;
}Node;


void visit(char c)
{
    printf("%c",c);
}

void init_tree(Node **);
void destroy_tree(Node **);
void pre_traverse(Node *,void(char));
void pre_create_tree(Node **);
void in_traverse(Node *,void(char));
void threadlize_tree(Node *);

Node * pre;

int main(void) //  ***-+a00*b00-c00d00/e00f00***输入 abd000ce000, 0换为空格作为输入
{
    Node * S;
    pre_create_tree(&S);
    pre_traverse(S,visit);
    printf("\n");
    in_traverse(S,visit);
    printf("\n");
    return 0;
}

void threadlize_tree(Node * S)
{

}

void in_create_tree(Node ** S)
{
    char ch;
    scanf("%c",&ch);//例如输入12  3  ;
    if(ch==' ')
    {
        *S = NULL;
    }
    else
    {
        pre_create_tree(&(*S)->left);
        *S = (Node *)malloc(sizeof(Node));
        (*S)->data = ch;
        pre_create_tree(&(*S)->right);
    }
}

void in_traverse(Node * S,void v(char)) //中序遍历
{
    if(S)
    {
        if (S->ltag != leaf)
            in_traverse(S->left,v);
        v(S->data);
        if (S->rtag != leaf)
            in_traverse(S->right,v);
    }
}

void pre_create_tree(Node ** S)
{
    char ch;
    scanf("%c",&ch);//例如输入12  3  ;
    if(ch==' ')
    {
        *S = NULL;
    }
    else
    {
        *S = (Node *)malloc(sizeof(Node));
        (*S)->data = ch;
        pre_create_tree(&(*S)->left);
        if ((*S)->left == 0)
            (*S)->ltag = leaf;
        pre_create_tree(&(*S)->right);
        if ((*S)->right == 0)
            (*S)->rtag = leaf;
    }
}

void pre_traverse(Node * S,void v(char))
{
    if(S)
    {
        v(S->data);
        pre_traverse(S->left,v);
        pre_traverse(S->right,v);
    }
}

void destroy_tree(Node ** S)
{
    if(*S)
    {
        destroy_tree(&(*S)->left);
        destroy_tree(&(*S)->right);
        free(*S);
        *S = NULL;
    }
}

void init_tree(Node ** S)
{
    *S = NULL;
}