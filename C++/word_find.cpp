//
// Created by 邓岩 on 2018/7/6.
//

# include <istream>
# include <fstream>
# include <vector>
# include <set>
# include <map>
# include <sstream>
# include <iostream>

/*----------------------------------------------------
 输入一个单词，查询该单词在指定文件出现的次数及行号以及该行内容
---------------------------------------------------- */


using namespace std;

class QueryResult{
    friend ostream &print(ostream &os, const QueryResult &qr);
public:
    QueryResult(const string & w,shared_ptr<set<int>> n,shared_ptr<vector<string>> f): findword(w),lines(n),file(f){}
private:
    string findword;
    shared_ptr<set<int>> lines;
    shared_ptr<vector<string>> file;
};

class TextQuery{
public:
    TextQuery(ifstream & infile):file(new vector<string>) {
        string text;
        while(getline(infile,text))
        {
            file->push_back(text);
            int n = file->size() - 1 ;
            istringstream line(text);
            string word;
            while(line >> word)
            {
                auto &lines = wm[word];
                if(!lines)
                {
                    lines.reset(new set<int>);
                }
                lines->insert(n);
            }
        }
    }
    QueryResult query(const string & word) const
    {
        static shared_ptr<set<int>> nodata(new set<int>);
        auto loc = wm.find(word);
        if(loc == wm.end())
            return QueryResult(word,nodata,file);
        else
            return QueryResult(word,loc->second,file);
    }
private:
    shared_ptr<vector<string>> file;
    map<string,shared_ptr<set<int>>> wm;
};

ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.findword << " occurs " << qr.lines->size() << " " << "times" << endl;
    for (auto num : *qr.lines) {
        os << "\t(line " << num+1 << ") " << *(qr.file->begin() + num) << endl;
    }
    return os;
}

int main(void)
{
    ifstream infile("/Users/dengyan/countries");
    TextQuery tq(infile);
    while(true)
    {
        cout << "enter word to look for ,or q to quit\n";
        string s;
        if(!(cin >> s) || s == "q")
            break;
        print(cout,tq.query(s));
    }
    return 0;
}