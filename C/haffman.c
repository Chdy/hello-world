//
// Created by 邓岩 on 12/11/2017.
//
/*-----------------------------
 创建带权haffman树
 并生成haffman编码
 ------------------------------*/

# include <stdlib.h>
# include <stdio.h>
# include <memory.h>

struct haffnode
{
    int weight;
    int lchild;
    int rchild;
    int parent;
};

typedef char ** haffcode;

void select(struct haffnode * tree,int i,int * min1,int * min2);
void haffmancode(struct haffnode ** tree,haffcode * code,int * w,int n);

int main(void)
{
    int n;
    int * w;
    haffcode code;
    struct haffnode * tree;
    printf("请输入权值的个数：");
    scanf("%d",&n);
    w = (int *)malloc(sizeof(int)*n);
    printf("请陆续输入各个权值：\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d",w+i);
    }
    haffmancode(&tree,&code,w,n);
    printf("\nHaffmancode:\n");
    for (int j = 1; j <= n; ++j) {
        printf("%d\t%s\n",tree[j].weight,code[j]);
    }
}
void haffmancode(struct haffnode ** tree,haffcode * code,int * w,int n)
{
    int min1,min2;
    int m = 2*n-1;
    *tree = (struct haffnode *)malloc(sizeof(struct haffnode)*(m+1));
    for (int i = 1; i <= n; ++i,++w) {
        (*tree)[i].weight = *w;
        (*tree)[i].lchild = 0;
        (*tree)[i].rchild = 0;
        (*tree)[i].parent = 0;
    }
    for (int j = n+1; j <= m; ++j) {
        (*tree)[j].parent = 0;
    }
    for (int k = n+1; k <= m; ++k) {
        select(*tree,k-1,&min1,&min2);
        (*tree)[k].lchild = min1;
        (*tree)[k].rchild = min2;
        (*tree)[k].weight = (*tree)[min1].weight + (*tree)[min2].weight;
        (*tree)[min1].parent = k;
        (*tree)[min2].parent = k;
    }
    *code = (char **)malloc(sizeof(char *)*(n+1));
    char cd[n];
    int start,p,c;
    cd[n-1] = 0;
    for (int l = 1; l <= n; ++l) {
        start = n-1;
        c = l;
        for (p = (*tree)[l].parent; p!=0;c = p,p = (*tree)[p].parent) {
            if((*tree)[p].lchild==c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }
        (*code)[l] = (char *)malloc(n-start);
        strcpy((*code)[l],cd+start);
    }
}

void select(struct haffnode * tree,int n,int * min1,int * min2)
{
    int m1,m2;
    int k = 100;
    for (int i = 1; i <= n; ++i) {
        if(tree[i].weight<k&&tree[i].parent==0)
        {
            k = tree[i].weight;
            m1 = i;
        }
    }
    tree[m1].parent = 1;
    k = 100;
    for (int i = 1; i <= n; ++i) {
        if(tree[i].weight<k&&tree[i].parent==0)
        {
            k = tree[i].weight;
            m2 = i;
        }
    }
    tree[m2].parent = 1;
    if(m1>m2)//序号低的放左边，因为新建立的节点总是有最大的序号，所以叶子节点会在左边
    {
        k = m1;
        m1 = m2;
        m2 = k;
    }
    *min1 = m1;
    *min2 = m2;
}
