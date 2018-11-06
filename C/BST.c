//
// Created by 邓岩 on 2018/10/28.
//
//二叉搜索树
//性质：对于任意节点，其左子树节点的值不大于它，右子树的节点不小于它


# include <stdio.h>
# include <stdlib.h>

typedef struct node {
    int value;
    struct node * left, * right, * parent;
}Node,* pNode;

pNode tree_minimum(pNode x) //找到根节点为x的最小节点
{
    if (x == NULL)
        return NULL;

    while (x->left)
        x = x->left;
    return x;
}

pNode tree_maximum(pNode x) //找到根节点为x的最大节点
{
    if (x == NULL)
        return NULL;

    while (x->right)
        x = x->right;
    return x;
}

pNode tree_find(pNode x, int value) //找到根节点为x且权值为value的节点
{
    while (x != NULL && x->value != value)
        if (x->value < value)
            x = x->right;
        else
            x = x->left;

    return x;
}

void inordered_walk(pNode x) //由于是中序遍历，也就是先输出左子树，再输出本身节点，最后输出右子树，由于左子树的值都小于自身，右子树的值都大于自身，且该函数作用于每个节点，那么输出的结果必然是递增的
{
    if (x != NULL)
    {
        inordered_walk(x->left);
        printf("%d ", x->value);
        inordered_walk(x->right);
    }
}

pNode tree_successor(pNode x)
{
    if (x == NULL)
        return NULL;

    if (x->right) //如果有右孩子
        return tree_minimum(x->right);

    //以下会有两种情况，既然该节点没有右孩子
    //那么如果该节点是其父节点的左孩子，这样的话，其父节点就是后继
    //或者它是父节点的右孩子，那么存在一个它最近祖先x，该x是另一个节点y的左孩子，那y就是它的后继

    while (x->parent && x==x->parent->right) //当结束时，x必然是某节点的左子树，那么只需要找它的父亲即可
        x = x->parent;

    return x->parent;
}

void tree_insert(pNode * T, int value)
{
    pNode y = NULL;
    pNode x = *T;
    if (*T == NULL)
    {
        *T = (pNode)calloc(1, sizeof(Node)); //使用calloc这样可以减少初始化的操作
        (*T)->value = value;
        return;
    }

    while (x != NULL) {
        y = x;
        if (x->value < value)
            x = x->right;
        else
            x = x->left;
    }

    if (y->value < value) {
        y->right = (pNode)calloc(1, sizeof(Node));
        y->right->value = value;
        y->right->parent = y;
    } else {
        y->left = (pNode)calloc(1, sizeof(Node));
        y->left->value = value;
        y->left->parent = y;
    }
}

void tranplant(pNode * x, pNode y)
{
    if (*x == NULL)
        return;

    if ((*x)->parent == NULL) //根节点
    {
        *x = y;
        y->parent = NULL;
    }
    else if ((*x)->parent->left == *x) { //如果被替换的是左孩子
        if (y != NULL)
            y->parent = (*x)->parent;
        (*x)->parent->left = y;
    } else { //如果被替换的是右孩子
        if (y != NULL)
            y->parent = (*x)->parent;
        (*x)->parent->right = y;
    }
}

int tree_delete(pNode * T, int val)
{
    if (*T == NULL)
        return -1;

    pNode r = *T;
    //以下删除有三种情况
    //要么删除点没有孩子，则直接删除，并修改父节点的对应的子节点为NULL
    //如果有单个孩子，那么使用将其孩子移动到该被删除孩子处
    //如果有两个孩子，删除节点后，将其后继移动到被删除处，此时由于它有右子树，那么其后继一定在右子树上，由于其后继是其右子树上的最小节点，那么其后继一定没有左子树(因为左子树上的点一定比它小)，但是可能有右子树，如果它有右子树，则需要先用它的右子树替换它，再用它替换到被删除的节点处

    if((r = tree_find(r, val)) == NULL) //如果没有找到节点
        return -1;
    if (r->left == NULL) //如果没有左子树
        tranplant(&r, r->right);
    else if (r->right == NULL) //如果没有右子树
        tranplant(&r, r->left);
    else { //两个子树都有
        pNode next = tree_minimum(r->right); //找其后继
        if (next->parent != r) {
            tranplant(&next, next->right); //取下后继点
            next->right = r->right;
            r->right->parent = next;
        }
        next->left = r->left;
        next->left->parent = next;
        if (r == *T) //如果删除的是头节点，这里必须要传送保存根节点结构的地址
            tranplant(T, next); //如果没有进行上面的if语句，那么现在的next就是r的右孩子
        else //如果使用这部，虽然r的确是指向根节点，但是&r只是一个函数内部的局部地址而已，无法真正的对树指向的根值进行改变，所以如果一开始定义一个节点，节点中的数据再指向根就会方便很多
            tranplant(&r, next); //如果没有进行上面的if语句，那么现在的next就是r的右孩子
    }
    return 0;
}

int main(void)
{
    setbuf(stdout, NULL);
    pNode T = NULL;
    printf("请输入想要输入的节点个数:");
    int i, k;
    scanf("%d", &i);
    printf("开始输入数据...\n");
    for (int j = 0; j < i; ++j) {
        scanf("%d", &k);
        tree_insert(&T, k);
    }
    tree_delete(&T, 2);
    inordered_walk(T);
}