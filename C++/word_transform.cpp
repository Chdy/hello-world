//
// Created by 邓岩 on 2018/5/17.
//

/*---------------------------------------------
 "/Users/dengyan/word_trans" 文件保存转换规则，格式为key value
 h how
 r are
 u you
 "/Users/dengyan/word_trans" 为需要转换的文件
 ---------------------------------------------*/

map<string,string> buildmap(ifstream &mapfile);
const string & trans(const string &str,const map<string,string> &maprule);
void word_trans(ifstream &input,ifstream &mapfile); //将ifstream改为istream后可使用cin作为参数

map<string,string> buildmap(ifstream &mapfile)
{
    map<string,string> remap;
    string str,line;
    while(getline(mapfile,line))
    {
        istringstream record(line);
        record >> str;
        record >> remap[str];
    }
    return remap;
}

const string & trans(const string &str,const map<string,string> &maprule)
{
    auto map_at = maprule.find(str);
    if(map_at != maprule.cend())
        return map_at->second;
    else
        return str;
}

void word_trans(ifstream &input,ifstream &mapfile) //将ifstream改为istream后可使用cin作为参数
{
    map<string,string> maprule = buildmap(mapfile);
    string line,word;
    while (getline(input,line))
    {
        istringstream record(line);
        while (record >> word)
            cout << trans(word,maprule) << " ";
        cout << endl;
    }
}

int main() {//6.4.1
    ifstream input("/Users/dengyan/test");
    ifstream maprule("/Users/dengyan/word_trans");
    word_trans(input,maprule);
}