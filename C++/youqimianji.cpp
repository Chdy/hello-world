//
// Created by 邓岩 on 2019/5/20.
//

/*
 * 油漆面积
问题描述
　　X星球的一批考古机器人正在一片废墟上考古。
　　该区域的地面坚硬如石、平整如镜。
　　管理人员为方便，建立了标准的直角坐标系。


　　每个机器人都各有特长、身怀绝技。它们感兴趣的内容也不相同。
　　经过各种测量，每个机器人都会报告一个或多个矩形区域，作为优先考古的区域。


　　矩形的表示格式为(x1,y1,x2,y2)，代表矩形的两个对角点坐标。


　　为了醒目，总部要求对所有机器人选中的矩形区域涂黄色油漆。
　　小明并不需要当油漆工，只是他需要计算一下，一共要耗费多少油漆。


　　其实这也不难，只要算出所有矩形覆盖的区域一共有多大面积就可以了。
　　注意，各个矩形间可能重叠。


　　本题的输入为若干矩形，要求输出其覆盖的总面积。
输入格式
　　第一行，一个整数n，表示有多少个矩形(1<=n<10000)
　　接下来的n行，每行有4个整数x1 y1 x2 y2，空格分开，表示矩形的两个对角顶点坐标。
　　(0<= x1,y1,x2,y2 <=10000)
输出格式
　　一行一个整数，表示矩形覆盖的总面积面积。
样例输入
3
1 5 10 10
3 1 20 20
2 7 15 17
样例输出
340
样例输入
3
5 2 10 6
2 7 12 10
8 1 15 15
样例输出
128
 */

# include <iostream>
# include <algorithm>

using namespace std;

#define ll long long

bool area[10001][10001];

int main(void)
{
    int x1, y1, x2, y2;
    ll n, sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);
        for (int j = x1; j < x2; j++) {
            for (int k = y1; k < y2; k++) {
                if (!area[j][k]) {
                    area[j][k] = true;
                    sum++;
                }
            }
        }
    }
    cout << sum << endl;
    return 0;
}


/*
struct Square {
    ll x1, y1, x2, y2;
    ll area() {
        return abs(y2 - y1) * abs(x2 - x1);
    }
};

int comp(Square &l, Square &r) {
    return l.x1 < l.x2;
}

Square v[10001];

ll n;

ll intersectionarea(Square &l, Square &r) { //计算相交面积
    Square a;
    if (l.x2 <= r.x1 || l.y1 >= r.y2 || l.y2 <= r.y1)
        return 0;
    if (l.y1 <= r.y1) { //r 在 l的上方
        a.x1 = r.x1;
        a.y1 = r.y1;
        if (l.y2 >= r.y2) { //r被l包围
            a.x2 = r.x2;
            a.y2 = r.y2;
        } else {
            a.x2 = l.x2;
            a.y2 = l.y2;
        }
    } else { //r 在 l的下方
        a.x1 = r.x1;
        a.y1 = r.y2;
        if (l.x2 >= r.x2) {
            a.x2 = l.x2;
            a.y2 = l.y1;
        } else {
            a.x2 = r.x2;
            a.y2 = l.y1;
        }
    }
    return a.area();
}

int main(void)
{
    ll sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i].x1 >> v[i].y1 >> v[i].x2 >> v[i].y2;
        sum += v[i].area();
    }
    cout << sum << endl;
    sort(v, v + n, comp);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll k = intersectionarea(v[i], v[j]);
            if (k == 0)
                break;
            sum -= k;
        }
    }
    cout << sum << endl;
    return 0;
}*/