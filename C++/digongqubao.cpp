//
// Created by 邓岩 on 2019/5/19.
//

/*
 * 地宫取宝
 *
   问题描述
　　X 国王有一个地宫宝库。是 n x m 个格子的矩阵。每个格子放一件宝贝。每个宝贝贴着价值标签。

　　地宫的入口在左上角，出口在右下角。

　　小明被带到地宫的入口，国王要求他只能向右或向下行走。

　　走过某个格子时，如果那个格子中的宝贝价值比小明手中任意宝贝价值都大，小明就可以拿起它（当然，也可以不拿）。

　　当小明走到出口时，如果他手中的宝贝恰好是k件，则这些宝贝就可以送给小明。

　　请你帮小明算一算，在给定的局面下，他有多少种不同的行动方案能获得这k件宝贝。
输入格式
　　输入一行3个整数，用空格分开：n m k (1<=n,m<=50, 1<=k<=12)

　　接下来有 n 行数据，每行有 m 个整数 Ci (0<=Ci<=12)代表这个格子上的宝物的价值
输出格式
　　要求输出一个整数，表示正好取k个宝贝的行动方案数。该数字可能很大，输出它对 1000000007 取模的结果。
样例输入
2 2 2
1 2
2 1
样例输出
2
样例输入
2 3 2
1 2 3
2 1 5
样例输出
14
 *
 */

# include <iostream>

using namespace std;

long long dp[51][51][15][15]; //dp[x][y][k][z] 代表从下标x, y处此时手上物品为k的且物品最大值为k的情况下有多种种路径到达终点且满足条件
long long v[51][51];

#define N 1000000007

long long n, m, k;

long long dfs(int x, int y, int sum, int max) {
    long long s = 0;
    if (dp[x][y][sum][max] != -1)
        return dp[x][y][sum][max];

    if (x == n && y == m) {
        if (sum == k || sum == k - 1 && v[x][y] > max) {
            dp[x][y][sum][max] = 1;
            return 1;
        } else {
            dp[x][y][sum][max] = -1;
            return 0;
        }
    }

    if (x + 1 <= n) {
        if (v[x][y] > max) {
            s += dfs(x + 1, y, sum + 1, v[x][y])%N;
        }
        s += dfs(x + 1, y, sum, max)%N;
    }

    if (y + 1 <= m) {
        if (v[x][y] > max) {
            s += dfs(x, y + 1, sum + 1, v[x][y])%N;
        }
        s += dfs(x, y + 1, sum, max)%N;
    }
    dp[x][y][sum][max] = s%N;
    return dp[x][y][sum][max];
}

int main(void) {
    cin >> n >> m >> k;
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> v[i][j];
            ++v[i][j];
        }
    }
    cout << dfs(1, 1, 0, 0);
    return 0;
}