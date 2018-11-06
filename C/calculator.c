# include <stdio.h>
# include <stdlib.h>

# define size 100
# define extend 10

typedef struct steak
{
    int * pTop;
    int * pBottom;
    int steaksize;
}Steak,*pSteak;

void init_steak(pSteak);
char precede(int,int);
void push_steak(pSteak,int);
void pop_steak(pSteak,int *);
int get_steak(pSteak);
int calculate(int,int,int);
int In(int);
int empty_steak(pSteak);
int calculate_formula(void);

int main(void)
{
    printf("请输入表达式，如果输入负数，请使用(0-x)!:\n");
    printf("%d\n",calculate_formula());
}

int calculate_formula()
{
    char c;
    char z[11];
    int i;
    int a,b,d,x;
    Steak S;
    Steak T;
    init_steak(&S);
    init_steak(&T);
    push_steak(&T,'\n');
    c = getchar();
    x = get_steak(&T);
    while( c!='\n' || x!='\n')
    {
            if( In(c) )
            {
                switch(precede(x,c))
                {
                    case '<':
                        push_steak(&T,c);
                        c = getchar();
                        break;
                    case '=':
                        pop_steak(&T,&x);
                        c = getchar();
                        break;
                    case '>':
                        pop_steak(&S,&a);
                        pop_steak(&S,&b);
                        pop_steak(&T,&x);
                        push_steak(&S,calculate(a,b,x));
                }
            }
            else if(c>='0' && c<='9')
            {
                i = 0;
                while(c>='0' && c<='9')
                {
                    z[i++] = c;
                    c = getchar();
                }
                z[i]=0;
                d = atoi(z);
                push_steak(&S,d);
            }
            else
            {
                printf("表达式含有非法字符！\n");
                exit(-1);
            }
            x = get_steak(&T);
    }
        pop_steak(&S,&x);
        if( !empty_steak(&S) )
        {
            printf("表达式错误！95\n");
            exit(-1);
        }
        return x;
}

char precede(int t1,int t2)
{
    char f;
    switch(t2)
    {
            case '+':
            case '-':
        {
            if(t1=='(' || t1=='\n')
                f = '<';
            else
                f = '>';
                break;
        }
            case '*':
            case '/':
        {
            if(t1=='*' || t1=='/' || t1==')')
                f = '>';
            else
                f = '<';
                break;
        }
            case '(':
            if(t1 == ')')
            {
                printf("括号不匹配！\n");
                exit(-1);
            }
            else
                f = '<';
                break;
            case ')':switch(t1)
        {
                case '(':
                f = '=';
                break;
                case '\n':
            {
                printf("缺少左括号！\n");
                exit(-1);
            }
                default:f = '>';
        }
            break;
            case '\n':switch(t1)
        {
                case '\n':
                f = '=';
                break;
                case '(':
            {
                printf("缺少右括号！\n");
                exit(-1);
            }
            default:f = '>';
        }
    }
    return f;
}

int In(int c)
{
    switch(c)
    {
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
            case ')':
            case '\n':return 1;
    }
    return 0;
}

int calculate(int a,int b,int x)
{
    switch(x)
    {
        case '+':return a+b;
        case '-':return b-a;
        case '*':return a*b;
    }
    return a/b;
}

int get_steak(pSteak S)
{
    return *(S->pTop-1);
}

void pop_steak(pSteak S,int * x)
{
    if(S->pTop == S->pBottom)
    {
        printf("表达式错误！\n");
        exit(-1);
    }
    *x = *--S->pTop;
}

void push_steak(pSteak S,int x)
{
    if(S->pTop-S->pBottom == S->steaksize)
    {
        S->pBottom = (int *)realloc(S->pBottom,sizeof(int) * extend+S->steaksize);
        S->pTop = S->pBottom+S->steaksize;
        S->steaksize += extend;
    }
    *S->pTop++ = x;
}

int empty_steak(pSteak S)
{
    if(S->pTop == S->pBottom)
        return 1;
    else
        return 0;
}

void init_steak(pSteak S)
{
    S->pBottom = (int *)malloc(sizeof(int) * size);
    if(S->pBottom == NULL)
    {
        printf("分配失败！\n");
        exit(-1);
    }
    S->pTop = S->pBottom;
}