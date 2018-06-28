/*-----------------------------------------
 树的双亲表示法
 ------------------------------------------*/

# include <stdio.h>
# include <stdlib.h>

# define Maxsize 100

typedef struct node
{
    char data;
    int parent;
}Node,*pNode;

typedef struct qn
{
    char data;
    int num;
    struct qn * next;
}qN;

typedef struct tree
{
    Node p[Maxsize];
    int n;
}tree;

int strlen(char *);
void print(tree *);
void init_tree(tree *);
void create_tree(tree *);
void traverse_tree(tree *);
int depth_tree(tree *);
void assign_tree(tree *,char,char);
char left_child(tree *,char);
int insert_tree(tree *,char,int,tree);


int main(void)
{
    tree S;
    create_tree(&S);
    print(&S);
    printf("将a改为x\n");
    assign_tree(&S,'a','x');
    traverse_tree(&S);
    printf("b的第一个左子树为:%c\n",left_child(&S,'b'));
    printf("THe depth of this tree  is %d\n",depth_tree(&S));
    return 0;
}

void create_tree(tree * S)
{
    qN *p,q;
    int i = 1;
    int j,l;
    char c[Maxsize];
    init_tree(S);
    printf("请输入根节点的值，字符型：\n");
    scanf("%c%*c",&S->p[0].data);
    if(S->p[0].data != ' ')
    {
        S->p[0].parent = -1;
        qN * first;
        qN * rear;
        rear = (qN*)malloc(sizeof(qN));
        rear->num = 0;
        rear->data = S->p[0].data;
        first = (qN*)malloc(sizeof(qN));
        rear->next = first;
        while(i<Maxsize && first!=rear)
        {
            q.num = rear->num;
            q.data = rear->data;
            p = rear;
            rear = rear->next;
            free(p);
            printf("请输入%c结点的所有子结点:\n",q.data);
            gets(c);
            l = strlen(c);
            if(c[0]==' ')
                continue;
            for(j=0;j<l;j++)
            {
                S->p[i].data = c[j];
                S->p[i].parent = q.num;
                first->num = i;
                first->data = c[j];
                p = (qN*)malloc(sizeof(qN));
                first->next = p;
                first = p;
                i++;
            }

        }
        if(i>=Maxsize)
        {
            printf("结点数大于数组容量");
            exit(-1);
        }
        S->n = i;
    }
    else
        S->n = 0;
}

int insert_tree(tree * S,char e,int i,tree c)
{
    int j,k,m,l,f = 1;
    if(S->n)
    {
        for(j=0;i<S->n;j++)
        {
            if(S->p[j].data==e)
                break;
        }
        for(l=j+1;l<S->n;l++)
        {
            if(S->p[l].parent==j)
                break;
        }
        if(l==S->n||i==1)
        {
            l = j+1;
        }
        else
        {
            for (m = 1; m < i; m++)
                l++;
            while (S->p[l].parent != j)
                l--;
        }
        if(l<S->n)
        {
            for (k = S->n - 1; k >= l; k--)
            {
                S->p[k + c.n] = S->p[k];
                if (S->p[k].parent >= l)
                    S->p[k + c.n].parent += c.n;
            }
        }
        for(m=0;m<c.n;m++)
        {
            S->p[l+m] = c.p[m];
            S->p[l+m].parent += l;
        }
        S->p[l].parent = j;
        S->n += c.n;
        while(f)
        {
            //按层序排序
        }

    }
}

char left_child(tree * S,char e)
{
    int i,j;
    for(i=0;i<S->n;i++)
    {
        if(S->p[i].data == e)
            break;
    }
    for(j=i+1;j<S->n;j++)
        if(S->p[j].parent==i)
            return S->p[j].data;
    return 0;
}

int depth_tree(tree * S)
{
    int i,m,max=0,dep;
    for(i=0;i<S->n;i++)
    {
        dep = 1;
        m = S->p[i].parent;
        while(m!=-1)
        {
            m = S->p[m].parent;
            dep++;
        }
        if(max<dep)
            max = dep;
    }
    return max;
}

void assign_tree(tree * S,char old,char new)
{
    int i;
    for(i=0;i<S->n;i++)
    {
        if(S->p[i].data==old)
            S->p[i].data = new;
    }
}

void print(tree * S)
{
    int i;
    printf("结点     双亲");
    for(i=0;i<S->n;i++)
    {
        printf("\n%c",S->p[i].data);
        if(S->p[i].parent!=-1)
            printf("     %c",S->p[S->p[i].parent].data);
    }
    printf("\n");
}

void traverse_tree(tree * S)
{
    int i;
    int m;
    for(i=0;i<S->n;i++)
    {
        printf("%2c",S->p[i].data);
    }
    printf("\n");
}

int strlen(char * c)
{
    int i = 0;
    while(*c++!='\0')
    {
        i++;
    }
    return i;
}

void init_tree(tree * S)
{
    S->n = 0;
}
