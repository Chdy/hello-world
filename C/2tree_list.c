# include <stdio.h>
# include <stdlib.h>

//先序输入树，然后输出
//递归遍历
//非递归中序遍历

# define size 100
# define extend 10

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

typedef struct stack
{
    Node ** pTop;
    Node ** pBottom;
    int stacksize;
}Stack,*pStack;

void visit(char c)
{
    printf("%c",c);
}

void init_tree(Node **);
void destroy_tree(Node **);
void pre_traverse(Node *,void(char));
void pre_create_tree(Node **);
void in_traverse(Node *,void(char));
void in_traverse_use_stack(Node *);
int depth_tree(Node *);
char parent_tree(Node *,char);
void init_stack(pStack);
void push_stack(pStack,Node *);
int pop_stack(pStack,Node **);
int empty_stack(pStack);


int main(void) //  ***-+a00*b00-c00d00/e00f00***输入 abd000ce000, 0换为空格作为输入
{
    Node * S;
    printf("按先序输入创建二叉树：");
    pre_create_tree(&S);
    printf("先序遍历: ");
    pre_traverse(S,visit);
    printf("\n");
    printf("中序遍历: ");
    in_traverse(S,visit);
    printf("\n");
    printf("非递归中序遍历: ");
    in_traverse_use_stack(S);
    printf("\n");
    printf("S的深度是:%d\n",depth_tree(S));
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

void in_traverse_use_stack(Node * S) //非递归中序遍历树
{
    Stack stack;
    init_stack(&stack);
    Node * p;

    while (S || !empty_stack(&stack)) {
        if (S) {
            push_stack(&stack, S);
            S = S->left;
        } else {
            pop_stack(&stack, &S);
            printf("%c", S->data);
            S = S->right;
        }
    }

}

void in_traverse(Node * S,void v(char)) //中序遍历
{
    if(S)
    {
        in_traverse(S->left,v);
        v(S->data);
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

int pop_stack(pStack S,Node ** val)
{
    /*if( empty_stack(S) )
    {
        printf("栈为空！\n");
        exit(-1);
    }*/
    *val = *--(S->pTop);
    return 0;
}

void push_stack(pStack S,Node * val)
{
    if(S->pTop-S->pBottom == S->stacksize)
    {
        S->pBottom = (Node **)realloc(S->pBottom,(S->stacksize + extend)*sizeof(Node *));
        S->stacksize += extend;
    }
    *(S->pTop)++ = val;
}

void init_stack(pStack S)
{
    S->pBottom = (Node **)malloc(sizeof(Node *)*size);
    S->pTop = S->pBottom;
    S->stacksize = size;
}

int empty_stack(pStack S)
{
    if(S->pTop == S->pBottom)
        return 1;
    else
        return 0;
}