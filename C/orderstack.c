/*
 --------------------------------------------------
 编写内容：括号匹配
 功能：
 创建
 入栈
 出栈
 括号匹配
 时间：2016.04.08
 --------------------------------------------------
 */
# include <stdio.h>
# include <stdlib.h>

# define size 100
# define extend 10

typedef struct stack
{
    char * pTop;
    char * pBottom;
    int stacksize;
}Stack,*pStack;

void init_stack(pStack);
void push_stack(pStack,char);
int pop_stack(pStack,char *);
int empty_stack(pStack);

int main(void)
{
    char ch[80];
    char val;
    char * p;
    Stack S;
    init_stack(&S);
    printf("请输入带有((),[],{})的表达式：\n");
    gets(ch);
    p = ch;
    while(*p)
    {
        switch(*p)
        {
            case '(':
            case '[':
            case '{': push_stack(&S,*p++);
                break;
            case ')':
            case ']':
            case '}':
            if( !empty_stack(&S) )
            {
                pop_stack(&S,&val);
                if( !((val=='('&&*p==')') || (val=='['&&*p==']') || (val=='{'&&*p=='}')) )
                {
                    printf("左右括号不匹配!\n");
                    exit(-1);
                   }
            }
            else
                {
                    printf("缺少左括号!\n");
                    exit(-1);
                }
            default:p++;
        }
    }
    if( empty_stack(&S) )
        printf("括号匹配！\n");
    else
        printf("缺少右括号！\n");
    return 0;
}

int empty_stack(pStack S)
{
    if(S->pTop == S->pBottom)
        return 1;
    else
        return 0;
}

int pop_stack(pStack S,char *val)
{
    /*if( empty_stack(S) )
    {
        printf("栈为空！\n");
        exit(-1);
    }*/
    *val = *--(S->pTop);
    return 0;
}

void push_stack(pStack S,char val)
{
    if(S->pTop-S->pBottom == S->stacksize)
    {
        S->pBottom = (char *)realloc(S->pBottom,(S->stacksize + extend)*sizeof(char));
        S->stacksize += extend;
    }
    *(S->pTop)++ = val;
}

void init_stack(pStack S)
{
    S->pBottom = (char *)malloc(sizeof(char)*size);
    S->pTop = S->pBottom;
    S->stacksize = size;
}