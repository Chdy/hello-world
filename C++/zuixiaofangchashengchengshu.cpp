//
// Created by 邓岩 on 2019/5/21.
//

/*
 * 最小方差生成树
问题描述
给定带权无向图，求出一颗方差最小的生成树。
输入格式
输入多组测试数据。第一行为N,M，依次是点数和边数。接下来M行，每行三个整数U,V,W，代表连接U,V的边，和权值W。保证图连通。n=m=0标志着测试文件的结束。
输出格式
对于每组数据，输出最小方差，四舍五入到0.01。输出格式按照样例。
样例输入
4 5
1 2 1
2 3 2
3 4 2
4 1 1
2 4 3
4 6
1 2 1
2 3 2
3 4 3
4 1 1
2 4 3
1 3 3
0 0
样例输出
Case 1: 0.22
Case 2: 0.00
数据规模与约定
1<=U,V<=N<=50,N-1<=M<=1000,0<=W<=50。数据不超过5组。
 */

# include <iostream>
# include <algorithm>

using namespace std;

int v[51][51];

int n, m;
double ret;

struct edge{
    int from, to;
    double w, d;
} es[1001];

int rd[1001];

int comp(struct edge &l, struct edge &r) {
    return l.w < r.w;
}

int compd(struct edge &l, struct edge &r) {
    return l.d < r.d;
}

void init() {
    for (int i = 1; i <= n; i++)
        rd[i] = i;
}

int find(int x) {
    if (rd[x] == x)
        return x;
    return rd[x] = find(rd[x]);
}

int same(int x, int y) {
    return find(x) == find(y);
}

void unite(int x, int y) {
    int l = rd[x];
    int r = rd[y];
    if (l != r)
        rd[l] = r;
}

void kruskal(int wsum) {
    init();
    int xsum = 0;
    double sum = 0;
    double mean = 1.0 * wsum/(n - 1);
    for (int i = 0; i < m; i++)
        es[i].d = (es[i].w - mean) * (es[i].w - mean);
    sort(es, es + m, compd);
    for (int i = 0; i < m; i++) {
        struct edge a = es[i];
        if (!same(a.from, a.to)) {
            unite(a.from, a.to);
            sum += a.d;
            xsum += a.w;
        }
    }
    if (xsum == wsum)
        ret = min(ret, sum);
}

int main(void) {
    int k = 1;
    while (scanf("%d %d", &n, &m) && (n + m)) {
        ret = 200000000;
        int in = 0, ax = 0;
        for (int i = 0; i < m; i++) {
            cin >> es[i].from >> es[i].to >> es[i].w;
        }
        sort(es, es + m, comp);
        for (int i = 0; i < n - 1; i++) //计算可能的最小权值和，因为边数是点数减一
            in += es[i].w;
        for (int i = m - 1; i >= m - n; i--)
            ax += es[i].w;
        for (int i = in; i <= ax; i++) {
            kruskal(i);
        }
        printf("Case %d: %.2lf\n", k++, ret/(n - 1));
    }
    return 0;
}
