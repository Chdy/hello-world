# include <stdio.h>
# include <stdlib.h>
struct arr
{
    int * pBase;
    int cnt;
    int len;
};

void init_arr(struct arr *);//数据初始化
int append_arr(struct arr *);//追加数据
int is_full(struct arr *);//判断数据是否满
void show_arr(struct arr *);//显示数组中的数据
int insert_arr(struct arr *,int ,int );//选择地点进行数据插入
int dele_arr(struct arr*,int);//选择地点删除数据

int main(void)
{
    struct arr pArr;
    init_arr(&pArr);
    append_arr(&pArr);
    append_arr(&pArr);
    append_arr(&pArr);
    show_arr(&pArr);
    insert_arr(&pArr,2,200);//将第二个地方的数据改为200
    show_arr(&pArr);
    if ( dele_arr(&pArr,3) )//删除第三个数据
        printf("删除成功！\n");
    show_arr(&pArr);
    return 0;
}

int dele_arr(struct arr *pArr,int pos)
{
    int i,j;
    j = pArr->pBase[pos-1];
    for(i=pos; i>pArr->cnt-1; i++)
        pArr->pBase[i-1] = pArr->pBase[i];
    printf("删除的值为%d\n",j);
    return 0;
}

int insert_arr(struct arr *pArr,int pos,int val)
{
    int i;
    if( is_full(pArr) )
    {
        printf("插入失败！该数组已满\n");
        return 0;
    }
    else
    {
        for(i=pArr->cnt-1; i>=pos-1; i--)
            pArr->pBase[i+1] = pArr->pBase[i];
        pArr->pBase[pos-1] = val;
        pArr->cnt++;
    }
    return 0;
}

void init_arr(struct arr * pArr)
{
    pArr->pBase = (int *)malloc(sizeof(int) * 6);
    if(pArr->pBase == NULL)
    printf("动态内存分配失败！\n");
    else
    {
        pArr->cnt = 0;
        pArr->len = 6;

    }
}

void show_arr(struct arr * pArr)
{
    int i;
    for(i=0; i<pArr->cnt; i++)
        printf("第%d个有效数值为%d\n",i+1,pArr->pBase[i]);
}

int append_arr(struct arr * pArr)
{
    int j;
    if( is_full(pArr) )
    return 0;
    else
    {
        printf("请输入第%d个数值的数据: \n",pArr->cnt+1);
        scanf("%d",&j);
        pArr->pBase[pArr->cnt] = j;
        pArr->cnt++;
    }
    return 0;
}

int is_full(struct arr * pArr)
{
    if(pArr->cnt == pArr->len)
    return 1;
    else
    return 0;
}
