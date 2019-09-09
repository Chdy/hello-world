//
// Created by 邓岩 on 2019/5/20.
//

/*
 * 网络寻路
问题描述
X 国的一个网络使用若干条线路连接若干个节点。节点间的通信是双向的。某重要数据包，为了安全起见，必须恰好被转发两次到达目的地。该包可能在任意一个节点产生，我们需要知道该网络中一共有多少种不同的转发路径。

源地址和目标地址可以相同，但中间节点必须不同。

如下图所示的网络。




输入格式
输入数据的第一行为两个整数N M，分别表示节点个数和连接线路的条数(1<=N<=10000; 0<=M<=100000)。

接下去有M行，每行为两个整数 u 和 v，表示节点u 和 v 联通(1<=u,v<=N , u!=v)。

输入数据保证任意两点最多只有一条边连接，并且没有自己连自己的边，即不存在重边和自环。

输出格式
输出一个整数，表示满足要求的路径条数。
样例输入1
3 3
1 2
2 3
1 3
样例输出1
6
样例输入2
4 4
1 2
2 3
3 1
1 4
样例输出2
10
 */

# include <iostream>
# include <vector>

using namespace std;

#define ll long long

vector<int> v[10001];
int step[10001];

ll n, m;
ll sum;

void dfs(int x, int count) {
    if (count == 2) {
        sum += v[x].size() - 1; //到达第二个中间结点后就不用继续走了，加上该中间结点的所有相邻点个数，减掉一个是因为下一步不能往回走
        return;
    }
    step[x] = 1;
    for (int i = 0; i < v[x].size(); i++) {
        if (step[v[x][i]] == 0)
            dfs(v[x][i], count + 1);
    }
    step[x] = 0;
}

int main(void)
{
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        v[l].push_back(r);
        v[r].push_back(l);
    }
    for (int i = 1; i <= n; i++) {
        dfs(i, 0);
    }
    cout << sum << endl;
    return 0;
}