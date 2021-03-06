/*
 -----------------------------------------
 采用定长结构，带KMP算法
 -----------------------------------------
 */

# include <stdio.h>
# include <stdlib.h>

# define MAXSIZE 20

typedef char SString[MAXSIZE+1];

int string_assign(char *,char *);
int string_length(char *);//对于该存储结构有缺陷
void string_print(char *);
void string_copy(char *,char *);
int string_empty(char *);
int string_cmp(char *,char *);
int string_size(char *);
void string_clear(char *);
int string_connect(char *,char *,char *);
int string_sub(char *,char *,int,int);
int string_index(char *,char *,int);
int string_insert(char *,char *,int);
int string_delete(char *,int,int);
int string_replace(char *,char *,char *);
void get_next(char *,int **);
int KMP_index(char *,char *,int,int *);

int main(void)
{
    int * next;
    int k;
    char c[100];
    SString sub,t,S1,S2;
    gets(c);
    k = string_assign(S1,c);
    printf("打印S1：\n");
    string_print(S1);
    get_next(S1,&next);
    printf("打印next数组：\n");
    for(k = 1;k<=next[0];k++)
        printf("%d",next[k]);
    printf("\n");
    string_copy(S2,S1);
    printf("打印S1copy-S2：\n");
    string_print(S2);
    k = string_connect(t,S1,S2);
    printf("打印S1+S2=t：\n");
    string_print(t);
    printf("打印sub：\n");
    string_sub(sub,t,2,2);
    string_print(sub);
    k = string_index(t,S1,3);
        //k = KMP_index(t,S1,2,next);//KMP法索引
    if(k)
        printf("该子串的位子为：%d\n",k);
    else
        printf("不存在!\n");
    if( string_insert(t,S1,9) )
        printf("全插入成功！\n");
    else
        printf("部分插入成功！\n");
    printf("打印t after inserting：\n");
    string_print(t);
    if ( string_delete(t,1,8) )
        printf("删除成功！\n");
    else
        printf("失败！\n");
    printf("打印t after deleting：\n");
    string_print(t);
    
    return 0;
}

int KMP_index(char * S,char * T,int pos,int * next)
{
    int i = pos;
    int j = 1;
    while(i<=S[0] && j<=T[0])
    {
        if(j==0 || S[i] == T[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if(j>T[0])
        return i-T[0];
    else
        return 0;
}

void get_next(char * S,int ** next)
{
    *next = (int *)malloc(sizeof(int) * (S[0]+1));
    *next[0] = S[0];
    int i = 1;
    int j = 0;
    (*next)[1] = 0;
    while(i<S[0])
    {
        if(j == 0 || S[i] == S[j])
        {
            i++;
            j++;
            if(S[i] != S[j])
                (*next)[i] = j;
            else
                (*next)[i] = (*next)[j];
        }
        else
            j = (*next)[j];
    }
        //printf("%d",next[0]);*/
}

int string_replace(char * S,char * t,char * v)
{
    int i = 1;
    int k;
    if( string_empty(t) )
        return 0;
    do
    {
        i = string_index(S,t,i);
        string_delete(S,i,t[0]);
        k = string_insert(S,v,i);
        if(!k)
            return 0;
        i += v[0];
    }while(i);
    return 1;
}

int string_delete(char * S,int pos,int len)
{
    if(pos<1 || len<0 || pos>S[0]-len+1)
        return 0;
    else
    {
        int i;
        for(i=pos;i<=S[0]-len;i++)
        {
            S[i] = S[i+len];
        }
        S[0] -= len;
        return 1;
    }
}

int string_insert(char * S,char * t,int pos)
{
    if(pos<1 || pos>S[0]+1)
        return 0;
    if(S[0]+t[0]<=MAXSIZE)
    {
        int i;
        for(i=S[0]+t[0];i>=t[0]+pos;i--)
        {
            S[i] = S[i-t[0]];
        }
        for(i=pos;i<pos+t[0];i++)
        {
            S[i] = t[i-pos+1];
        }
        S[0] += t[0];
        return 1;
    }
    else
    {
        int i;
        for(i=MAXSIZE;i>MAXSIZE-(S[0]-pos+1);i--)
        {
            S[i] = S[S[0]+i-MAXSIZE];
        }
        for(i=pos;i<=MAXSIZE-(S[0]-pos+1);i++)
        {
            S[i] = t[i-pos+1];
        }
        S[0] = MAXSIZE;
        return 0;
    }
    
}

int string_index(char * S,char * t,int pos)
{
    int i,j;
    if(i>=1 && i<=S[0])
    {
        i = pos;
        j = 1;
        while(i<=S[0] && j<=t[0])
        {
            if(S[i] == t[j])
            {
                i++;
                j++;
            }
            else
            {
                i = i-j+2;
                j = 1;
            }
        }
        if(j>t[0])
            return i-j+1;
        else
            return 0;
    }
    
    return 0;
}

int string_sub(char * sub,char * S,int pos,int len)
{
    int i;
    if(pos<0 || len>S[0]-pos+1)
        return 0;
    else
    {
        for(i=1;i<=len;i++)
        {
            sub[i] = S[pos+i-1];
        }
        sub[0] = len;
    }
    return 1;
}

int string_connect(char * T,char * L,char * R)
{
    int i;
    if(MAXSIZE < L[0]+R[0])
        return 0;
    else
    {
        T[0] = L[0]+R[0];
        for(i=1;i<=L[0];i++)
        {
            T[i] = L[i];
        }
        for(i=L[0]+1;i<=MAXSIZE;i++)
        {
            T[i] = R[i-L[0]];
        }
    }
    return 1;
}

int string_cmp(char * L,char * R)
{
    int i;
    for(i=1;i<=L[i] && i<=R[i];i++)
    {
        if(L[i] != R[i])
            return L[i]-R[i];
    }
    return L[0]-R[0];
}

int string_size(char * S)
{
    return S[0];
}

void string_clear(char * S)
{
    S[0] = 0;
}

int string_empty(char * S)
{
    if(S[0] == 0)
        return 1;
    else
        return 0;
}

void string_copy(char * T,char * S)
{
    int i = 0;
    while(S[i] != NULL)
    {
        T[i] = S[i];
        i++;
    }
}

int string_length(char * S)
{
    int i = 0;
    while(S[i] != NULL)
    {
        i++;
    }
    return i;
}

void string_print(char * S)
{
    printf("printf:");
    int i;
    for(i=1;i<=S[0];i++)
    {
        printf("%c",S[i]);
    }
    printf("\n");
}

int string_assign(char * S1,char * c)
{
    if(string_length(c) > MAXSIZE)
        return 0;
    else
    {
        int i;
        S1[0] = string_length(c);
        for(i=1;i<=S1[0];i++)
        {
            S1[i] = *(c+i-1);
        }
    }
    return 1;
}
















