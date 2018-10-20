//
// Created by 邓岩 on 2018/10/7.
//

# include <stdio.h>
# include <stdlib.h>
# include <memory.h>

#define ElemType int

typedef struct array
{
    ElemType * base;//数组的基地址
    int length;//标志着整个数组长度
    int cur;//标志着当前数组中的元素个数
}Array,* pArray;


int Init_array(pArray arr);//初始化数组，失败返回-1
int Resize_array(pArray arr);//重新分配两倍大小数组空间，失败返回-1
void Print_array(pArray arr);//打印数组中的元素个数
int Insert_array(pArray arr,int pos,ElemType value);//向数组中插入元素，pos为1表示插入到第一个元素，失败返回-1
int Delete_array(pArray arr,int pos,ElemType * e);//删除数组中第pos个元素，返回值通过e返回
int find_array(pArray arr,ElemType value);//查找元素所在的下标，不在就返回-1
void free_array(pArray arr);//释放空间


void msg()
{
    printf("*			1、建立线性表（初始化）			*\n");
    printf("*			2、查找元素（定位）			*\n");
    printf("*			3、插入元素				*\n");
    printf("*			4、删除元素				*\n");
    printf("*			5、显示元素				*\n");
    printf("*			6、修改元素（存储）			*\n");
    printf("*			7、判断是否为空表			*\n");
    printf("*			8、计算数据表长度			*\n");
    printf("*			9、销毁数据表				*\n");
    printf("*			0、退出程序				*\n");
    printf("-----------------------------------------------------------------\n");
    printf("提示:请首先初试化线性表!\n");
    printf("请输入你的选项:0-9:");
}

int main()
{
    Array arr;
    int choose = -1,n,e,pos;
    for(;choose!=0;)
    {

        msg();
        scanf("%d",&choose);
        switch (choose)
        {
            case 0:
                printf("程序正在关闭.....\n");
                exit (0);
            case 1:
                Init_array(&arr);
                break;

            case 2:
                printf("请输入要查找的元素:");
                scanf("%d",&e);
                if ((n = find_array(&arr,e)) != -1)
                    printf("该元素的位置是%d\n:",n);
                else
                    printf("该元素不存在!\n");
                break;

            case 3:
                printf("请输入你要插入的元素");
                scanf("%d",&e);
                printf("请输入你要插入的位置:");
                scanf("%d",&pos);
                if (Insert_array(&arr,pos,e))
                    printf("插入成功!\n");
                else
                    printf("插入失败,请检查插入的位置是否正确及空间是否已满!\n");
                break;
            case 4:
                printf("请输入你要删除的元素位置");
                scanf("%d",&pos);
                if (Delete_array(&arr,pos,&e))
                    printf("删除成功!，删除的数据为%d\n",e);
                break;
            case 5:
                Print_array(&arr);
                break;
            case 6:
                break;//未实现
            case 7:
                if(arr.cur == 0)
                    printf("为空表\n");
                else
                    printf("非空表\n");
                break;
            case 8:
                printf("当前数据表长度为%d,已使用%d\n",arr.length,arr.cur);
                break;
            case 9:
                free_array(&arr);
        }
    }
    return 0;
}


void free_array(pArray arr)
{
    free(arr->base);//释放空间
    arr->cur = 0;
    arr->length = 0;
}

int find_array(pArray arr,ElemType value)
{
    int i = arr->cur;
    int j = 0;
    for (; j != i; ++j) {
        if((arr->base)[j] == value)//如果找到值
            return j;//返回下标
    }
    return -1;
}

int Delete_array(pArray arr,int pos,ElemType * e)//删除第pos个元素
{
    if(pos > arr->cur)//pos数据不合法
        return -1;
    *e = (arr->base)[pos - 1];//将删除的值返回
    memcpy(arr->base + pos - 1,arr->base + pos,(arr->cur - pos) * sizeof(ElemType));//将被删除元素后面的数据向前移动
    --arr->cur;
}

int Insert_array(pArray arr,int pos,int value)//将value插入到第pos个元素
{
    if(pos > arr->cur)//pos数据不合法，默认插入到最后一个元素
        pos = arr->cur + 1;
    if(arr->cur == arr->length)//当前没有剩余空间
        if( Resize_array(arr) == -1)//分配失败
            return -1;//插入失败
    if( (memmove(arr->base+pos,arr->base+pos-1,(arr->cur - pos + 1) * sizeof(ElemType))) != NULL )//移动插入点之后的值
    {
        (arr->base)[pos-1] = value;//插入值
        arr->cur++;//数组成员+1
        return 0;
    }
    else
        return -1;
}

void Print_array(pArray arr)
{
    int n = arr->cur;
    int i = 0;
    for(; i != n; i++)
    {
        printf("%d ",(arr->base)[i]);
    }
    printf("\n");
}

int Resize_array(pArray arr)
{
    ElemType * temp = (ElemType *)malloc(sizeof(ElemType) * arr->length * 2);//分配两倍的大小
    if( memcpy(temp,arr->base,arr->cur * sizeof(ElemType)) == NULL)//将原数组数据移动到新数组
        return -1;
    printf("重分配成功\n");
    free(arr->base);//释放旧数组
    arr->base = temp;//改变指向的基地址
    arr->length *= 2;//数组长度 * 2
    return arr->length;
}

int Init_array(pArray arr)
{
    printf("请输入需要的元素个数:");
    scanf("%d",&arr->cur);//保存数组当前元素个数
    if( (arr->base = (ElemType *)malloc(sizeof(ElemType) * arr->cur * 2)) != NULL )//分配所需要空间大小的两倍
    {
        arr->length = arr->cur * 2;//保存数组大小
        printf("数组分配成功，请输入你想要输入的数据:");
        int i = 0;
        for(; i != arr->cur; i++)
        {
            scanf("%d",arr->base + i);
        }
        return 0;
    }
    else
        return -1;
}
