# include <stdio.h>
# include <stdlib.h>

# define size 4

typedef struct node
{
    char ch[size];
    struct node * next;
}Node,*pNode;

typedef struct Cstring
{
    pNode head;
    pNode tail;
    int length;
}Cstring,*pCstring;

void string_initial(pCstring);
int string_assign(pCstring,char *);
int string_length(char *);
int string_plength(pCstring);
void string_print(pCstring);
int string_tochar(pCstring,char **);
int string_copy(pCstring,pCstring);
int string_compare(pCstring,pCstring);
void string_clear(pCstring);
int string_concat(pCstring,pCstring,pCstring);
int string_substring(pCstring,pCstring,int,int);
int string_index(pCstring,pCstring,int pos);
int string_insert(pCstring,pCstring,int pos);
int string_delete(pCstring,int,int);
int string_replace(pCstring,pCstring,pCstring);

int main(void)
{
    char * a;
    Cstring S;
    Cstring T;
    Cstring A;
    Cstring B;
    Cstring sub;
    string_initial(&B);
    string_initial(&S);
    string_initial(&T);
    string_initial(&A);
    string_initial(&sub);
    char c[50];
    char b[1] = {'1'};
    string_assign(&B,b);
    printf("请输入c的值：\n");
    gets(c);
    string_assign(&S,c);
    printf("S print:");
    string_print(&S);
    printf("\n");
    string_tochar(&S,&a);
    string_copy(&S,&T);
    printf("T print:");
    string_print(&T);
    printf("\n");
    printf("compare S and T:");
    printf("changeu---%d,%d\n",string_plength(&S),string_plength(&T) );
    printf("%d\n",string_compare(&S,&T));
    printf("concat S and T:");
    string_concat(&A,&S,&T);
    string_print(&A);
    printf("\n");
    if( string_substring(&A,&sub,2,5) )
        printf("OK\n");
    else
        printf("error\n");
    printf("substring:");
    string_print(&sub);
    printf("\n");
    printf("index:%d",string_index(&sub,&S,3));
    printf("\n");
    printf("insert:");
    if( string_insert(&sub,&S,3) )
        string_print(&sub);
    else
        printf("error\n");
    printf("\n");
    printf("delete:");
    if( string_delete(&sub,1,4) )
        string_print(&sub);
    else
        printf("error\n");
    printf("\n");
    string_replace(&sub,&B,&T);
    printf("replace:");
    string_print(&sub);
    printf("\n");
    return 0;
}

int string_replace(pCstring S,pCstring T,pCstring V)
{
    int i;
    int k;
    int m;
    char * c;
    char * a;
    i = string_index(S,T,1);
    k = string_plength(T);
    m = string_plength(V);
    while(i)
    {
        string_delete(S,i,k);
        string_insert(S,V,i);
        i = string_index(S,T,i+m);
    }
    return 0;
}

int string_delete(pCstring S,int pos,int len)
{
    int i,k;
    char * c;
    string_tochar(S,&c);
    i = string_length(c);
    if(pos<1 || len>i-pos+1)
        return 0;
    for(k=pos-1;k<i-len;k++)
        c[k] = c[k+len];
    c = (char *)realloc(c,sizeof(char) * (i-len+1));
    free(S->head);
    c[i-len] = '\0';
    string_initial(S);
    string_assign(S,c);
    free(c);
    return 1;
}

int string_insert(pCstring S,pCstring sub,int pos)
{
    int i,j,k;
    char * c;
    char * a;
    string_tochar(S,&c);
    string_tochar(sub,&a);
    i = string_length(c);
    j = string_length(a);
    if(pos<0 || pos>i+1)
        return 0;
    c = (char *)realloc(c,sizeof(char) * (i+j));
    if(!c)
        return 0;
    for(k=i+j-1;k>=j+pos-1;k--)
    {
        c[k] = c[k-j];
    }
    for(k=pos-1;k<pos+j-1;k++)
    {
        c[k] = a[k-pos+1];
    }
    string_assign(S,c);
    return 1;
}

int string_index(pCstring S,pCstring sub,int pos)
{
    int i,j,k,m;
    m = 0;
    char * c;
    char * a;
    string_tochar(S,&c);
    i = string_length(c);
    if(pos<1||pos>i)
        return 0;
    string_tochar(sub,&a);
    j = string_length(a);
    for(k=pos-1;k<i-j+1;k++)
    {
        while(c[k] == a[m])
        {
            k++;
            m++;
            if(m == j)
                return k-m+1;
        }
        k -= m;
        m = 0;
    }
    free(c);
    free(a);
    return 0;
}

int string_substring(pCstring S,pCstring sub,int pos,int len)
{
    char * c;
    string_tochar(S,&c);
    int i;
    i = string_length(c);
    if(pos<1||pos>i||len>i-pos+1)
        return 0;
    char * a = (char *)malloc(sizeof(char) * len);
    for(i=0;i<len;i++)
    {
        *(a+i) = *(c+pos-1+i);
    }
    string_assign(sub,a);
    free(c);
    free(a);
    return 1;
}

int string_concat(pCstring A,pCstring S,pCstring T)
{
    int i;
    int j;
    int k;
    Cstring s;
    Cstring t;
    string_initial(&s);
    string_initial(&t);
    i = string_copy(S,&s);
    j = string_copy(T,&t);
    if(!i||!j)
        return 0;
    s.tail->next = t.head;
    A->head = s.head;
    A->tail = t.tail;
    A->length = S->length + T->length;
    return 1;
}

int string_compare(pCstring S,pCstring T)
{
    int i = 0;
    int j;
    char * s;
    char * t;
    int m = 0;
    string_tochar(S,&s);
    string_tochar(T,&t);
    i = string_length(s);
    j = string_length(t);
    while(s[m]&&t[m])
    {
        if(s[m]!=t[m])
            return s[m]-t[m];
        m++;
    }
    free(s);
    free(t);
    return i-j;
}

int string_copy(pCstring S,pCstring T)
{
    int i;
    char * c;
    string_tochar(S,&c);
    i = string_assign(T,c);
    free(c);
    return i;
}

int string_tochar(pCstring S,char ** c)
{
    char w;
    pNode q = S->head;
    if(string_plength(S) == 0)
        return 0;
    else
    {
        *c = (char *)malloc(sizeof(char) * (string_plength(S) + 1) );
        if(!*c)
            return 0;
        char * p;
        p = *c;
        int i;
        while(q)
        {
            for(i=0;i<size;i++)
            {
                if(q->ch[i]!='\0')
                    *p++ = q->ch[i];
            }
            q = q->next;
        }
        *p = '\0';
        return 1;
    }
}

int string_assign(pCstring S,char * c)
{
    int i,j,k;
    pNode q;
    i = string_length(c);
    if(i == 0)
        return 0;
    else
    {
        j = i/size;
        if(i%size)
            j++;
        S->length = j;
        for(i=0;i<j;i++)
        {
            q = (pNode)malloc(sizeof(Node));
            if(!q)
                return 0;
            for(k=0;k<size&&*c;k++)
            {
                q->ch[k] = *c++;
            }
            if(i==0)
                S->head = S->tail = q;
            else
            {
                S->tail->next = q;
                S->tail = q;
                q->next = NULL;
            }
            if(!*c)
            {
                q->next = NULL;
                for(;k<size;k++)
                    q->ch[k] = '\0';
            }
        }
    }
    return 1;
}

void string_clear(pCstring S)
{
    int i;
    pNode p,q;
    p = S->head;
    q = p->next;
    for(i=0;i<S->length;i++)
    {
        free(p);
        p = q;
        q = q->next;
    }
    S->head = S->tail = NULL;
    S->length = 0;
}

void string_print(pCstring S)
{
    int i,j;
    pNode p = S->head;
    for(i=0;i<S->length;i++)
    {
        for(j=0;j<size;j++)
        {
            printf("%c",p->ch[j]);
        }
        p = p->next;
    }
}

int string_plength(pCstring S)
{
    int i,j,k=0;
    pNode p = S->head;
    for(i=0;i<S->length;i++)
    {
        for(j=0;j<size&&p->ch[j] != '\0';j++)
        {
            k++;
        }
        p = p->next;
    }
    return k;
}

int string_length(char * c)
{
    int i = 0;
    while(*c && *c!='\0')
    {
        c++;
        i++;
    }
    return i;
}

void string_initial(pCstring S)
{
    S->head = S->tail = NULL;
    S->length = 0;
}