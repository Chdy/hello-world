# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    struct node * left,* right;
    char data;
}Node;

typedef struct queue
{
    struct queue * next;
    Node * data;
}Queue;

void visit(char c)
{
    printf("%c",c);
}

void init_tree(Node **);
void destroy_tree(Node **);
void pre_traverse(Node *,void(char));
void pre_create_tree(Node **);
int depth_tree(Node *);
char parent_tree(Node *,char);

int main(void)
{
    Node * S;
    pre_create_tree(&S);
    pre_traverse(S,visit);
    printf("\n");
    printf("S的深度是:%d\n",depth_tree(S));
    printf("parent = %c\n",parent_tree(S,'3'));
    return 0;
}

char parent_tree(Node * S,char e)
{
    Queue * q,* p;
    Queue * head,* tail;
    if(S)
    {
        q = (Queue *)malloc(sizeof(Queue));
        head = tail = (Queue *)malloc(sizeof(Queue));
        head->data = S;
        head->next = q;
        q->next = NULL;
        head = q;
        while(tail!=head)
        {
            q = tail;
            tail = q->next;
            if((q->data->left&&(q->data->left->data==e))||(q->data->right&&(q->data->right->data==e)))
                return q->data->data;
            else
            {
                if(q->data->left)
                {
                    p = (Queue *)malloc(sizeof(Queue));
                    head->data = q->data->left;
                    head->next = p;
                    p->next = NULL;
                    head = p;
                }
                if(q->data->right)
                {
                    p = (Queue *)malloc(sizeof(Queue));
                    head->data = q->data->right;
                    head->next = p;
                    p->next = NULL;
                    head = p;
                }
            }
            free(q);
        }
    }
    return 1;
}

int depth_tree(Node * S)
{
    int i;
    if(!S)
    {
        return 0;
    }
    else
    {
        i = depth_tree(S->left);
        if(i<depth_tree(S->right))
            i = depth_tree(S->right);
        return i+1;
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
        pre_create_tree(&(*S)->right);
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