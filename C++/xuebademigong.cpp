//
// Created by 邓岩 on 2019/5/21.
//

/*
 * 学霸的迷宫
问题描述
　　学霸抢走了大家的作业，班长为了帮同学们找回作业，决定去找学霸决斗。但学霸为了不要别人打扰，住在一个城堡里，城堡外面是一个二维的格子迷宫，要进城堡必须得先通过迷宫。因为班长还有妹子要陪，磨刀不误砍柴功，他为了节约时间，从线人那里搞到了迷宫的地图，准备提前计算最短的路线。可是他现在正向妹子解释这件事情，于是就委托你帮他找一条最短的路线。
输入格式
　　第一行两个整数n， m，为迷宫的长宽。
　　接下来n行，每行m个数，数之间没有间隔，为0或1中的一个。0表示这个格子可以通过，1表示不可以。假设你现在已经在迷宫坐标(1,1)的地方，即左上角，迷宫的出口在(n,m)。每次移动时只能向上下左右4个方向移动到另外一个可以通过的格子里，每次移动算一步。数据保证(1,1)，(n,m)可以通过。
输出格式
　　第一行一个数为需要的最少步数K。
　　第二行K个字符，每个字符∈{U,D,L,R},分别表示上下左右。如果有多条长度相同的最短路径，选择在此表示方法下字典序最小的一个。
样例输入
Input Sample 1:
3 3
001
100
110

Input Sample 2:
3 3
000
000
000
样例输出
Output Sample 1:
4
RDRD

Output Sample 2:
4
DDRR
数据规模和约定
　　有20%的数据满足：1<=n,m<=10
　　有50%的数据满足：1<=n,m<=50
　　有100%的数据满足：1<=n,m<=500。
 */

# include <iostream>
# include <queue>

using namespace std;

int step[501][501];

string v[500];

int n, m;

typedef pair<int, int> pos;

struct {
    int x, y;
} direct[4] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}}; //D,L,R,U

string trans = "DLRU";

string ret;

int judge(int x, int y) {
    if (x >= n || x < 0)
        return 0;
    if (y >= m || y < 0)
        return 0;
    if (step[x][y] || v[x][y] == '1')
        return 0;
    return 1;
}

void bfs(int x, int y) {
    queue<pos> q;
    q.push(pos(x, y));
    while (!q.empty()) {
        pos cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int xx = cur.first + direct[i].x;
            int yy = cur.second + direct[i].y;
            if (judge(xx, yy)) {
                step[xx][yy] = step[cur.first][cur.second] + 1;
                q.push(pos(xx, yy));
            }
        }
    }
}

int dfs(int x, int y, int cur) { //dfs路径导出
    if (cur == step[n - 1][m - 1]) {
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        int xx = x + direct[i].x;
        int yy = y + direct[i].y;
        if (x >= n || x < 0 || y >= m || y < 0)
            continue;
        ret.push_back(trans[i]);
        if (step[xx][yy] == cur + 1)
            if (dfs(xx, yy, cur + 1) == 1)
                return 1;
        ret.erase(ret.size() - 1, ret.size());
    }
    return 0;
}

int main(void)
{
    cin >> n >> m;
    getchar();
    for (int i = 0; i < n; i++) {
        getline(cin, v[i]);
    }

    step[0][0] = 1;
    bfs(0, 0);
    dfs(0, 0, 1);
    cout << ret.size() << endl;
    cout << ret << endl;
    return 0;
}