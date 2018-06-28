/*------------------------------------------
 线索二叉树的创建以及遍历
 先序和中序
 先生成普通二叉树
 然后进行线索处理
 -----------------------------------------*/
# include <stdio.h>
# include <stdlib.h>

enum Tag
{
    link,thread
};

typedef struct node
{
    char data;
    struct node * right, *left;
    enum Tag rtag,ltag;
}Node,*pNode;

pNode pre;

void visit(char c)
{
    printf("%c",c);
}

void create_tree(pNode *);
void mid_order(pNode);
void mid_order_thread(pNode *,pNode);
void mid_order_traverse(pNode,void(char));
void pre_order(pNode);
void pre_order_thread(pNode *,pNode);
void pre_order_traverse(pNode,void(char));

int main(void)
{
    pNode S;
    pNode T;
    create_tree(&S);
        //mid_order_thread(&T,S);
        //mid_order_traverse(T,visit);
    pre_order_thread(&T,S);
    pre_order_traverse(T,visit);
    return 0;
}

void create_tree(pNode * S)//按先序生成树
{
    char ch;
    scanf("%c",&ch);
    if(ch==' ')
    {
        *S = NULL;
    }
    else
    {
        *S = (pNode)malloc(sizeof(Node));
        (*S)->data = ch;
        create_tree(&(*S)->left);
        if((*S)->left)
            (*S)->ltag = link;
        create_tree(&(*S)->right);
        if((*S)->right)
            (*S)->rtag = link;
    }
}

void mid_order_traverse(pNode S,void v(char c))
{
    pNode p = S->left;
    while(p!=S)
    {
        while(p->ltag==link)
            p = p->left;
        v(p->data);
        while(p->rtag==thread&&p->right!=S)
        {
            p = p->right;
            v(p->data);
        }
        p = p->right;
    }
}

void mid_order_thread(pNode * S,pNode p)
{
    *S = (pNode)malloc(sizeof(Node));
    (*S)->ltag = link;
    (*S)->rtag = thread;
    (*S)->right = *S;
    if(!p)
    {
        (*S)->left = (*S);
    }
    else
    {
        (*S)->left = p;
        pre = *S;
        mid_order(p);
        pre->right = *S;
        pre->rtag = thread;
        (*S)->right = pre;
    }
}

void mid_order(pNode p)
{
    if(p)
    {
        mid_order(p->left);
        if(!p->left)
        {
            p->left = pre;
            p->ltag = thread;
        }
        if(!pre->right)
        {
            pre->right = p;
            pre->rtag = thread;
        }
        pre = p;
        mid_order(p->right);
    }
}

void pre_order(pNode p)
{
    if(p)
    {
        if(!p->left)
        {
            p->left = pre;
            p->ltag = thread;
        }
        if(!pre->right)//这里是pre不是p
        {
            pre->right = p;
            pre->rtag = thread;
        }
        pre = p;
        if(p->ltag==link)
            pre_order(p->left);
        if(p->rtag==link)
            pre_order(p->right);
    }
}

void pre_order_thread(pNode * S,pNode p)
{
    *S = (pNode)malloc(sizeof(Node));
    (*S)->ltag = link;
    (*S)->rtag = thread;
    (*S)->right = *S;
    if(!p)
    {
        (*S)->left = *S;
    }
    else
    {
        (*S)->left = p;
        pre = *S;
        pre_order(p);
        pre->rtag = thread;
        pre->right = *S;
        (*S)->right = pre;
    }
}

void pre_order_traverse(pNode S,void v(char c))
{
    pNode p = S->left;
    while(p!=S)
    {
        v(p->data);
        if(p->ltag==link)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
}





