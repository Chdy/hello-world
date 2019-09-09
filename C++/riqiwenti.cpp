//
// Created by 邓岩 on 2019/5/22.
//

/*
 * 日期问题
问题描述
　　小明正在整理一批历史文献。这些历史文献中出现了很多日期。小明知道这些日期都在1960年1月1日至2059年12月31日。令小明头疼的是，这些日期采用的格式非常不统一，有采用年/月/日的，有采用月/日/年的，还有采用日/月/年的。更加麻烦的是，年份也都省略了前两位，使得文献上的一个日期，存在很多可能的日期与其对应。


　　比如02/03/04，可能是2002年03月04日、2004年02月03日或2004年03月02日。


　　给出一个文献上的日期，你能帮助小明判断有哪些可能的日期对其对应吗？
输入格式
　　一个日期，格式是"AA/BB/CC"。 (0 <= A, B, C <= 9)
输出格式
　　输出若干个不相同的日期，每个日期一行，格式是"yyyy-MM-dd"。多个日期按从早到晚排列。
样例输入
02/03/04
样例输出
2002-03-04
2004-02-03
2004-03-02

 AA BB CC

 年月日 1 2 3 AA BB CC
 月日年 2 3 1 CC AA BB
 日月年 3 2 1 CC BB AA

 第一个输入三种都有可能
 第二个输入不能做为年
 第三个输入不能作为月

 */

# include <iostream>
# include <string>
# include <vector>
# include <algorithm>

using namespace std;

string AA, BB, CC;

int monthday[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int valid(vector<string> &v) {
    if (v[0] >= "60")
        v[0] = "19" + v[0];
    else
        v[0] = "20" + v[0];

    int flag = 0;
    int year = atoi(v[0].c_str());
    int month = atoi(v[1].c_str());
    int day = atoi(v[2].c_str());
    //cout << year << " " << month << " " << day << endl;

    if (month < 1 || month > 12)
        return 0;

    if (year % 4 == 0 && year%100 || year % 100 == 0) {
        monthday[2]++;
    }

    if (day < 1 || day > monthday[month]) {
        if (monthday[2] == 29)
            monthday[2]--;
        return 0;
    }
    return 1;
}

int main(void) {
    string s;
    getline(cin, AA, '/');
    getline(cin, BB, '/');
    getline(cin, CC);
    vector<vector<string> > v(3);
    v[0].push_back(AA);
    v[0].push_back(BB);
    v[0].push_back(CC);
    v[1].push_back(CC);
    v[1].push_back(AA);
    v[1].push_back(BB);
    v[2].push_back(CC);
    v[2].push_back(BB);
    v[2].push_back(AA);
    vector<string> ret;
    for (int i = 0; i < v.size(); i++) {
        if (!valid(v[i])) { //BB不能为年, CC不能为月
            v.erase(v.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < v.size(); i++) {
        string a = v[i][0] + "-" + v[i][1] + "-" + v[i][2];
        ret.push_back(a);
    }


    sort(ret.begin(), ret.end());
    vector<string>::iterator x = unique(ret.begin(), ret.end());

    for (vector<string>::iterator i = ret.begin() ; i < x; i++)
        cout << *i << endl;

    return 0;
}