//
// Created by 邓岩 on 2019/6/11.
//

/*
 * 1、问题描述
	学生信息包括：学号、姓名、性别、年龄、班级等信息
	小学生除了包括学生所有信息外，还包括英语、数学和语文成绩。
	中学生除了包括小学生所有信息外，还包括地理、历史成绩。
	大学生除了包括学生所有信息外，还包括专业、英语、程序设计和高等数学等课程。
	设计一个程序能够对学生成绩进行管理，应用到继承、抽象类、虚函数、虚基类、多态和文件的输入/输出等内容。

2、功能要求
	（1）添加功能：程序能够添加不同学生的记录，提供选择界面供用户选择所要添加的类别，要求学号要唯一，如果添加了重复学号的记录时，则提示数据添加重复并取消添加。
	（2）查询功能：可根据学号、姓名等信息对已添加的学生记录进行查询，如果未找到，给出相应的提示信息，如果找到，则显示相应的记录信息。
	（3）显示功能：可显示当前系统中所有学生的记录，每条记录占据一行。
	（4）编辑功能：可根据查询结果对相应的记录进行修改，修改时注意学号的唯一性。
	（5）删除功能：主要实现对已添加的学生记录进行删除。如果当前系统中没有相应的记录，则提示“记录为空！”并返回操作。
	（6）统计功能：能根据多种参数进行统计。能统计学生人数、总分、单科的平均分等。
	（7）保存功能：可将当前系统中国各类记录存入文件中，存入方式任意。
	（8）读取功能：可将保存在文件中的信息读入到当前系统中，供用户进行使用。
	（9）排序功能：可按总分和单科成绩排名次。
 */

# include <algorithm>
# include <iostream>
# include <string>
# include <vector>
# include <unistd.h>
# include <fcntl.h>
#include <map>
#include <numeric>
# include <iomanip>

using namespace std;


class Student {
public:
    Student() = default;
    Student(string id, string name, string sex, int age, string cls) {
        this->id =  id;
        this->name =  name;
        this->sex =  sex;
        this->age = age;
        this->cls = cls;
    }
    string id;
    string name;
    string sex;
    int age;
    int kind;
    string cls;
    virtual void print() {};
    virtual double score() { return 0; };
};

class pupil : public Student {
public:
    pupil() { kind = 1; };
    pupil(string id, string name, string sex, int age, string cls, double math, double english, double chinese){
        Student(id, name, sex, age, cls);
        kind = 1;
        this->math = math;
        this->english = english;
        this->chinese = chinese;

    }
    double math;
    double english;
    double chinese;
    virtual void print() override {
        printf("%3s %s %2s %d %s %5.2lf %5.2lf %5.2lf\n", id.c_str(),  name.c_str(),  sex.c_str(), age ,  cls.c_str(),  english,  math, chinese);
    }
    virtual double score() override { return math + english + chinese; };

};

class middle : public pupil {
public:
    middle() { kind = 2; }
    middle(string id, string name, string sex, int age, string cls, double math, double english, double chinese, double geoge, double history){
        pupil(id, name, sex, age, cls, math, english, chinese);
        this->geoge = geoge;
        this->history = history;
    }
    virtual void print() override {
        printf("%3s %s %2s %d %s %5.2lf %5.2lf %5.2lf %5.2lf %5.2lf\n", id.c_str(),  name.c_str(),  sex.c_str(), age, cls.c_str(), english,  math, chinese, geoge, history);
    }
    virtual double score() override { return math + english + chinese + geoge + history; };
    double geoge;
    double history;
};

class university : public middle {
public:
    university() { kind = 3; }
    university(string id, string name, string sex, int age, string cls, double math, double english, double chinese, double geoge, double history, double sp, double program, double calculus){
        middle(id, name, sex, age, cls, math, english, chinese, geoge, history);
        this->sp = sp;
        this->program = program;
        this->calculus = calculus;
    }
    virtual void print() override {
        printf("%3s %s %2s %d %s %5.2lf %5.2lf %5.2lf %5.2lf %5.2lf %5.2lf %5.2lf %5.2lf\n", id.c_str(),  name.c_str(),  sex.c_str(), age, cls.c_str(), english,  math, chinese, geoge, history, sp, program, calculus);
    }
    virtual double score() override { return math + english + chinese + geoge + history + sp + program + calculus; };
    double sp;
    double program;
    double calculus;
};

class StudentControl {
public:
    map<string, Student *> id;
    map<string, vector<Student *> > name;

    map<string, pupil *> p;
    map<string, middle *> m;
    map<string, university *> u;

    void add() {
        cout << "---------------------添加信息---------------------" << endl;
        cout << "请选择添加的学生类型: " << endl;
        cout << "\t1. 小学生" << endl;
        cout << "\t2. 中学生" << endl;
        cout << "\t3. 大学生" << endl;

        int c;
        cin >> c;
        switch (c) {
            case 1: {
                pupil * p1 = new pupil();
                cout << "请输入学号、姓名、性别、年龄、班级、英语、数学、语文成绩" << endl;
                cin >> p1->id >> p1->name >> p1->sex >> p1->age >> p1->cls \
                    >> p1->english >> p1->math >> p1->chinese;
                if (!id.count(p1->id)) {
                    id[p1->id] = p1;
                    name[p1->name].push_back(p1);
                    p[p1->id] = p1;
                    cout << "添加成功" << endl;
                } else {
                    delete(p1);
                    cout << "学号已经存在，请重试" << endl;
                }
                break;
            }
            case 2: {
                middle * p2 = new middle();
                cout << "请输入学号、姓名、性别、年龄、班级、英语、数学、语文、地理、历史成绩" << endl;
                cin >> p2->id >> p2->name >> p2->sex >> p2->age >> p2->cls \
                    >> p2->english >> p2->chinese >> p2->math >> p2->geoge >> p2->history;
                if (!id.count(p2->id)) {
                    id[p2->id] = p2;
                    name[p2->name].push_back(p2);
                    m[p2->id] = p2;
                    cout << "添加成功" << endl;
                } else {
                    delete(p2);
                    cout << "学号已经存在，请重试" << endl;
                }
                break;
            }
            case 3: {
                university * p3 = new university();
                cout << "请输入学号、姓名、性别、年龄、班级、英语、数学、语文、地理、历史、专业、程序设计和高等数学成绩" << endl;
                cin >> p3->id >> p3->name >> p3->sex >> p3->age >> p3->cls \
                     >> p3->english >> p3->math >> p3->chinese >> p3->geoge >> p3->history
                     >> p3->sp >> p3->program >> p3->calculus;
                if (!id.count(p3->id)) {
                    id[p3->id] = p3;
                    name[p3->name].push_back(p3);
                    u[p3->id] = p3;
                    cout << "添加成功" << endl;
                } else {
                    delete(p3);
                    cout << "学号已经存在，请重试" << endl;
                }
                break;
            }
        }
        cout << "-----------------------END-----------------------" << endl;
    }

    void show() {
        cout << "---------------------显示信息---------------------" << endl;
        if (!p.empty()) {
            cout << "|---------------------小学生--------------------" << endl;

            for (auto i : p) {
                cout << "|";
                i.second->print();
            }
        }
        if (!m.empty()) {
            cout << "|---------------------中学生--------------------" << endl;
            for (auto i : m) {
                cout << "|";
                i.second->print();
            }
        }
        if (!u.empty()) {
            cout << "|---------------------大学生--------------------" << endl;
            for (auto i : u) {
                cout << "|";
                i.second->print();
            }
        }
        cout << "-----------------------END-----------------------" << endl;
    }

    Student * query() {
        cout << "---------------------查询信息---------------------" << endl;
        int c;
        cout << "\t1. 按学号查询" << endl;
        cout << "\t2. 按姓名查询" << endl;

        cin >> c;
        switch (c) {
            case 1: {
                cout << "请输入学号: " << endl;
                string idd;
                cin >> idd;
                if (id.count(idd)) {
                    cout << "|", id[idd]->print();
                    return id[idd];
                } else {
                    cout << "未找到相关信息" << endl;
                }
                break;
            }
            case 2: {
                cout << "请输入姓名: " << endl;
                string namee;
                cin >> namee;
                if (name.count(namee)) {
                    for (auto i : name[namee])
                        cout << "|", i->print();
                } else {
                    cout << "未找到相关信息" << endl;
                }
            }
        }
        cout << "-----------------------END-----------------------" << endl;
        return 0;
    }

    void del() {
        cout << "---------------------删除信息---------------------" << endl;
        string idd;
        cout << "请输入学号: " << endl;
        cin >> idd;

        if (id.count(idd)) {
            auto &v = name[id[idd]->name]; //首先删除name红黑树中的数据
            v.erase(find_if(v.begin(), v.end(), [&] (Student * x) { return x->id == idd; }));
            if (!name[id[idd]->name].empty())
                name.erase(id[idd]->name);

            switch (id[idd]->kind) {
                case 1:
                    p.erase(idd);
                    break;
                case 2:
                    m.erase(idd);
                    break;
                case 3:
                    u.erase(idd);
                    break;
            }
            delete(id[idd]);
            id.erase(idd);
            cout << "删除成功" << endl;

        } else {
            cout << "记录为空" << endl;
        }

        cout << "-----------------------END-----------------------" << endl;
    }

    void edit() {
        cout << "---------------------编辑信息---------------------" << endl;
        Student * x = query();
        cout << "以上为查询到的信息，注意只有按照学号查询才可修改" << endl;
        if (x == NULL) {
            cout << "\t请使用学号查询" << endl;
        } else {
            cout << "待完成，请先删除数据后添加数据" << endl;
        }
        cout << "-----------------------END-----------------------" << endl;
    }

    void statistic() {
        cout << "---------------------统计信息---------------------" << endl;
        cout << fixed << setprecision(2) << "\t\t人数\t英语\t数学\t语文\t地理\t历史\t专业\t程序\t高数" << endl;
        if (!p.empty())
            cout << "小学生     " << p.size() << " "
                    << accumulate(p.begin(), p.end(), 1.0 , [] (double a, pair<string, pupil *> b) { return a + b.second->english; }) / p.size() << " "
                    << accumulate(p.begin(), p.end(), 1.0 , [] (double a, pair<string, pupil *> b) { return a + b.second->math; }) / p.size() << " "
                    << accumulate(p.begin(), p.end(), 1.0 , [] (double a, pair<string, pupil *> b) { return a + b.second->chinese; }) / p.size() << endl;
        if (!m.empty())
            cout << "中学生     " << m.size() << " "
                    << accumulate(m.begin(), m.end(), 1.0 , [] (double a, pair<string, middle *> b) { return a + b.second->english; }) / m.size() << " "
                    << accumulate(m.begin(), m.end(), 1.0 , [] (double a, pair<string, middle *> b) { return a + b.second->math; }) / m.size() << " "
                    << accumulate(m.begin(), m.end(), 1.0 , [] (double a, pair<string, middle *> b) { return a + b.second->chinese; }) / m.size() << " "
                    << accumulate(m.begin(), m.end(), 1.0 , [] (double a, pair<string, middle *> b) { return a + b.second->geoge; }) / m.size() << " "
                    << accumulate(m.begin(), m.end(), 1.0 , [] (double a, pair<string, middle *> b) { return a + b.second->history; }) / m.size() << endl;
        if (!u.empty())
            cout << "大学生     " << u.size() << " "
                << accumulate(u.begin(), u.end(), 1.0 , [] (double a, pair<string, university *> b) { return a + b.second->english; }) / u.size() << " "
                << accumulate(u.begin(), u.end(), 1.0 , [] (double a, pair<string, university *> b) { return a + b.second->math; }) / u.size() << " "
                << accumulate(u.begin(), u.end(), 1.0 , [] (double a, pair<string, university *> b) { return a + b.second->chinese; }) / u.size() << " "
                << accumulate(u.begin(), u.end(), 1.0 , [] (double a, pair<string, university *> b) { return a + b.second->chinese; }) / u.size() << " "
                << accumulate(u.begin(), u.end(), 1.0 , [] (double a, pair<string, university *> b) { return a + b.second->geoge; }) / u.size() << " "
                << accumulate(u.begin(), u.end(), 1.0 , [] (double a, pair<string, university *> b) { return a + b.second->history; }) / u.size() << " "
                << accumulate(u.begin(), u.end(), 1.0 , [] (double a, pair<string, university *> b) { return a + b.second->sp; }) / u.size() << " "
                << accumulate(u.begin(), u.end(), 1.0 , [] (double a, pair<string, university *> b) { return a + b.second->program; }) / u.size() << " "
                << accumulate(u.begin(), u.end(), 1.0 , [] (double a, pair<string, university *> b) { return a + b.second->calculus; }) / u.size() << " "
                << accumulate(u.begin(), u.end(), 1.0 , [] (double a, pair<string, university *> b) { return a + b.second->english; }) / u.size() << endl;
        cout << "-----------------------END-----------------------" << endl;
    }

    void save() {
        if (id.empty()) {
            cout << "当前数据集为空，继续操作将清空本地数据库，是否确认(y/n)" << endl;
            char a;
            cin >> a;
            if (a != 'y' && a != 'Y')
                return;
        }
        int fd = open("/Users/dengyan/info.dat", O_WRONLY|O_CREAT|O_TRUNC, 0744);
        if (fd == -1) {
            cout << strerror(errno) << endl;
            return;
        }

        int out = dup(STDOUT_FILENO); //先复制标准输出描述符，防止关闭
        dup2(fd, STDOUT_FILENO);

        cout << id.size() << endl;
        for (auto i : id)
            cout << i.second->kind << " ", i.second->print();

        dup2(out, STDOUT_FILENO);
        close(fd);
        close(out);

        cout << "---------------------保存成功---------------------" << endl;
    }

    void read() {
        int n;
        int fd = open("/Users/dengyan/info.dat", O_RDONLY);
        if (fd == -1) {
            cout << "数据文件不存在" << endl;
            return;
        }
        int in = dup(STDIN_FILENO);
        dup2(fd, STDIN_FILENO); //将标准输入重定向到文件

        int fd2 = open("/dev/null", O_WRONLY); //丢弃垃圾信息
        int out = dup(STDOUT_FILENO);
        dup2(fd2, STDOUT_FILENO);

        cin >> n;
        while (n--) {
            add();
        }

        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);

        close(fd);
        close(fd2);
        close(in);

        cout << "---------------------读取成功---------------------" << endl;
    };

    void sorted() {
        cout << "---------------------排序信息---------------------" << endl;
        cout << "请选择排序方式" << endl;
        cout << "1. 总分排名" << endl;
        cout << "2. 英语排名" << endl;
        cout << "3. 数学排名" << endl;
        cout << "4. 语文排名" << endl;
        cout << "5. 地理排名" << endl;
        cout << "6. 历史排名" << endl;
        cout << "7. 专业排名" << endl;
        cout << "8. 程序排名" << endl;
        cout << "9. 高数排名" << endl;


        int c;
        cin >> c;

        vector<pupil *> pv;
        for (auto i : p)
            pv.push_back(i.second);

        vector<middle *> mv;
        for (auto i : m)
            mv.push_back(i.second);

        vector<university *> uv;
        for (auto i : u)
            uv.push_back(i.second);

        switch (c) {
            case 1: {
                cout << "|---------------------小学生--------------------" << endl;
                sort(pv.begin(), pv.end(), [] (pupil * a, pupil * b) { return a->score() > b->score(); });
                int j = 1;
                for (auto i : pv)
                    cout << "| " << j << ". ", i->print(), j++;

                cout << "|---------------------中学生--------------------" << endl;
                sort(mv.begin(), mv.end(), [] (middle * a, middle * b) { return a->score() > b->score(); });
                j = 1;
                for (auto i : mv)
                    cout << "| " << j << ". ", i->print(), j++;

                cout << "|---------------------大学生--------------------" << endl;
                sort(uv.begin(), uv.end(), [] (university * a, university * b) { return a->score() > b->score(); });
                j = 1;
                for (auto i : uv)
                    cout << "| " << j << ". ", i->print(), j++;
                break;
            }
            case 2: {
                cout << "|---------------------小学生--------------------" << endl;
                sort(pv.begin(), pv.end(), [] (pupil * a, pupil * b) { return a->english > b->english; });
                int j = 1;
                for (auto i : pv)
                    cout << "| " << j << ". ", i->print(), j++;

                cout << "|---------------------中学生--------------------" << endl;
                sort(mv.begin(), mv.end(), [] (middle * a, middle * b) { return a->english > b->english; });
                j = 1;
                for (auto i : mv)
                    cout << "| " << j << ". ", i->print(), j++;

                cout << "|---------------------大学生--------------------" << endl;
                sort(uv.begin(), uv.end(), [] (university * a, university * b) { return a->english > b->english; });
                j = 1;
                for (auto i : uv)
                    cout << "| " << j << ". ", i->print(), j++;
                break;
            }
            case 3: {
                cout << "|---------------------小学生--------------------" << endl;
                sort(pv.begin(), pv.end(), [] (pupil * a, pupil * b) { return a->math > b->math; });
                int j = 1;
                for (auto i : pv)
                    cout << "| " << j << ". ", i->print(), j++;

                cout << "|---------------------中学生--------------------" << endl;
                sort(mv.begin(), mv.end(), [] (middle * a, middle * b) { return a->math > b->math; });
                j = 1;
                for (auto i : mv)
                    cout << "| " << j << ". ", i->print(), j++;

                cout << "|---------------------大学生--------------------" << endl;
                sort(uv.begin(), uv.end(), [] (university * a, university * b) { return a->math > b->math; });
                j = 1;
                for (auto i : uv)
                    cout << "| " << j << ". ", i->print(), j++;
                break;
            }
            case 4: {
                cout << "|---------------------小学生--------------------" << endl;
                sort(pv.begin(), pv.end(), [] (pupil * a, pupil * b) { return a->chinese > b->chinese; });
                int j = 1;
                for (auto i : pv)
                    cout << "| " << j << ". ", i->print(), j++;

                cout << "|---------------------中学生--------------------" << endl;
                sort(mv.begin(), mv.end(), [] (middle * a, middle * b) { return a->chinese > b->chinese; });
                j = 1;
                for (auto i : mv)
                    cout << "| " << j << ". ", i->print(), j++;

                cout << "|---------------------大学生--------------------" << endl;
                sort(uv.begin(), uv.end(), [] (university * a, university * b) { return a->chinese > b->chinese; });
                j = 1;
                for (auto i : uv)
                    cout << "| " << j << ". ", i->print(), j++;
                break;
            }
            case 5: {
                int j = 1;
                cout << "|---------------------中学生--------------------" << endl;
                sort(mv.begin(), mv.end(), [] (middle * a, middle * b) { return a->geoge > b->geoge; });
                j = 1;
                for (auto i : mv)
                    cout << "| " << j << ". ", i->print(), j++;

                cout << "|---------------------大学生--------------------" << endl;
                sort(uv.begin(), uv.end(), [] (university * a, university * b) { return a->geoge > b->geoge; });
                j = 1;
                for (auto i : uv)
                    cout << "| " << j << ". ", i->print(), j++;
                break;
            }
            case 6: {
                int j = 1;
                cout << "|---------------------中学生--------------------" << endl;
                sort(mv.begin(), mv.end(), [] (middle * a, middle * b) { return a->history > b->history; });
                j = 1;
                for (auto i : mv)
                    cout << "| " << j << ". ", i->print(), j++;

                cout << "|---------------------大学生--------------------" << endl;
                sort(uv.begin(), uv.end(), [] (university * a, university * b) { return a->history > b->history; });
                j = 1;
                for (auto i : uv)
                    cout << "| " << j << ". ", i->print(), j++;
                break;
            }case 7: {
                int j = 1;
                cout << "|---------------------大学生--------------------" << endl;
                sort(uv.begin(), uv.end(), [] (university * a, university * b) { return a->sp > b->sp; });
                for (auto i : uv)
                    cout << "| " << j << ". ", i->print(), j++;
            }
            case 8: {
                int j = 1;
                cout << "|---------------------大学生--------------------" << endl;
                sort(uv.begin(), uv.end(), [] (university * a, university * b) { return a->program > b->program; });
                for (auto i : uv)
                    cout << "| " << j << ". ", i->print(), j++;
                break;
            }
            case 9: {
                int j = 1;
                cout << "|---------------------大学生--------------------" << endl;
                sort(uv.begin(), uv.end(), [] (university * a, university * b) { return a->calculus > b->calculus; });
                for (auto i : uv)
                    cout << "| " << j << ". ", i->print(), j++;
                break;
            }
        }
        cout << "-----------------------END-----------------------" << endl;
    }


};


int main() {
    int c;
    StudentControl core;
    while (1) {
        cout << "--------------------学生管理系统--------------------" << endl;
        cout << "|                   1. 显示信息                    |" << endl;
        cout << "|                   2. 添加信息                    |" << endl;
        cout << "|                   3. 查询信息                    |" << endl;
        cout << "|                   4. 删除信息                    |" << endl;
        cout << "|                   5. 编辑信息                    |" << endl;
        cout << "|                   6. 统计信息                    |" << endl;
        cout << "|                   7. 保存信息                    |" << endl;
        cout << "|                   8. 读取信息                    |" << endl;
        cout << "|                   9. 排序信息                    |" << endl;
        cout << "|                   0. 退出程序                    |" << endl;
        cout << "------------------------END-----------------------" << endl;
        cin >> c;
        switch (c) {
            case 0:
                return 0;
            case 1:
                core.show();
                break;
            case 2:
                core.add();
                break;
            case 3:
                core.query();
                break;
            case 4:
                core.del();
                break;
            case 5:
                core.edit();
                break;
            case 6:
                core.statistic();
                break;
            case 7:
                core.save();
                break;
            case 8:
                core.read();
                break;
            case 9:
                core.sorted();
                break;
        }
     }

    return 0;
}