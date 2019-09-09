//
// Created by 邓岩 on 2019/5/20.
//

/*
 * 对局匹配
问题描述
　　小明喜欢在一个围棋网站上找别人在线对弈。这个网站上所有注册用户都有一个积分，代表他的围棋水平。


　　小明发现网站的自动对局系统在匹配对手时，只会将积分差恰好是K的两名用户匹配在一起。如果两人分差小于或大于K，系统都不会将他们匹配。


　　现在小明知道这个网站总共有N名用户，以及他们的积分分别是A1, A2, ... AN。


　　小明想了解最多可能有多少名用户同时在线寻找对手，但是系统却一场对局都匹配不起来(任意两名用户积分差不等于K)？
输入格式
　　第一行包含两个个整数N和K。
　　第二行包含N个整数A1, A2, ... AN。


　　对于30%的数据，1 <= N <= 10
　　对于100%的数据，1 <= N <= 100000, 0 <= Ai <= 100000, 0 <= K <= 100000
输出格式
　　一个整数，代表答案。
样例输入
10 0
1 4 2 8 5 7 1 4 2 8
样例输出
6
 */

# include <iostream>
# include <algorithm>

using namespace std;
#define ll long long

ll n, k;
ll v[100002];

int main(void)
{
    int m = 0;
    ll count = 0;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int j;
        cin >> j;
        v[j]++;
        m = max(m, j);
    }
    if (k) {
        for (int i = 0; i + k <= m; i++) {
            while (v[i] && v[i + k]) {
                v[i]--;
                v[i + k]--;
                count++;
            }
        }
    } else {
        for (int i = 0; i <= m; i++) {
            if (v[i] >= 2) {
                count += v[i] - 1;
            }
        }
    }
    cout << n - count << endl;
    return 0;
}