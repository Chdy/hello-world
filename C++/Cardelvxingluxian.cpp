//
// Created by 邓岩 on 2019/5/20.
//

/*
 * Car的旅行路线
问题描述
　　又到暑假了，住在城市A的Car想和朋友一起去城市B旅游。她知道每个城市都有四个飞机场，分别位于一个矩形的四个顶点上，同一个城市中两个机场之间有一 条笔直的高速铁路，第I个城市中高速铁路了的单位里程价格为Ti，任意两个不同城市的机场之间均有航线，所有航线单位里程的价格均为t。
　　那么Car应如何安排到城市B的路线才能尽可能的节省花费呢?她发现这并不是一个简单的问题，于是她来向你请教。
　　找出一条从城市A到B的旅游路线，出发和到达城市中的机场可以任意选取，要求总的花费最少。
输入格式
　　的第一行有四个正整数s，t，A，B。
　　S表示城市的个数，t表示飞机单位里程的价格，A，B分别为城市A，B的序号，(1<=A，B<=S)。
　　接下来有S行，其中第I行均有7个正整数xi1，yi1，xi2，yi2，xi3，yi3，Ti，这当中的(xi1，yi1)，(xi2，yi2)，(xi3，yi3)分别是第I个城市中任意三个机场的坐标，T I为第I个城市高速铁路单位里程的价格。
输出格式
　　共有n行，每行一个数据对应测试数据，保留一位小数。
样例输入
3 10 1 3
1 1 1 3 3 1 30
2 5 7 4 5 2 1
8 6 8 8 11 6 3
样例输出
47.55
数据规模和约定
　　0<S<=100，
 */

# include <iostream>
# include <vector>
# include <cmath>
# include <iomanip>

using namespace std;

int s, t, A, B;

int x[404], y[404];
int T[101];

double price[404][404];

int main(void)
{
    cin >> s >> t >> A >> B;
    for (int i = 0; i < s; i++) {
        int j = i * 4;
        cin >> x[j] >> y[j] >> x[j + 1] >> y[j + 1] >> x[j + 2] >> y[j + 2] >> T[i];
        if ((x[j + 1] - x[j]) * (x[j + 2] - x[j]) + (y[j + 1] - y[j]) * (y[j + 2] - y[j]) == 0) { //x[j]是给定三个点的直角点，利用点乘判断
            x[j + 3] = x[j + 2] + x[j + 1] - x[j]; //矩形两条对角线的两点x坐标相加的值相等
            y[j + 3] = y[j + 2] + y[j + 1] - y[j];
        } else if ((x[j] - x[j + 1]) * (x[j + 2] - x[j + 1]) + (y[j] - y[j + 1]) * (y[j + 2] - y[j + 1]) == 0) { //x[j + 1]是直角点
            x[j + 3] = x[j + 2] + x[j] - x[j + 1];
            y[j + 3] = y[j + 2] + y[j] - y[j + 1];
        } else {
            x[j + 3] = x[j + 1] + x[j] - x[j + 2];
            y[j + 3] = y[j + 1] + y[j] - y[j + 2];
        }
    }

    for (int i = 0; i < s * 4; i++) {
        for (int j = 0; j < s * 4; j++) {
            if (i == j)
                price[i][j] = 0;
            else if (i/4 == j/4) {
                price[i][j] = abs(sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]))) * T[i/4];
            } else {
                price[i][j] = abs(sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]))) * t;
            }
        }
    }



    for (int d = 0; d < s * 4; d++) {
        for (int i = 0; i < s * 4; i++) {
            for (int j = 0; j < s * 4; j++) {
                price[i][j] = min(price[i][j], price[i][d] + price[d][j]);
            }
        }
    }

    double ret = 200000000;

    for (int i = (A - 1)*4; i < (A - 1)*4 + 4; i++) {
        for (int j = (B - 1)*4; j < (B - 1)*4 + 4; j++) {
            ret = min(ret, price[i][j]);
        }
    }

    printf("%.1lf", ret);

    return 0;
}