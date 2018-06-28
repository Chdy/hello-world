//广义表
# include <stdio.h>
# include <stdlib.h>

# define Atom 0
# define List 1

typedef struct node
{
    int tag;
    union
    {
        char atom;
        struct node * hp;
    };
    struct node * tp;
}Node;

void visit(char e)
{
    printf("%c ",e);
}

void subString(char **,char *,int,int);
int strLength(char *);
void printStr(char *);
void sever(char **,char **);
void create_glist(Node **,char *);
void printList(Node *,void(char));
int length_glist(Node *);
int depth_glist(Node *);
void destroy_glist(Node **);
void copy_glist(Node **,Node *);
void insert_glist(Node **,Node *);
void delete_glist(Node **,Node **);
Node * get_car(Node *);
Node * get_cdr(Node *);

int main(void)
{
    Node * q;
    Node * S;
    Node * T;
    char * car;
    char * a = (char *)malloc(sizeof(char) * 100);
    printf("请输入a的值：\n");
    gets(a);
    printStr(a);
    sever(&a,&car);
    printf("car:");
    printStr(car);
    printf("cdr:");
    printStr(a);
    create_glist(&S,car);
    printf("输出由car所生成的S:\n");
    printList(S,visit);
    printf("\n");
    copy_glist(&T,S);
    printf("输出由S所复制的T:\n");
    printList(T,visit);
    printf("\n");
    printf("T的长度为:%d",length_glist(T));
    printf("\n");
    printf("T的深度为:%d",depth_glist(T));
    printf("\n");
    printf("T的car为:\n");
    q = get_car(T);
    printList(get_car(T),visit);
    return 0;
}

void create_glist(Node ** S,char * str)
{
    Node * p;
    char * car;
    char a[2] = "()";
    *S = (Node *)malloc(sizeof(Node));
    if(*str==a[0]&&*(str+1)==a[1])
    {
        (*S)->tag = List;
        (*S)->hp = (*S)->tp = NULL;
    }
    if(strLength(str) == 1)
    {
        (*S)->tag = Atom;
        (*S)->atom = *str;
        (*S)->tp = NULL;
    }
    else
    {
        subString(&str,str,2,strLength(str)-2);
        sever(&str,&car);
        (*S)->tag = List;
        (*S)->tp = NULL;
        create_glist(&(*S)->hp,car);
        p = (*S)->hp;
        while((*str)!=a[0]||(*(str+1))!=a[1])//一定要括号
        {
            sever(&str,&car);
            create_glist(&p->tp,car);
            p = p->tp;
        }
    }
}

void sever(char ** str,char ** car)
{
    int i,n,k;
    char * p;
    char c1 = '(';
    char c2 = ')';
    char c3 = ',';
    p = *str;
    n = strLength(*str);
    for(i=0,k=0;(i<n&&*(p+i)!=c3)||k!=0;i++)
    {
        if(*(p+i)==c1)
            k++;
        if(*(p+i)==c2)
            k--;
    }
    i++;
    if(i<n)
    {
        subString(car,*str,1,i-1);
        subString(str,*str,i+1,n-i);
    }
    else
    {
        *car = (char *)malloc(sizeof(char) * n+1);
        for(i=0;i<n;i++)
        {
            (*car)[i] = (*str)[i];
        }
        *str = (char *)malloc(sizeof(char) * 3);
        *str = "()";
    }
}

Node * get_car(Node * S)
{
    Node * p;
    Node * q;
    if(!S||((S->tag==List)&&(S->hp==NULL)))
        return NULL;
    p = S->hp->tp;
    S->hp->tp = NULL;
    copy_glist(&q,S->hp);
    S->hp->tp = p;
    return q;
}

Node * get_cdr(Node * S)
{
    Node * p;
    Node * q;
    if(!S||((S->tag==List)&&(S->hp==NULL)))
        return NULL;
    p = S->hp;
    S->hp = p->tp;
    copy_glist(&q,S);
    S->hp = p;
    return q;
}

int length_glist(Node * S)
{
    int i = 0;
    Node * p;
    if(!S)
        return 0;
    else
    {
        if(S->tag)
        {
            p = S->hp;
            while(p)
            {
                i++;
                p = p->tp;
            }
        }
        else
        {
            p = S;
            while(p)
            {
                i++;
                p = p->tp;
            }
        }
    }
    return i;
}

int depth_glist(Node * S)
{
    int max = 0;
    int dep;
    Node * p;
    if(!S||(S->tag==List&&(!S->hp)))
        return 1;
    else if(S->tag==Atom)
        return 0;
    else
    {
        for(p=S->hp;p;p=p->tp)
        {
            dep = depth_glist(p);
            if(dep>max)
                max = dep;
        }
        return max+1;
    }
}

void copy_glist(Node ** T,Node * S)
{
    if(!S)
        *T = NULL;
    else
    {
        *T = (Node *)malloc(sizeof(Node));
        (*T)->tag = S->tag;
        if(S->tag==Atom)
        {
            (*T)->atom = S->atom;
            copy_glist(&(*T)->tp,S->tp);
        }
        else
        {
            copy_glist(&(*T)->hp,S->hp);
            copy_glist(&(*T)->tp,S->tp);
        }
    }
}

void insert_glist(Node ** S,Node * p)
{
    if(*S)
    {
        p->tp = (*S)->hp;
        (*S)->hp = p;
    }
}

void delete_glist(Node ** S,Node **p)
{
    if(*S&&(*S)->hp)
    {
     
        *p = (*S)->hp;
        (*S)->hp = (*p)->tp;
        (*p)->tp = NULL;
    }
    else
        *p = NULL;
}

void destroy_glist(Node ** S)
{
    Node * ph,* pt;
    if(*S)
    {
        if((*S)->tag==List)
            ph = (*S)->hp;
        else
            ph = NULL;
        pt = (*S)->tp;
        destroy_glist(&ph);
        destroy_glist(&pt);
        free(*S);
        *S = NULL;
    }
}

void printList(Node * S,void v(char))
{
    if(S)
    {
        if(S->tag==Atom)
        {
            v(S->atom);
            printList(S->tp,v);
        }
        else
        {
            printList(S->hp,v);
            printList(S->tp,v);
        }
    }
}

void subString(char ** sub,char * S,int pos,int length)
{
    int i;
    int n = strLength(S);
    if(pos<1 || length>n-pos+1)
        exit(-1);
        //char c[length+1]; 错误，栈分配已被释放，问题？该程序执行完后c的空间并没有释放
    char * c = (char *)malloc(sizeof(char)*(length+1));
    char * q = c;
    for(i=0;i<length;i++)
    {
        *(q+i) = *(S+pos+i-1);
    }
    *sub = c;
}

void printStr(char * S)
{
    if(S)
    {
        while(*S)
        {
            printf("%c",*S++);
        }
        printf("\n");
    }
}

int strLength(char * S)
{
    int i = 0;
    if(S)
        while(*S++)
        {
            i++;
        }
    return i;
}