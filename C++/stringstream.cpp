//
// Created by 邓岩 on 2018/4/26.
//

/*
 istreamstring的用法
 输入形式：
 dengyan 1388 321321
 huwangfei 312431 8908
 rongti dsas fasd
 以两下会车结束
 总的来说:
 istringstream类似sscanf
 ostringstream类似sprintf
 */

struct Person{
    string name;
    vector<string> phones;
};

int valid(const string &c)
{
    for (auto i : c)
        if(!isdigit(i))
            return 0;
    return 1;
}

int main() {//6.4.1
    string line,word;
    vector<Person> people;
    //ifstream fd("/Users/dengyan/exam");加上这行并将下行的cin改为fd可从文件读取
    while(getline(cin,line))
    {
        if(line == string(""))
            break;
        Person info;
        istringstream record(line);
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }
    for (const auto &c : people)
    {
        ostringstream formatted,badnums;
        for(const auto &num : c.phones){
            if(!valid(num))
                badnums << " " << num;
            else
                formatted << " " << num;
        }
        if(badnums.str().empty())
            cout << c.name << formatted.str() << endl;
        else
            cerr << "Input error: " << c.name << " invalid number(s) " << badnums.str() << endl;
    }
    return 0;
}