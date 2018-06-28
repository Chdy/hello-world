//
// Created by 邓岩 on 2018/5/6.
//

/*------------------------------------
 统计文件中除exlude元素集合以外各单词出现个数
 ------------------------------------*/

# include <iostream>
# include <map>
# include <set>
# include <string>
# include <fstream>

using namespace std;

int main() {//6.4.1
    set<string> exclude = {"2"};
    map<string,size_t > word_count;
    string word;
    ifstream in("/Users/dengyan/exam");
    istream_iterator<string> iter(in),eof;
    while(iter != eof)
    {
        if(exclude.find(*iter) == exclude.end())
            ++word_count[*iter++];
        else
            iter++;
    }
    for (const auto &w : word_count)
        cout << w.first << " occurs " << w.second << endl;
}