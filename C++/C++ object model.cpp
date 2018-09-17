//
// Created by 邓岩 on 2018/8/14.
//

# include <iostream>
# include <string>
# include <memory>
# include <vector>
# include <list>
# include <algorithm>
# include <numeric>
# include <iomanip>
# include "Sales_item.h"
# include <unistd.h>
# include <sstream>
# include <fstream>
# include <array>
# include <forward_list>
# include <stack>
# include <queue>
# include <functional>
# include <map>
# include <unordered_map>
# include <set>
# include <unordered_set>
# include <utility>
# include <functional>


using std::cin;
using std::cout;
using std::endl;

class B {
public:
    //B() = default;
    int a;
    B(int x)
    {
        a = x;
        cout << a << endl;
    }
    B(B &lhr)
    {
        cout << "copy contructor" << endl;
    }
    B &operator=(B &lhr) {
        cout << "copy assignment" << endl;
        return *this;
    }
};

class A
{
public:
    int a;
    B b;
    static int c;
    A() : b(5){
        cout << "A constructor" << endl;
    };
    A(A &lhr) : b(lhr.b)//我猜测对于类中有其他类对象的类类型，其合成的拷贝构造函数应该是这样，将此函数去掉对程序没有影响
    {
        a = lhr.a;
    }
};


class X {};
class Y : public virtual X {};
class Z : public virtual X {};
class W : public Y,public Z {};

int main() {//1®6.1.5
    A a;
}

/*
 * 所谓合成，就是在已有的默认构造函数上进行一些必要的拓展
 * 首先最重要的一点，如果类中没有其他类类型(或者有其他类类型，但该类类型也没有默认构造函数)，虚函数，虚继承，那么该类可当作C语言结构体看待，他没有任何构造函数
 * 如果类A中有其他类类型B(前提是B有构造函数)，那么如果没有显式对他进行初始化，此时A就会合成一个构造函数，该构造函数中会调用B的构造函数，如果B没有构造函数，那么A不会生成合成的构造函数
 * 如果基类有任何的构造函数，那么其衍生类一定会有构造函数，如果没有现实定义，会由编译器合成一个用来调用其父类的构造函数
 * 在拷贝构造函数中，如果类中没有其他类类型以及没有虚函数也没有虚继承，那么他合成的拷贝构造构造函数是按位拷贝的，否则他是按成员拷贝的
 * 对于合成的拷贝构造函数，如果该类中有其他类成员，且其他类成员有拷贝构造函数，他会调用其他类成员的拷贝构造函数，或者其继承的基类有拷贝构造函数，那么他也会有
 * 对于一个类实例，他的内存结构包括成员对象和虚函数表指针，每一个类类型只有一个虚函数表，即虚函数表是共享的
 * 如果子类的默认构造函数是删除的，那么派生类合成的默认构造函数也是删除的
 */