//
// Created by 邓岩 on 2019/3/9.
//

//蓝桥杯 八皇后改

# include <iostream>
# include <vector>
# include <sstream>
# include <iterator> //istring_iterator在这里
# include <algorithm> //stl算法需要加这个

using namespace std;

int maxv = 0; //当前最大值
int queue8[8];

int check_vaild(int i, int j) { //检查在第i行j列放置皇后是否会冲突
    for (int k = 0; k < i; k++) {
        int value = queue8[k];
        int mis = i - k;
        if (j == value) //判断是否同一列
            return 0;
        if ((value + mis) == j) //判断是否在正对角线
            return 0;
        if ((value - mis) == j) //判断是否在负对角线
            return 0;
    }
    return 1;
}

void backtrack(vector< vector<int> > &res, vector<int> a, int n) {
    if (n == 8) {
        int sum = 0;
        for (int i = 0; i < 8; i++) {
            sum += res[i][queue8[i]];
        }
        maxv = maxv<sum?sum:maxv;
    }
    for (int i = 0; i < 8; i++) {
        if (check_vaild(n, i)) {
            queue8[n] = i;
            a.push_back(i);
            backtrack(res, a, n + 1);
            a.pop_back();
        }
    }
}

int main(void) {
    string s;
    vector< vector<int> > res(8, vector<int>(8));
    for (int i = 0; i < 8; i++) {
        getline(cin , s);
        istringstream str(s);
        copy(istream_iterator<int>(str), istream_iterator<int>(), res[i].begin());
    }
    backtrack(res, {}, 0);
    cout << maxv << endl;
    return 0;
}