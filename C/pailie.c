# include <stdio.h>
# include <stdlib.h>

//void output();

int main(void)
{
    printf("请输入r-非重复排列的元素个数\nlen:");
    int len;
    int a,j;//更换值容器
    int i,b,k;//循环变量
    int t;//替换值容器
    scanf("%d",&len);
    int * p = (int *)malloc(sizeof(int) * len);
    for(k=0; k<len; k++)//初始化数值
        p[k] = k+1;
    
    for(i=0; i<len; i++)
    {
        if(p[len-i]>p[len-i-1])
        {
            if(i == 0)
            {
                j = p[len-1];
                p[len-1] = p[len-2];
                p[len-2] = j;
            }
            else
            {
                for(b=0; b<i-1 ;b++)
                {
                    t = p[len-1-i];
                    if(p[len-i+b]>p[len-i+1+b])
                    {
                        p[len-1-i] = p[len-i+b+1];
                        p[len-i+b+1] = t;
                    }
                    else
                    {
                        p[len-1-i] = p[len-i+b];
                        p[len-1-b] = t;
                    }
                }
            }
        }
    }
    for(i=0; i<len; i++)
    printf("第%d个元素为%d\n",i+1,p[i]);
    
    return 0;
}

/*void ouuput()
{
    
}*/

