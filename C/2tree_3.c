# include <stdio.h>
# include <stdlib.h>

typedef struct Node
{
    char data;
    struct Node * left, * right, * parent;
}Node,*pNode;

typedef struct queue
{
    struct queue * next;
    pNode node;
}queue;

void initial_tree(pNode *);
void destroy_tree(pNode *);
void create_tree(pNode *);
int depth_tree(pNode);
char parent_tree(pNode,char);
pNode point(pNode,char);

int main(void)
{
    pNode S;
    pNode q;
    create_tree(&S);
    printf("该树的深度为:%d\n",depth_tree(S));
    printf("3节点的父亲是:%c\n",parent_tree(S,'3'));
    return 0;
}

pNode point(pNode S,char c)
{
    if(S)
    {
        queue * head = (queue *)malloc(sizeof(queue));
        queue * rear = head;
        queue * q = (queue *)malloc(sizeof(queue));
        queue * p;
        head->node = S;
        head->next = q;
        head = q;
        while(head!=rear)
        {
            q = rear;
            rear = rear->next;
            if(q->node->data==c)
                return q->node;
            else
            {
                if(q->node->left)
                {
                    p = (queue *)malloc(sizeof(queue));
                    head->node = q->node->left;
                    head->next = p;
                    head = p;
                }
                if(q->node->right)
                {
                    p = (queue *)malloc(sizeof(queue));
                    head->node = q->node->right;
                    head->next = p;
                    head = p;
                }
            }
            free(q);
        }
    }
    return NULL;
}

char parent_tree(pNode S,char c)
{
    pNode p;
    p = point(S,c);
    printf("%c\n",p->data);
    if(p!=S)
        return p->parent->data;
    return 0;
}

void create_tree(pNode * S)
{
    char c;
    scanf("%c",&c);
    if(c==' ')
        *S = NULL;
    else
    {
        *S = (pNode)malloc(sizeof(Node));
        (*S)->data = c;
        (*S)->parent = NULL;
        create_tree(&(*S)->left);
        if((*S)->left)
            (*S)->left->parent = *S;
        create_tree(&(*S)->right);
        if((*S)->right)
            (*S)->right->parent = *S;
    }
}

int depth_tree(pNode S)
{
    int i,j;
    if(!S)
        return 0;
    i = depth_tree(S->left);
    j = depth_tree(S->right);
    return i>j?i+1:j+1;
}

void destroy_tree(pNode * S)
{
    if((*S)->left)
        destroy_tree(&(*S)->left);
    if((*S)->right)
        destroy_tree(&(*S)->right);
    free(*S);
    *S = NULL;
}

void initial_tree(pNode * S)
{
    *S = NULL;
}
