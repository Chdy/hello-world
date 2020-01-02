//
// Created by 邓岩 on 2019/5/19.
//

/*
 * 危险系数
 问题描述
抗日战争时期，冀中平原的地道战曾发挥重要作用。

地道的多个站点间有通道连接，形成了庞大的网络。但也有隐患，当敌人发现了某个站点后，其它站点间可能因此会失去联系。

我们来定义一个危险系数DF(x,y)：

对于两个站点x和y (x != y), 如果能找到一个站点z，当z被敌人破坏后，x和y不连通，那么我们称z为关于x,y的关键点。相应的，对于任意一对站点x和y，危险系数DF(x,y)就表示为这两点之间的关键点个数。

本题的任务是：已知网络结构，求两站点之间的危险系数。

输入格式
输入数据第一行包含2个整数n(2 <= n <= 1000), m(0 <= m <= 2000),分别代表站点数，通道数；

接下来m行，每行两个整数 u,v (1 <= u, v <= n; u != v)代表一条通道；

最后1行，两个数u,v，代表询问两点之间的危险系数DF(u, v)。

输出格式
一个整数，如果询问的两点不连通则输出-1.
样例输入
7 6
1 3
2 3
3 4
3 5
4 5
5 6
1 6
样例输出

 */

# include <iostream>
# include <vector>

using namespace std;

int n, m, k, j;

vector<int> v[1000];
vector<int> recur;
int step[1000];
int counts[1000];

void dfs(int x) {
    if (x == j) {
        for (int i = 0; i < recur.size(); i++) {
            counts[recur[i]] += 1;
        }
        return;
    }
    for (int i = 0; i < v[x].size(); i++) {
        if (step[v[x][i]] == 0) {
            recur.push_back(v[x][i]);
            step[v[x][i]] = 1;
            dfs(v[x][i]);
            step[v[x][i]] = 0;
            recur.pop_back();
        }
    }
}

int main(void)
{
    int sum = 0;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> k >> j;
        if (k == 0 || j == 0)
            break;
        v[k].push_back(j);
        v[j].push_back(k);
    }
    cin >> k >> j;
    recur.push_back(k);
    step[k] = 1;
    dfs(k);

    for (int i = 1; i <= n; i++) {
        if (counts[i] == counts[k])
            sum++;
    }
    sum -= 2;
    if (sum == -2)
        cout << -1 << endl;
    else
        cout << sum << endl;
    return 0;
}