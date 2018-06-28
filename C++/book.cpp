//
// Created by 邓岩 on 2018/4/22.
//

# include <cstdlib>
# include <string>
# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>
# include <unistd.h>
# include <fcntl.h>

using namespace std;

class Screen{
    friend class Windou_mgr;//友元类声明
    // friend void Windou_mgr::clear(Windou_mgr::ScreenIndex);
public:
    typedef std::string::size_type pos;
    Screen() = default;
    Screen(pos ht,pos wd,char c): height(ht),width(wd),contents(ht*wd,c){}
    inline char get(pos r,pos c) const;//常量成员函数，this指针由Screen * const类型转换为const Screen * const类型
    char get() const;
    Screen &move(pos r,pos c);
    Screen &set(char);
    Screen &set(pos,pos,char);
    Screen &display(ostream &os) {
        do_display(os);
        return *this;
    }
    const Screen &display(ostream &os) const {//成员函数重载
        do_display(os);
        return *this;
    }
private:
    pos cursor = 0;
    pos height = 0,width = 0;
    string contents;
    void do_display(ostream &os) const {os << contents;}
};

inline Screen &Screen::move(Screen::pos r, Screen::pos c) {//外部定义成员函数
    pos row = r * width;
    cursor += row + c;
    return *this;
}

char Screen::get() const {
    return contents[cursor];
}

char Screen::get(Screen::pos r, Screen::pos c) const {//外部重载成员函数
    pos row = r * width;
    return contents[row+c];
}

Screen &Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}

Screen &Screen::set(Screen::pos r, Screen::pos col, char ch) {
    contents[r*width+col] = ch;
    return *this;
}

class Windou_mgr{
public:
    using ScreenIndex = vector<Screen>::size_type ;
    void clear(ScreenIndex);
    vector<Screen> screens{Screen(24,80,'1')};
};

void Windou_mgr::clear(Windou_mgr::ScreenIndex i) {
    Screen &s = screens[i];
    s.contents = string(s.height*s.width,' ');
}

class Sales_data{
    friend Sales_data add(const Sales_data&,const Sales_data&);//友元函数声明
    friend ostream &print(ostream&,const Sales_data&);
    friend istream &read(istream&,Sales_data&);
public:
    Sales_data(const string &s, unsigned n, double p):bookNo(s),units_sold(n),revenue(p*n) {}//构造函数初始化
    explicit Sales_data(const string &s = "0-11"): Sales_data(s,0,0) {} //委托构造函数，增加explicit关键字，避免隐式转换
    explicit Sales_data(istream&);// 可转换后调用，q.combine(static_cast<Sales_data>(cin));
    string isbn() const {return bookNo;}
    Sales_data &combine (const Sales_data&);
private:
    string bookNo = "0x-111";
    unsigned units_sold = 0;
    double revenue = 0.0;
    double avg_price() const;
};

Sales_data add(const Sales_data&,const Sales_data&);
ostream &print(ostream&,const Sales_data&);
istream &read(istream&,Sales_data&);

Sales_data::Sales_data(istream &is):Sales_data() {
    read(is,*this);
}

double Sales_data::avg_price() const {
    if (units_sold)
        return revenue/units_sold;
    else
        return 0;
}

Sales_data &Sales_data::combine(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

istream &read(istream &is,Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream &print(ostream &os,const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

//7.5.3

void print(const string & a = "123")//以下两个函数当以无参数或一个参数调用时，会报错，有二义性
{
    cout << a << endl;
}

void print(const string & a = "123",const string & b = "234")
{
    cout << a << endl;
    cout << b << endl;
}

int main(void)
{
    string s{"12312321312"};
    istringstream fd("432423432");
    fd.str("31232");
    cout << fd.str() << endl;
}

/*
    int a;
    iostream::badbit;
    Sales_data q("123");
    auto old_state = cin.rdstate();
    //q.combine(static_cast<Sales_data>(cin));// 调用explicit修饰的构造函数
    cout << q.isbn() << endl;
    const Screen s1(6,6,'b');
    Screen s(6,6,'a');
    s.move(4,0).set('#');
    cin.tie(nullptr);
    cout << "dasd";
    cin >> a;
    cout << a;
 */

/*
    Sales_data q("123456");
    cout << q.isbn() << endl;
    q.combine(cin);
    const Screen s1(6,6,'b');
    Screen s(6,6,'a');
    s.move(4,0).set('#');
    Windou_mgr win;
    win.screens[0].display(cout);
    printf("\n");
    win.clear(0);
    win.screens[0].display(cout);
*/