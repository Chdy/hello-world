//
// Created by 邓岩 on 2018/10/29.
//

# include <stdio.h>
# include <stdlib.h>

//红黑树
//每个节点包含5个属性，颜色，权值，左子树指针，右子树指针
//一颗红黑树是满足下列红黑形式的二叉搜索树
//1. 每个节点或者是红色的，或者是黑色的
//2. 根节点是黑色的
//3. 每个叶节点是黑色的，这里说的叶节点是代表每个真正的叶节点还有两个子节点，那两个子节点也是黑色的，比如一个只有一个根节点的树，它为黑色，但是视作它还有两个子节点，也均为黑色
//4. 如果一个节点是红色的，则它的两个叶节点都是黑色的
//5. 对于每个节点，从该节点到其所有后代叶节点的简单路径上，均包含个数相同的黑色节点

//做左旋转时，x的父节点域和其右节点域会改变，右孩子的父节点域和右孩子的左孩子的父节点域会改变
//旋转操作在任何情况都能正常进行
//由于每次增加的都是红节点，且旋转操作绕两红点进行，性质上就像将一个红节点移动到了另一边，所以旋转操作不会破坏性质5
//此代码对于被删除的节点没有释放空间，而且管理节点的T的左孩子域没有指向树的最小节点，树中的最大节点的右孩子域没有指向管理节点，后面进行更改

#define RED 1
#define BLACK 0

typedef struct node {
    struct node * left;
    struct node * right;
    struct node * parent;
    int value;
    int color;
}Node, *pNode;

struct node * nil;

pNode tree_minimum(pNode x) //找到根节点为x的最小节点
{
    if (x == NULL)
        return NULL;

    while (x->left != nil)
        x = x->left;
    return x;
}

pNode rb_find(pNode T, int value) //找到根节点为x且权值为value的节点
{
    T = T->parent; //根节点
    while (T != nil && T->value != value)
        if (T->value < value)
            T = T->right;
        else
            T = T->left;

    return T;
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

void left_rotate(pNode x)
{
    pNode y = x->right;

    x->right = y->left;
    if (y->left != nil)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent->parent == x) //如果x是根节点
        x->parent->parent = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void right_rotate(pNode x)
{
    pNode y = x->left;

    x->left = y->right;
    if (y->right != nil)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent->parent == x)
        x->parent->parent = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

void rb_insert_fixup(pNode T, pNode x) // T是一个管理节点，T->parent指向根节点
{
    pNode y;

    while (x->parent->color == RED) //如果x的父亲是红节点，此时x的祖节点必为黑色(不然在插入前就不满足条件)
    {
        if (x->parent->parent->left == x->parent) { //如果x的父亲是左孩子
            y = x->parent->parent->right; //y是其叔节点
            if (y != nil && y->color == RED) { //此状态下可能会破坏性质4
                x->parent->color = BLACK; //父节点变为黑
                y->color = BLACK; //叔节点变为黑
                x->parent->parent->color = RED; //祖节点变为红，如果其曾祖节点为红色，那么性质4被破坏
                x = x->parent->parent; //进行下一轮循环，查看其祖节点和曾祖节点是够满足要求
            } else if (x == x->parent->right) { //此时其叔节点要么为空(空可以看作黑)要么为黑，如果x为内侧插入
                x = x->parent;
                left_rotate(x);
            } else {//外侧插入
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                right_rotate(x->parent->parent);
            }
        } else { //如果x的父亲是右孩子
            y = x->parent->parent->left; //y是其叔节点
            if (y != nil && y->color == RED) {
                x->parent->color = BLACK; //父节点变为黑
                y->color = BLACK; //叔节点变为黑
                x->parent->parent->color = RED; //祖节点变为红
                x = x->parent->parent; //查看其祖节点和曾祖节点是够满足要求
            } else if (x == x->parent->left) { //此时其叔节点要么为空(空可以看作黑)要么为黑，如果x为内侧插入
                x = x->parent;
                right_rotate(x);
            } else {
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                left_rotate(x->parent->parent);
            }
        }
        T->parent->color = BLACK; //这部不能掉，不然当根节点变成红色后会引发不必要的操作，根节点由红变黑不影响任何性质
    }
}

void rb_insert(pNode T, int val)
{
    pNode x, y, z;

    y = nil;
    x = T->parent; //根节点
    z = (pNode)malloc(sizeof(Node));
    z->color = RED;
    z->value = val;
    z->left = nil;
    z->right = nil;

    while (x != nil) {
        y = x;
        if (x->value < val)
            x = x->right;
        else
            x = x->left;
    }

    z->parent = y;

    if (y == nil)
    {
        z->color = BLACK;
        T->parent = z;
        z->parent = T;
        return;
    }
    else if (y->value < z->value)
        y->right = z;
    else
        y->left = z;
    rb_insert_fixup(T, z);
}

void rb_transplant(pNode u, pNode v)
{
    if (u->parent->parent == u) { //u为根节点
        u->parent->parent = v;
    } else if (u->parent->left == u) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

/*
 * 运行此函数时，就说明了x的前继y是一个黑节点
 * x如果为黑，那么x点必为nil点，(因为y为黑，并且y没有左孩子，那么其不可能有一个非nil的黑右孩子)，否则一开始便破坏了性质5
 * 如果x为红，将其直接变为黑即可
 */

void rb_delete_fixup(pNode T, pNode x)
{
    /*
     * 第一次进入循环时x必为nil，此时需要根据x的兄弟节点来判别情况
     * 如果x的兄弟是红色，那么其兄弟必然有两个非nil的左右黑孩子，否则一开始便不符合情况5
     * 如果其兄弟为黑，那么其兄弟要么没有孩子，要么有两个红孩子，要么有一个红孩子
     */

    pNode w;
    while (x != T->parent && x->color == BLACK) {
        if (x == x->parent->left) { //如果x是左孩子
            w = x->parent->right; //w是x的兄弟节点
//case1:
            if (w->color == RED) {

                /*
                 * 如果w是红色，此时w和x的父亲就是黑色，而且w必有两个非nil黑孩子，否则破坏性质5
                 * 这两个黑孩子可能有红孩子，如果左孩子没有红孩子，会进行下面的case2操作
                 * 将w和其父亲反色，然后左旋转
                 * 此时的状态可以看作w是根节点为黑色，w有一个左孩子，是w和x此前的父亲(红色)，w有一个右孩子，就是旋转前的右孩子(黑色，可能有数量不定的红孩子)
                 * w的左孩子此时也有两个孩子，左边的是x(nil)，右边的是w旋转前的左孩子(黑色，可能有数量不定的红孩子)
                 */

                w->parent->color = RED; //旋转点及其右孩子变色
                w->color = BLACK;
                left_rotate(w->parent); //然后左转，此时w的左孩子(黑色)成为了x父亲的右孩子，w成为了x的爷爷
                w = x->parent->right; //重新将w设置为x的兄弟
            }
//case2:
            if (w->left->color == BLACK && w->right->color == BLACK) {

                /*
                 * 如果x的兄弟左右孩子的颜色都为黑，那么这种情况只可能是由case1的旋转操作得来的
                 * 即case1的w的左孩子(非nil黑色)没有红色孩子，因为不存在互为兄弟的黑色节点都没有红孩子的情况
                 */

                w->color = RED; //如果w的左孩子有红孩子的话这步会直接导致性质4被破坏
                x = w->parent; //此时x是红色，循环退出后将其变为黑色即可
            } else if (w->right->color == BLACK) {
//case3:
                /*
                 * 如果w的右子树是黑色，那么w的右孩子就是nil。因为w本身是黑色，其不可能有黑色孩子(否则破坏性质5)
                 * 由于w为黑色时，其必有一个红孩子，因为不存在互为兄弟的黑色节点都没有红孩子的情况
                 * w此时是右子树，它的红孩子是它的左节点，处于内侧，需要通过旋转将红节点移动到外侧
                 * 将w和w的左孩子反色后右旋转
                 * 此时的状态可以看作根节点是x的父亲，颜色未知(因为旋转前w和x都为黑色，其父亲什么颜色没有影响)
                 * 根节点的左孩子是x(nil)，右孩子是旋转前w的左孩子(黑色，本来是红色，反色后旋转)，根节点的右孩子的右孩子(红色，本来是黑色，就是旋转前的w)
                 */

                w->left->color = BLACK; //w的左孩子原本为红色
                w->color = RED; //将w由黑色变为红色
                right_rotate(w); //将w点和其左孩子反色然后右旋转，形状上就像将左孩子移动到了右孩子的位置
                w = x->parent->right; //将w重新设置为x的兄弟，也可以用w = w->parent
            }
//case4:
/*
 * 此时状态有两种，w有两个红孩子，或者有一个右红孩子
 * 此时有w的父节点(颜色未知)，w(颜色为黑)，w的右子节点(颜色为红)，w的左子节点(可能存在，存在就为红，存在与否对下面的操作无影响)
 * 将w->parent，w，w->right 变为黑红黑，或者黑黑黑，取决于w的父节点的颜色，父节点为黑就变为黑黑黑，否则为黑红黑，也就是w变为其父亲的颜色
 * 因为下面需要绕w的父亲进行左旋转，w就会代替其父亲的位置，所以需要w和其父亲同色
 * 看上去就像是w失去了一个孩子，该孩子移动到了x处
 */
            w->color = w->parent->color; //w变为父亲的颜色
            w->parent->color = BLACK; //w的父亲变为黑色
            w->right->color = BLACK; //w的右孩子变为黑色
            left_rotate(w->parent); //左旋转
            x = T->parent; //退出循环
        } else { //x为右孩子，与上面情况对称
            w = x->parent->left;
//case1:
            if (w->color == RED) {
                w->parent->color = RED;
                w->color = BLACK;
                right_rotate(w->parent);
                w = x->parent->right;
            }
//case2:
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else if (w->left->color == BLACK) {
//case3:
                w->right->color = BLACK;
                w->color = RED;
                left_rotate(w);
                w = x->parent->right;
            }
//case4:
            w->color = x->parent->color;
            w->parent->color = BLACK;
            w->left->color = BLACK;
            right_rotate(w->parent);
        }
    }
    x->color = BLACK;
}

void rb_delete(pNode T, int val)
{
    pNode x, y, z;
    int color;

    if ((z = rb_find(T, val)) == nil) //未找到
        return;
    y = z;
    color = y->color;

    if (z->left == nil) {

       /*
        * 如果被删除节点最多一个孩子，该节点可能为黑色，也可能为红色
        * 如果为红色，那么它必定没有孩子，删除一个无孩子的红节点没有任何影响
        * 如果为黑色，那么它可能有一个红孩子，也可能没孩子
        * 如果为黑色且有一个红孩子，则直接使用将该红孩子替换它后变为黑色
        * 如果为黑色且没有孩子，x则为nil节点，那么则需rb_delete_pickup修复该红黑树
        */

        x = z->right;
        rb_transplant(z, z->right);
    } else if(z->right == nil) {
        x = z->left;
        rb_transplant(z, z->left);
    } else {

        /*
         * 此时被删除的z节点有两个孩子，先用后继点y移动到被删除的z处并变为z的颜色，那么可以看做实际上是删除了y节点
         * y必没有左孩子(如果其有左孩子，那么其左孩子就是y的前继)，而y本身必定在z的右子树上
         * 如果y是红节点，那么其必定也没有右孩子
         * 如果y是黑节点，那么可能有右孩子，如果有，该右孩子是唯一节点且必为红，只需要用该红孩子移动到y处变黑即可
         */

        y = tree_minimum(z->right);
        color = y->color; //保存后继点y的颜色，因为实际上是y被删除了
        x = y->right; //由于y可能有唯一的右红孩子，如果确实有红孩子，该红孩子就能顶替y，如果没有，x就是nil
        if (y->parent == z) {

            /*
             * 如果z的后继正好是其右孩子
             * 如果x为nil，则y没有右孩子，y有可能为红，也可能为黑
             * 由于x可能为nil，需要将nil的父节点设置为y，不然后面的rb_delete_fixup传递的x是nil却无法找到其父节点
             */

             x->parent = y;
        } else {

            /*
             * 如果y不是z的右孩子，则先用y的右孩子x(可能为红或者nil)替换y
             * 由于y后面要移动到z处，先将z的右子树和y绑定
             */

            rb_transplant(y, x);
            y->right = z->right;
            y->right->parent = y;
        }

        /*
         * 将y替换z，并将z的左子树和y绑定
         */

        rb_transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }

    /*
     * 被删除的节点已经由其后继补上，问题是其后继失去后，其后继的右孩子顶替后继所产生的影响
     * 如果x是红色，说明y有一个红色右孩子，y必然是黑色，前面的操作已经将x放置到y的位置了，后面只需要调用rb_delete_fixup将红变黑即可
     * 如果y为红色且没有右孩子，删除一个红色节点没有影响，下面的if语句会失败
     * 如果y为黑色且没有右孩子，删除一个黑色节点后会破坏性质5，由于x是y的右孩子，那么x就是nil，如果x为一个非nil的黑节点，在删除进行前，由于x的前继y并没有左节点，此时已经破坏了性质5
     */

    if (color == BLACK)
        rb_delete_fixup(T, x);
}

void inordered_walk(pNode T)
{
    if (T != nil) {
        inordered_walk(T->left);
        printf("%d ", T->value);
        inordered_walk(T->right);
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    int i, n;
    nil = (pNode)calloc(1, sizeof(Node));
    nil->color = BLACK;
    pNode T = (pNode)calloc(1, sizeof(Node)); //设置一个空节点，其parent指向根节点，左节点指向最小节点，右节点指向NULL
    T->parent = nil;
    printf("请输入想要插入的数目: ");
    scanf("%d", &i);
    for (int j = 0; j < i; ++j) {
        scanf("%d", &n);
        rb_insert(T, n);
    }
    rb_delete(T, 3);
    inordered_walk(T->parent);
    return 0;
}