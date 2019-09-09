//
// Created by 邓岩 on 2018/11/6.
//

//B树
//一颗B树是具有一下性质的有根树
//1.每个结点x有以下属性
// a. x.n当前存储在结点x中的关键字个数
// b. x.n个关键字本身x.key_1，x.key_2...，以非降序存放
// c. x.leaf一个布尔值，如何x是叶结点，则为TRUE，如果x为内部结点，则为FALSE
//2.每个内部结点x还包含x.n+1个指向其孩子的指针x.c_1，x.c_2...，叶结点没有孩子，所以它们的c_i属性没有定义
//3.关键字x.key对存储在各子树中的关键字范围加以分割: 如果k_i为任意一个存储在以x.c_i为根的子树中的关键字，那么k_1<=x.key_1<=k_2<=...<=x.key_(x.n)<<k_x.(n+1)
//4.每个叶结点具有相同的深度，即树的高度h
//5.每个叶结点所包含的关键字个数有上界和下界，用一个被称为B树的最小度数的固定整数t>=2来表示这些界
// a. 除了根节点以外的每个结点必须至少有t-1个关键字，因此，除了根结点以外的每个内部结点至少有t个孩子，如果树非空，根结点至少有一个关键字
// b. 每个结点至多可包含2t-1个关键字，因此，一个内部结点至多可有2t个孩子，当一个结点敲好有2t-1个关键字时，称该结点是满的

# include <stdio.h>
# include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FLASE 0
#define MIN_DEGREE 4

typedef struct node{
    int leaf;
    int data;
    int n; //关键字的个数
    int key[MIN_DEGREE * 2 + 1]; //指向关键字的数组，大小应为n+1，下标0处弃用
    struct node * child[MIN_DEGREE * 2 + 1]; //保存各个孩子指针的数组，大小为n+1
}BNode;

typedef struct {
    BNode * root;
    int t;
}BTree;

void b_tree_create(BTree * T)
{
    T->root = (BNode *)calloc(1, sizeof(BNode));
    T->root->leaf = TRUE;
    T->root->n = 0;
}

void b_tree_split_child(BNode * x, int i)
{
    int t = MIN_DEGREE;
    BNode * z = (BNode *)calloc(1, sizeof(BNode));
    BNode * y = (x->child)[i];
    z->leaf = y->leaf;
    y->leaf = t - 1;
    for (int k = 1; k < t; ++k) {
        (z->key)[k] = (y->key)[t + k];
    }
    
    for (int j = 0; j < t; ++j) {
        (z->child)[j] = (y->child)[t + j];
    }
    y->n = t - 1;
    memcpy(x->child + i + 1, x->child + i, sizeof(void *) * (t - i));
    (x->child)[i + 1] = z;
    memcpy(x->key + i + 1, x->key + i, sizeof(int) * (t - i));
    (x->key)[i] = (y->key)[t];
    x->n++;
}

BNode * b_tree_search(BTree * T, int k)
{

}

int main(void)
{

    return 0;
}