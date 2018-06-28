# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define maxsize 100
# define CHAR 1
    //# define CHAR 0
#if CHAR
typedef char type;
type Nil = ' ';
#else
typedef int type;
type Nil = 0;
#endif

typedef struct position
{
    int layer;
    int order;
}position;

void visit(type e)
{
    printf("%2c",e);
}


int empty_tree(type *);
int strLength(char *);
void init_tree(type *);
void create_tree(type *);
int depth_tree(type *);
type value(type *,position);
int assign(type *,position,type);
type parent(type *,type);
type left_child(type *,type);
type right_child(type *,type);
type left_bro(type *,type);
type right_bro(type *,type);
void move_tree(type *,int,type *,int);
void insert_child(type *,type,type *,int);
void delete_child(type *,position);
void layer_traverse(type *);
void pro_traverse(type *,int,void(type));
void mid_traverse(type *,int,void(type));
void end_traverse(type *,int,void(type));

int main(void)
{
    position n;
    n.layer = 2;
    n.order = 1;
    position e;
    type a[maxsize];
    type b[maxsize];
    create_tree(a);
    create_tree(b);
    printf("该树的深度为:%d\n",depth_tree(a));
    printf("请输入想得到节点的坐标:\n");
    scanf("%d,%d",&e.layer,&e.order);
    printf("值为:%c\n",value(a,e));
        //insert_child(a,'4',b,0);
    layer_traverse(a);
    pro_traverse(a,0,visit);
    printf("\n");
    mid_traverse(a,0,visit);
    printf("\n");
    end_traverse(a,0,visit);
    printf("\n");
    return 0;
}

void create_tree(type * S)
{
    int i = 0;
    init_tree(S);
#if CHAR
    char n;
    char s[maxsize];
    printf("请按层序输入二叉树的值，空值输入空格:\n");
    gets(s);
    n = strLength(s);
    for(;i<n;i++)
    {
        S[i] = s[i];
    }
#else
    printf("请按层序输入二叉树的值，0表示空值，999表示结束:\n");
    while(1)
    {
        scanf("%d",&S[i]);
        if(S[i] == 999)
        {
            S[i] = Nil;
            break;
        }
        i++;
    }
#endif
    for(i=1;i<maxsize;i++)
    {
        if(S[(i-1)/2]==Nil&&S[i]!=Nil)
            printf("出现无双亲的非空节点：S[%d]\n",i);
    }
}

void insert_child(type * S,type e,type * T,int LR)
{
    int i,k;
    for(i=0;i<pow(2,depth_tree(S))-1;i++)
        if(S[i]==e)
            break;
    k = 2 * i + 1 + LR;
    move_tree(S,k,S,2*k+2);
    move_tree(T,i,S,k);
}

void delete_child(type * S,position e)
{
    position k;
    int n = pow(2,e.layer-1) + e.order - 2;
    if(S[2*n+1]!=Nil)
    {
        k.layer = e.layer + 1;
        k.order = 2 * e.order - 1;
        delete_child(S,k);
    }
    if(S[2*n+2]!=Nil)
    {
        k.layer = e.layer + 1;
        k.order = 2 * e.order;
        delete_child(S,k);
    }
    S[n] = Nil;
}

void move_tree(type * S,int i,type * T,int j)
{
    if(S[2*i+1]!=Nil)
    {
        move_tree(S,2*i+1,T,2*j+1);
    }
    if(S[2*i+2]!=Nil)
        move_tree(S,2*i+2,T,2*j+2);
    T[j] = S[i];
    S[i] = Nil;
}

void layer_traverse(type * S)
{
    int i,j;
    int l = depth_tree(S);
    for(i=1;i<=l;i++)
    {
        for(j=pow(2,i-1)-1;j<pow(2,i)-1;j++)
        {
            if(S[j]==Nil)
                printf("  ");
            else
                printf("%2c",S[j]);
        }
        printf("\n");
    }
}

void pro_traverse(type * S,int n,void v(type))
{
    if(S[n]!=Nil)
    {
        v(S[n]);
        if(S[2*n+1]!=Nil)
            pro_traverse(S,2*n+1,v);
        if(S[2*n+2]!=Nil)
            pro_traverse(S,2*n+2,v);
    }
}

void mid_traverse(type * S,int n,void v(type))
{
    if(S[n]!=Nil)
    {
        if(S[2*n+1]!=Nil)
            mid_traverse(S,2*n+1,v);
        v(S[n]);
        if(S[2*n+2]!=Nil)
            mid_traverse(S,2*n+2,v);
    }
}

void end_traverse(type * S,int n,void v(type))
{
    if(S[n]!=Nil)
    {
        if(S[2*n+1]!=Nil)
            end_traverse(S,2*n+1,v);
        if(S[2*n+2]!=Nil)
            end_traverse(S,2*n+2,v);
        v(S[n]);
    }
}

type left_bro(type * S,type e)
{
    int i;
    if(S[0]==Nil)
        return Nil;
    for(i=1;i<maxsize;i++)
        if((S[i]==e)&&(i%2==0))
            return S[i-1];
    return Nil;
}

type right_bro(type * S,type e)
{
    int i;
    if(S[0]==Nil)
        return Nil;
    for(i=1;i<maxsize;i++)
        if((S[i]==e)&&(i%2==1))
            return S[i+1];
    return Nil;
}

type parent(type * S,type e)
{
    int i;
    if(S[0]==Nil)
        return Nil;
    for(i=1;i<maxsize;i++)
        if(S[i]==e)
            return S[(i-1)/2];
    return Nil;
}

type left_child(type * S,type e)
{
    int i;
    if(S[0]==Nil)
        return Nil;
    for(i=0;i<maxsize;i++)
        if(S[i]==e)
            return S[2*i+1];
    return Nil;
}

type right_child(type * S,type e)
{
    int i;
    if(S[0]==Nil)
        return Nil;
    for(i=0;i<maxsize;i++)
        if(S[i]==e)
            return S[2*i+2];
    return Nil;
}

int assign(type * S,position e,type v)
{
    int i = pow(2,e.layer-1) + e.order -2;
    if(v!=Nil&&S[(i-1)/2]==Nil)
        return 0;
    if(v==Nil&&(S[2*i+1]==Nil||S[2*i+2]==Nil))
        return 0;
    S[i] = v;
    return 1;
}

type value(type * S,position e)
{
    int k = pow(2,e.layer-1) + e.order - 2;
    return S[k];
}

void init_tree(type * S)
{
    int i;
    for(i=0;i<maxsize;i++)
    {
        S[i] = Nil;
    }
}

int depth_tree(type * S)
{
    int i = 99,j = 0,n = 1;
    while(S[i]==Nil)
    {
        i--;
    }
    i++;
    while(i>=n)
    {
        j++;
        n = n * 2;
    }
    return j;
}

int empty_tree(type * S)
{
    if(S[0] == Nil)
        return 1;
    else
        return 0;
}

int strLength(char * S)
{
    int i = 0;
    while(*S++)
    {
        i++;
    }
    return i;
}