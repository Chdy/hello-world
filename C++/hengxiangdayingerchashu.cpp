//
// Created by 邓岩 on 2019/5/20.
//

/*
 * 横向打印二叉树
问题描述
二叉树可以用于排序。其原理很简单：对于一个排序二叉树添加新节点时，先与根节点比较，若小则交给左子树继续处理，否则交给右子树。

当遇到空子树时，则把该节点放入那个位置。

10 8 5 7 12 4 的输入顺序，应该建成二叉树如下图所示，其中.表示空白。

...|-12
10-|
...|-8-|
.......|...|-7
.......|-5-|
...........|-4
本题目要求：根据已知的数字，建立排序二叉树，并在标准输出中横向打印该二叉树。

输入格式
输入数据为一行空格分开的N个整数。 N<100，每个数字不超过10000。

输入数据中没有重复的数字。

输出格式
输出该排序二叉树的横向表示。为了便于评卷程序比对空格的数目，请把空格用句点代替：

样例输入1
10 5 20
样例输出1
...|-20
10-|
...|-5
样例输入2
5 10 20 8 4 7
样例输出2
.......|-20
..|-10-|
..|....|-8-|
..|........|-7
5-|
..|-4
 */

// 思路，首先将数据保存为二叉树，并且因为没有重复数据，可以保存数据的深度，这样就能知道其对应字符串的长度，由于先输出的顺序是从右到左的，那么可以写一个遍历顺序为右中左，这样就可以保证输出顺序

# include <iostream>
#include <numeric>

using namespace std;

int deep[10001];
int lchild[10001];
int rchild[10001];
int parent[10001];
int maxvalue[10001]; //每一层的最大数据

int n;

void build_tree(int root, int k, int d) {
    //cout << k << " " << d << endl;
    if (k < root) {
        if (!lchild[root]) {
            lchild[root] = k;
            parent[k] = root;
            deep[k] = d + 1;
            maxvalue[k] = k;
        } else
            build_tree(lchild[root], k, d + 1);
    } else {
        if (!rchild[root]) {
            rchild[root] = k;
            parent[k] = root;
            deep[k] = d + 1;
            maxvalue[k] = k;
        } else
            build_tree(rchild[root], k, d + 1);
    }
}

void stringconstruct(string &s, int l) {
    if (parent[l] > l) {
        l = parent[l];
        while (l != 0) {
            if (l > parent[l]) {
                int i = 0, m = parent[l];
                while (m) {
                    i += maxvalue[m];
                    m = parent[m];
                }
                s[i + (deep[l] - 2) * 3 + 1] = '|';
                stringconstruct(s, l);
                return;
            }
            l = parent[l];
        }
    } else {
        l = parent[l];
        while (l != 0) {
            if (l < parent[l]) {
                int i = 0, m = parent[l];
                while (m) {
                    i += maxvalue[m];
                    m = parent[m];
                }
                s[i + (deep[l] - 2) * 3 + 1] = '|';
                stringconstruct(s, l);
                return;
            }
            l = parent[l];
        }
    }
}

void print_str(int x) {
    int k = deep[x];
    if (k == 1) {
        cout << x << "-|" << endl;
        return;
    }
//    else
//        cout << string(maxvalue[1] + 1, '.') << "|";

    if (k > 1) {
        int i = 0, m = parent[x];
        while (m) {
            i += maxvalue[m];
            m = parent[m];
        }
        string s(i + (k - 2) * 3 + 1, '.');
        stringconstruct(s, x);
        cout << s << "|"; //有bug，仍然未修复
    }

    if (!lchild[x] && !rchild[x]) //没孩子
        cout << "-" << x << endl;
    else
        cout << "-" << x << "-|" << endl;

}

void traversal(int x) {
    if (rchild[x])
        traversal(rchild[x]);
    print_str(x);
    if (lchild[x])
        traversal(lchild[x]);
}


int main(void)
{
    int root, k;
    cin >> root;
    deep[root] = 1;
    maxvalue[root] = root;
    while (scanf("%d", &k) == 1) {
        build_tree(root, k, 1);
    }
    for (int i = 1; i <= 10000; i++) {
        k = 0;
        while (maxvalue[i]) {
            k++;
            maxvalue[i]/=10;
        }
        maxvalue[i] = k;
    }
    traversal(root);
    return 0;
}