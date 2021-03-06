# include <stdio.h>
# include <stdlib.h>

typedef struct string
{
    char * ch;
    int length;
}String;

void string_inital(String *);
int string_length(char *);
void string_assign(String *,char *);
void string_print(String *);
void string_copy(String *,String *);
int string_empty(String *);
int string_cmp(String *,String *);
void string_clear(String *);
void string_connect(String *,String *,String *);
void string_sub(String *,String *,int,int);
int string_index(String *,String *,int);
int string_insert(String *,String *,int);
int string_delete(String *,int,int);
int string_replace(String *,String *,String *);

int main(void)
{
    String s1,s2,t,sub;
    string_inital(&sub);
    string_inital(&s1);
    string_inital(&s2);
    string_inital(&t);
    char c[100];
    gets(c);
    string_assign(&s1,c);
    printf("S1 print:");
    string_print(&s1);
    printf("S2 print:");
    string_copy(&s2,&s1);
    string_print(&s2);
    printf("t print:");
    string_connect(&t,&s1,&s2);
    string_print(&t);
    printf("sub print:");
    string_sub(&sub,&t,2,3);
    string_print(&sub);
    printf("index print:");
    printf("%d\n",string_index(&sub,&t,2));
    printf("insert print:");
    string_insert(&t,&sub,1);
    string_print(&t);
    printf("delete print:");
    string_delete(&t,2,3);
    string_print(&t);
    printf("replace print:");
    string_replace(&t,&s1,&sub);
    string_print(&t);
    return 0;
}

int string_replace(String * S,String * t,String * r)
{
    int i = 1;
    do
    {
        i = string_index(t,S,i);
        if( string_empty(t) )
            return 0;
        if(i)
        {
            string_delete(S,i,t->length);
            string_insert(S,r,i);
            i += r->length;
        }
    }while(i);
    return 1;
}
    
int string_delete(String * t,int pos,int len)
{
    int i;
    if(pos<1 || len<0 || len>t->length-pos+1)
        return 0;
    for(i=pos-1;i<=t->length-len;i++)
    {
        t->ch[i] = t->ch[i+len];
    }
    t->ch = (char *)realloc(t->ch,sizeof(char) * (t->length-len));
    t->length -= len;
    return 1;
}

int string_insert(String * t,String * sub,int pos)
{
    if(pos<1 || pos>t->length+1)
        return 0;
    if(sub->length)
    {
        int i;
        t->ch = (char *)realloc(t->ch,sizeof(char) * (sub->length+t->length));
        if(!t->ch)
            exit(-1);
        for(i=t->length+sub->length-1;i>=pos+sub->length-1;i--)
        {
            t->ch[i] = t->ch[i-sub->length];
        }
        for(i=pos-1;i<pos+sub->length-1;i++)
        {
            t->ch[i] = sub->ch[i-pos+1];
        }
        t->length += sub->length;
    }
    return 1;
}

int string_index(String * sub,String * t,int pos)
{
    if(pos<1 || pos>t->length || sub->length>t->length-pos+1)
        return 0;
    String SUB;
    string_inital(&SUB);
    int n,m,i;
    i = pos;
    n = sub->length;
    m = t->length;
    while(i<=m-n+1)
    {
        string_sub(&SUB,t,i,n);
        if(string_cmp(&SUB,sub) != 0)
        {
            i++;
        }
        else
            return i;
    }
    return 0;
}


void string_sub(String * sub,String * t,int pos,int len)
{
    if(pos<1 || pos>t->length || len<0 || len>t->length-pos+1)
        return;
    if(sub->ch)
        free(sub->ch);
    if(!len)
    {
        sub->ch = NULL;
        sub->length = 0;
    }
    else
    {
        sub->ch = (char *)malloc(sizeof(char) * len);
        if(sub->ch == NULL)
            return;
        int i;
        for(i=0;i<len;i++)
        {
            sub->ch[i] = t->ch[pos+i-1];
        }
        sub->length = len;
    }
    return;
}

void string_connect(String * t,String * S,String * V)
{
    int i;
    if(t->ch)
        free(t->ch);
    t->length = S->length + V->length;
    t->ch = (char *)malloc(sizeof(char) * t->length);
    if(t->ch == NULL)
        exit(-1);
    for(i=0;i<S->length;i++)
    {
        t->ch[i] = S->ch[i];
    }
    for(i=S->length;i<t->length;i++)
    {
        t->ch[i] = V->ch[i-S->length];
    }
}

int string_cmp(String * S,String * T)
{
    int i = 0;
    while(i<S->length && i<T->length)
    {
        if(S->ch != T->ch)
            return S->ch[i]-T->ch[i];
        i++;
    }
    return S->length-T->length;
}

void string_copy(String * T,String * S)
{
    int i;
    if(T->ch != NULL)
        free(T->ch);
    T->ch = (char *)malloc(sizeof(char) * S->length);
    if(T->ch == NULL)
        exit(-1);
    for(i=0;i<S->length;i++)
    {
        T->ch[i] = S->ch[i];
    }
    T->length = S->length;
    return;
}

void string_assign(String * S,char * c)
{
    int i;
    if(S->ch != NULL)
        free(S->ch);
    i = string_length(c);
    if(!i)
    {
        S->ch = NULL;
        S->length = 0;
    }
    else
    {
        S->ch = (char *)malloc(sizeof(char) * i);
        if( S->ch == NULL)
            exit(-1);
        i--;
        S->length = i+1;
        for(;i>=0;i--)
        {
            *(S->ch+i) = *(c+i);
        }
    }
}

int string_empty(String * S)
{
    if(S->length == 0 && S->ch == NULL)
        return 1;
    else
        return 0;
}

void string_inital(String * S)
{
    S->ch = NULL;
    S->length = 0;
}

void string_print(String * S)
{
    int i;
    for(i=0;i<S->length;i++)
    {
        printf("%c",S->ch[i]);
    }
    printf("\n");
}

void string_clear(String * S)
{
    free(S->ch);
    S->ch = NULL;
    S->length = 0;
}

int string_length(char * c)
{
    int i = 0;
    while(c[i] != NULL)
    {
        i++;
    }
    return i;
}