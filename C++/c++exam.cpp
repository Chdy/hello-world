//
// Created by 邓岩 on 2019/2/28.
//

# include <iostream>
# include <string>
# include <sstream>
# include <iomanip>
# include <algorithm>
# include <vector>
# include <stdio.h>

using namespace std;

class teacher {
public:
    static int uid;
    double salary;
    double add;
    int time;
    int id;
    virtual void info () {};
};

int teacher:: uid = 1;

class professor : public teacher {
public:
    professor() = default;
    professor(int t)  {
        id = uid++;
        add = 50;
        salary = 5000;
        time = t;
    }
    virtual void info () {  cout << "professor id = " << id << " wage = " << salary + add * time << endl; };
};

class assprofessor : public teacher {
public:
    assprofessor() = default;
    assprofessor(int t) {
        id = uid++;
        add = 30;
        salary = 3000;
        time = t;
    }
    virtual void info () {  cout << "assprofessor id = " << id << " wage = " << salary + add * time << endl; };
};

class lecturer : public teacher {
public:
    lecturer() = default;
    lecturer(int t) {
        id = uid++;
        add = 20;
        salary = 2000;
        time = t;
    }
    virtual void info () {  cout << "lecturer id = " << id << " wage = " << salary + add * time << endl; };
};

int main(void) {
    teacher * a = new lecturer(10);
    teacher * b = new assprofessor(10);
    teacher * c = new professor(10);
    a->info();
    b->info();
    c->info();
}

/*
class StudentManger;

class Student {
public:
    int no;         //学生的学号
    string name;    //学生的姓名
    float score;   //学生的成绩
    Student* per;   //当前结点的前一个结点指针
    Student* next;  //下一个结点指针
};

class StudentManger //类的定义
{
private:
    Student * head;
public:
    StudentManger();                       //构造函数
    Student* find(int i_no);                   //查找指定学号的学生
    void edit(Student * , string i_newname,float i_score); //修改学生的信息
    void erase(Student *);                               //删除指定学号的学生
    int add(Student* i_newStudent);           //增加学生
    int getno(Student *);                                //获得学生的学号
    string getname(Student *);                           //获得学生的名字
    float getscore(Student *);                          //获得学生的成绩
    static int maxno;
};

StudentManger::StudentManger()
{
    head = new Student();
    head->next = NULL;
}
Student* StudentManger::find(int i_no)
{
    Student * t = head->next;
    while (t != NULL) {
        if (t->no == i_no)
            return t;
        t = t->next;
    }
    return NULL;
}

void StudentManger::edit(Student * t, string i_name,float i_score)
{
    if(i_name=="")
        return ;
    t->name=i_name;
    t->score=i_score;
}
void StudentManger::erase(Student * t)
{
    if(t->no<0)
        return ;
    if(t->per!=NULL)
        t->per->next=t->next;
    if(t->next!=NULL)
        t->next->per=t->per;
    t->next=NULL;
    t->per=NULL;
}
int StudentManger::add(Student* i_newStudent)
{
    int no=maxno+1;
    while(true)
    {
        if(NULL==find(no))
            break;
        no=no+1;
    }
    Student * tmp = head;
    while(true){
        if(tmp->next==NULL)
            break;
        tmp=tmp->next;
    }
    tmp->next=i_newStudent;
    i_newStudent->next=NULL;
    i_newStudent->per=tmp;
    i_newStudent->no=no;
    return no;
}

int StudentManger::getno(Student * t){return t->no;}
string StudentManger::getname(Student * t){return t->name;}
float StudentManger::getscore(Student * t){return t->score;}
int StudentManger::maxno=1000;
int main()
{
    StudentManger * Studentroot=new StudentManger();
    string input1;
    float input2;
    Student* tmp=NULL;
    while(true){
        cout<<"输入指令：查找(F),增加(A),编辑(E),删除(D),退出(Q)"<<endl;
        cin>>input1;
        if(("F"==input1)||("f"==input1))
        {
            cout<<"输入学号:";
            int no=-1;
            cin>>no;
            tmp=Studentroot->find(no);
            if(tmp==NULL)
            {
                cout<<"没找到"<<endl;
                continue;
            }
            cout<<"学号:"<<Studentroot->getno(tmp);
            cout<<"  姓名:";
            string name;
            if((name=Studentroot->getname(tmp))!="")
                cout<<name;
            else
                cout<<"未输入"<<endl;
            cout<<" 成绩："<<Studentroot->getscore(tmp)<<endl;
        }
        else if((input1=="A")||(input1=="a"))
        {
            cout<<"输入姓名，成绩: ";
            cin>>input1>>input2;;
            tmp=new Student();
            Studentroot->edit(tmp, input1,input2);
            cout<<"学号: "<<Studentroot->add(tmp)<<endl;
        }
        else if((input1=="E")||(input1=="e"))
        {
            cout<<"输入学号:";
            int no=0;
            cin>>no;
            tmp=Studentroot->find(no);
            if(tmp==NULL)
            {
                cout<<"空号"<<endl;
                continue;
            }
            cout<<"新姓名,新成绩: ";
            cin>>input1>>input2;
            Studentroot->edit(tmp, input1, input2);
            cout<<"更改成功."<<endl;
        }
        else if((input1=="D")||(input1=="d"))
        {
            cout<<"输入学号:";
            int no=0;
            cin>>no;
            tmp=Studentroot->find(no);
            Studentroot->erase(tmp);
            cout<<"已成功删除"<<endl;
            delete tmp;
        }
        else if((input1=="Q")||(input1=="q"))
        {
            break;
        }
        else
        {
            cout<<"输入有误！"<<endl;
        }
    }
    delete Studentroot;
    return 0;
}
 */

/*
class Circle {
public:
    Circle () = default;
    Circle(double radius) {
        this->radius = radius;
    }
    double area() {
        return 3.1415 * radius * radius;
    }
    void set(double x) {
        radius = x;
    }
    double get() {
        return radius;
    }

private:
    double radius;
};

class stack {
private:
    int * a;
    int index;
    int len;
public:
    stack() = default;
    ~stack() { free(a); }
    stack(int n) {
        a = (int *)malloc(sizeof(int) * n);
        len = n;
        index = 0;
    }
    void push(int x) {
        if (full()) {
            a = (int *)realloc(a, sizeof(int) * len * 2);
            len = 2 * len;
        }
        a[index++] = x;
    }
    int pop() {
        if (empty()) {
            cout << "The stack is empty" << endl;
            exit(-1);
        }
        return a[--index];
    }
    bool empty() { return index == 0; }
    bool full() { return index == len; }
};
 */

/*
struct twodim {
    int r;
    int c;
    float * a;
};

void get_twodim(twodim &s, int row, int col) {
    s.r = row;
    s.c = col;
    s.a = new float[row * col];
}

float &val(twodim &s, int i, int j ) {
    return s.a[i * s.c + j];
}

void free_twodim(twodim &s) {
    delete [] s.a;
}

int main(void) {//16.1.5
    struct twodim s;
    int i, j;
    get_twodim(s, 3, 4);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++)
            val(s, i, j) = 5;
    }

    for (i = 0;i < 3; i++) {
        for (j = 0; j < 4; j++)
            cout << setw(5) << val(s, i, j);
        cout << endl;
    }

    free_twodim(s);
    return 0;
}
 */

/*
void print(string &s, int n = 10)
{
    cout << string(s.begin(), s.begin() + min(int(s.size()), n)) << endl;
}
*/

/*
    string s;
    vector<string> buf;
    getline(cin, s);
    istringstream str(s);
    copy(istream_iterator<string>(str), istream_iterator<string>(), back_inserter(buf));
    sort(buf.begin(), buf.end());
    copy(buf.begin(), buf.end(), ostream_iterator<string>(cout, " "));
 */

// 输若干数据，找出最大值输出

/*
# include <iostream>
# include <string>
# include <sstream>
# include <algorithm>

using namespace std;

int main(void) {
    string s;
    getline(cin, s);
    istringstream str(s);
    cout << *max_element(istream_iterator<int>(str), istream_iterator<int>()) << endl;
    return 0;[
}
 */

/*
# include <iostream>
# include <string>
# include <iomanip>

using namespace std;

int main() {//16.1.5
    int day, stop, i = 0;
    cin >> day >> stop;
    cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
    cout << string(day * 5, ' ');
    while (stop--) {
        cout << setw(5) << ++i;
        if ((day + i) % 7 == 0)
            cout << endl;
    }
    return 0;
}
 */