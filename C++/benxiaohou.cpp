//
// Created by 邓岩 on 2019/5/21.
//

/*
 * 笨小猴
问题描述
　　笨小猴的词汇量很小，所以每次做英语选择题的时候都很头疼。但是他找到了一种方法，经试验证明，用这种方法去选择选项的时候选对的几率非常大！
　　这种方法的具体描述如下：假设maxn是单词中出现次数最多的字母的出现次数，minn是单词中出现次数最少的字母的出现次数，如果maxn-minn是一个质数，那么笨小猴就认为这是个Lucky Word，这样的单词很可能就是正确的答案。
输入格式
　　输入文件只有一行，是一个单词，其中只可能出现小写字母，并且长度小于100。
输出格式
　　输出文件共两行，第一行是一个字符串，假设输入的的单词是Lucky Word，那么输出“Lucky Word”，否则输出“No Answer”；第二行是一个整数，如果输入单词是Lucky Word，输出maxn-minn的值，否则输出0。
样例输入
error
样例输出
Lucky Word
2
样例说明
　　单词error中出现最多的字母r出现了3次，出现次数最少的字母出现了1次，3-1=2，2是质数。
样例输入
olympic
样例输出
No Answer
0
样例说明
　　单词olympic中所有字母都只出现了1次，1-1=0，0不是质数。
 */

# include <iostream>
# include <string>

using namespace std;

int v[25];

int main(void)
{
    int in = 100000000, ax = 0;
    string s;
    getline(cin, s);
    for (int i = 0; i < s.size(); i++) {
        v[s[i] - 'a']++;
    }
    for (int i = 0; i <= 25; i++) {
        if (v[i] != 0) {
            if (v[i] > ax)
                ax = v[i];
            else if (v[i] < in)
                in = v[i];
        }
    }
    int pri = ax - in;
    if (pri <= 1) {
        cout << "No Answer" << endl;
        cout << 0 << endl;
        return 0;
    }

    for (int i = 2; i < pri; i++) {
        if (pri%i == 0) {
            cout << "No Answer" << endl;
            cout << 0 << endl;
            return 0;
        }
    }
    cout << "Lucky Word" << endl;
    cout << pri << endl;
    return 0;
}