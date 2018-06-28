/*------------------------------------------
 猜测：由函数调用引起的堆栈所分配的内存空间并不是当函数执行完毕后立刻
 释放空间，而是在下一个函数调用后释放。
 原因：在subString函数中静态分配了c数组，而后将c数组的地址返回给了主
 函数中某个实参，函数调用完后，仍可以访问c数组，但当在主函数调用一个其
 他函数后，便无法继续访问。
 
 无法将静态数组头地址的地址作为参数
 如：
 char a[10];
 &a  无法作为参数
 
 注意：
 *a[?] error
 该表达式会先执行a[?]
 后读取a[?]内地址指向的值
 (*a)[?] OK
 
 当含有!逻辑运算符时，后面如果有其他运算符应该打括号
 !(*str==a[0]) ok
 !*str==a[0] error

 广义表
 -----------------------------------------*/
# include <stdio.h>
# include <stdlib.h>

# define Atom 0
# define List 1

typedef struct node
{
    int tag;
    union
    {
        struct
        {
            struct node * hp,* tp;
        }ptr;
        int atom;
    };
}Node;

void visit(char e)
{
    printf("%c ",e);
}

void printStr(char *);
int strLength(char *);
void subString(char **,char *,int,int);
void serve(char **,char **);
void destroy_glist(Node **);
void copy_glist(Node **,Node *);
void init_glist(Node **);
int length_glist(Node *);
int depth_glist(Node *);
void create_list(Node **,char *);
void printList(Node *,void(char));
void insert_first_Node(Node **,Node *);
void delete_first_Node(Node **,Node **);
Node * head_glist(Node *);
Node * tail_glist(Node *);

int main(void)
{
    Node * S;
    Node * T;
    char * car;
        //char a[10];
    char * a = (char *)malloc(sizeof(char) * 100);
    gets(a);
    printf("输出a\n");
    printStr(a);
        //char ** str = &a;
        //char * sub;
        //subString(&sub,a,2,5);
        //printStr(sub);
    printf("\n");
    serve(&a,&car);
    printf("car:");
    printStr(car);
    printf("\n");
    printf("cdr:");
    printStr(a);
    printf("\n");
    printf("将car生成为广义表：\n");
    create_list(&S,car);
    printList(S,visit);
    printf("\n");
    printf("T复制S：\n");
    copy_glist(&T,S);
    printList(T,visit);
    printf("\n");
    printf("T长度:");
    printf("%d",length_glist(T));
    printf("\n");
    printf("T深度:");
    printf("%d",depth_glist(T));
    return 0;
}

void create_list(Node ** S,char * c)
{
    char * car;
    char * str;
    Node * p,* q;
    char a[2] = "()";
    if(*c==a[0]&&*(c+1)==a[1])
        *S = NULL;
    else
    {
        *S = (Node *)malloc(sizeof(Node));
        if(strLength(c)==1)
        {
            (*S)->tag = Atom;
            (*S)->atom = *c;
        }
        else
        {
            (*S)->tag = List;
            p = *S;
            subString(&str,c,2,strLength(c)-2);
            do
            {
                serve(&str,&car);
                create_list(&(p->ptr.hp),car);
                if(!(*str==a[0])||!(*(str+1)==a[1]))
                {
                    q = p;
                    p = (Node *)malloc(sizeof(Node));
                    p->tag = List;
                    q->ptr.tp = p;
                }
            }while(!(*str==a[0])||!(*(str+1)==a[1]));
            p->ptr.tp = NULL;
        }
    }
}

void serve(char ** str,char ** car)
{
    int i;
    int k = 0;
    int n = strLength(*str);
    char * p = *str;
    char c1 = '(';
    char c2 = ')';
    char c3 = ',';
    for(i=0;(i<n&&!(*(p+i)==c3))||k!=0;i++)//必须加括号
    {
        if(*(p+i)==c1)
            k++;
        if(*(p+i)==c2)
            k--;
    }
    i++;
    if(i<n)
    {
        subString(str,p,i+1,n-i);
        subString(car,p,1,i-1);
    }
    else
    {
        *car = (char *)malloc(sizeof(char) * (n+1));
        for(i=0;i<n;i++)
        {
            (*car)[i] = (*str)[i];//注意
        }
        *str = (char *)malloc(sizeof(char) * 3);
        *str = "()";
    }
}

void copy_glist(Node ** S,Node * T)
{
    if(!T)
        *S = NULL;
    else
    {
        *S = (Node *)malloc(sizeof(Node));
        if(T->tag == List)
        {
            (*S)->tag = List;
            copy_glist(&(*S)->ptr.hp,T->ptr.hp);
            copy_glist(&(*S)->ptr.tp,T->ptr.tp);
            
        }
        else
        {
            (*S)->tag = Atom;
            (*S)->atom = T->atom;
        }
    }
}

int depth_glist(Node * S)
{
    int max;
    int dep;
    if(!S)
        return 1;
    if(S->tag == Atom)
        return 0;
    for(max=0;S;S = S->ptr.tp)
    {
        dep = depth_glist(S->ptr.hp);
        if(dep>max)
            max = dep;
    }
    return max+1;
}

void  insert_first_Node(Node ** S,Node * T)
{
    Node * p = (Node *)malloc(sizeof(Node));
    p->tag = List;
    p->ptr.hp = T;
    p->ptr.tp = *S;
    *S = p;
}

void delete_first_Node(Node ** S,Node ** T)
{
    Node * p;
    p = *S;
    *T = p->ptr.hp;
    *S = p->ptr.tp;
    free(p);
}

Node * head_glist(Node * S)
{
    if(S)
    {
        Node * p;
        copy_glist(&p,S->ptr.hp);
        return p;
    }
    return NULL;
}

Node * tail_glist(Node * S)
{
    if(S)
    {
        Node * p;
        copy_glist(&p,S->ptr.tp);
        return p;
    }
    return NULL;
}

int length_glist(Node * S)
{
    int i = 0;
    while(S)
    {
        S = S->ptr.tp;
        i++;
    }
    return i;
}

void destroy_glist(Node ** S)
{
    Node * hp;
    Node * tp;
    if(*S)
    {
        if((*S)->tag == List)
        {
            hp = (*S)->ptr.hp;
            tp = (*S)->ptr.tp;
            destroy_glist(&hp);
            destroy_glist(&tp);
        }
        free(*S);
        *S = NULL;
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
        //free(S);
}

int strLength(char * c)
{
    int i = 0;
    while(*c++)
    {
        i++;
    }
    return i;
}

void printStr(char * c)
{
    if(c!=NULL)
    {
        while(*c)
        {
            printf("%c",*c++);
        }
    }
}

void init_glist(Node ** S)
{
    *S = NULL;
}

void printList(Node * S,void v(char))
{
    if(S)
    {
        if(S->tag == Atom)
        {
            v(S->atom);
        }
        else if(S->tag == List)
        {
            printList(S->ptr.hp,v);
            printList(S->ptr.tp,v);
        }
    }
}