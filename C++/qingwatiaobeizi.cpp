//
// Created by 邓岩 on 2019/5/23.
//

/*
 * 青蛙跳杯子
问题描述
　　X星球的流行宠物是青蛙，一般有两种颜色：白色和黑色。
　　X星球的居民喜欢把它们放在一排茶杯里，这样可以观察它们跳来跳去。
　　如下图，有一排杯子，左边的一个是空着的，右边的杯子，每个里边有一只青蛙。


　　*WWWBBB


　　其中，W字母表示白色青蛙，B表示黑色青蛙，*表示空杯子。


　　X星的青蛙很有些癖好，它们只做3个动作之一：
　　1. 跳到相邻的空杯子里。
　　2. 隔着1只其它的青蛙（随便什么颜色）跳到空杯子里。
　　3. 隔着2只其它的青蛙（随便什么颜色）跳到空杯子里。


　　对于上图的局面，只要1步，就可跳成下图局面：


　　WWW*BBB


　　本题的任务就是已知初始局面，询问至少需要几步，才能跳成另一个目标局面。


　　输入为2行，2个串，表示初始局面和目标局面。
　　输出要求为一个整数，表示至少需要多少步的青蛙跳。
样例输入
*WWBB
WWBB*
样例输出
2
样例输入
WWW*BBB
BBB*WWW
样例输出
10
 */

# include <iostream>
# include <string>
# include <queue>
# include <algorithm>
# include <map>

using namespace std;

string str;
string goal;

int step = 1;

map<string, int> s;


int BFS() {
    queue<string> q;
    q.push(str);
    s[str] = 0;
    int k = 1;
    while (!q.empty()) {
        string x = q.front();

        q.pop();
        int pos = x.find("*");
        int v = s[x];
        for (int j = -3; j <= 3; j++) {
            int newpos = pos + j;
            if (newpos >= 0 && newpos < str.size()) {
                string newstr = x;
                swap(newstr[newpos], newstr[pos]);
                if (newstr == goal) {
                    return s[x] + 1;
                }
                if (s.find(newstr) == s.end()) {
                    s[newstr] = v + 1;
                    q.push(newstr);
                }
            }
        }
    }
    return 0;
}

int main(void) {
    cin >> str >> goal;
    if (str == goal)
        cout << 0 << endl;

    cout << BFS() << endl;
    return 0;
}