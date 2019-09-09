//
// Created by 邓岩 on 2019/5/19.
//

/*
 * 大臣的旅费
问题描述
很久以前，T王国空前繁荣。为了更好地管理国家，王国修建了大量的快速路，用于连接首都和王国内的各大城市。

为节省经费，T国的大臣们经过思考，制定了一套优秀的修建方案，使得任何一个大城市都能从首都直接或者通过其他大城市间接到达。同时，如果不重复经过大城市，从首都到达每个大城市的方案都是唯一的。

J是T国重要大臣，他巡查于各大城市之间，体察民情。所以，从一个城市马不停蹄地到另一个城市成了J最常做的事情。他有一个钱袋，用于存放往来城市间的路费。

聪明的J发现，如果不在某个城市停下来修整，在连续行进过程中，他所花的路费与他已走过的距离有关，在走第x千米到第x+1千米这一千米中（x是整数），他花费的路费是x+10这么多。也就是说走1千米花费11，走2千米要花费23。

J大臣想知道：他从某一个城市出发，中间不休息，到达另一个城市，所有可能花费的路费中最多是多少呢？

输入格式
输入的第一行包含一个整数n，表示包括首都在内的T王国的城市数

城市从1开始依次编号，1号城市为首都。

接下来n-1行，描述T国的高速路（T国的高速路一定是n-1条）

每行三个整数Pi, Qi, Di，表示城市Pi和城市Qi之间有一条高速路，长度为Di千米。

输出格式
输出一个整数，表示大臣J最多花费的路费是多少。

样例输入1
5
1 2 2
1 3 1
2 4 5
2 5 4
样例输出1
135
输出格式
大臣J从城市4到城市5要花费135的路费。
 */

# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

vector<int> ret;
int n;

int step[100000];
vector<pair<int, int> > v[100000];

int sum, mx;
int idx;

void dfs(int x) {
    if (v[x].size() == 1 && step[v[x][0].first] == 1) {
        if (sum > mx) {
            mx = sum;
            idx = x;
        }
        return;
    }
    for (int i = 0; i < v[x].size(); i++) {
        if (step[v[x][i].first] == 0) {
            sum += v[x][i].second;
            step[v[x][i].first] = 1;
            dfs(v[x][i].first);
            sum -= v[x][i].second;
            step[v[x][i].first] = 0;
        }
    }
}

int main(void)
{
    int s, r = 0;
    int from, to, cost;
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> from >> to >> cost;
        v[from].push_back({to, cost});
        v[to].push_back({from, cost});
    }
    step[1] = 1;
    dfs(1);
    step[1] = 0;
    sum = 0;
    mx = 0;
    step[idx] = 1;
    dfs(idx);
    cout << (11 + 10 + mx) * mx / 2 << endl;
    return 0;
}