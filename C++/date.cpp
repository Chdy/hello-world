//
// Created by 邓岩 on 2019/4/12.
//

# include <iostream>
# include <ctime>
# include <string>
# include <vector>

using namespace std;

vector<string> trans = {"January","February","March","April","May","June","July","August","September","October","November","December"};

class Date{
public:
    Date() {
        t = time(nullptr);
    }
    Date(int tt) {
        t = tt;
    }
    void print() {
        ti = localtime(&t);
        cout << ti->tm_mon + 1 << "-" << ti->tm_mday << "-" << ti->tm_year + 1900 << endl;
    }
    time_t t;
    tm * ti;
};

class ShortE : public Date {
public:
    ShortE() = default;
    ShortE(int tt) : Date(tt) {
    }
    void print() {
        ti = localtime(&t);
        cout << ti->tm_mday << "-" << ti->tm_mon + 1 << "-" << ti->tm_year + 1900 << endl;
    }
};

class MediumDate : public Date {
public:
    MediumDate() = default;
    MediumDate(int tt) : Date(tt) {
    }
    void print() {
        ti = localtime(&t);
        cout << trans[ti->tm_mon].substr(0, 3) << "." << ti->tm_mday << "," << ti->tm_year + 1900 << endl;
    }
};

class LongDate : public Date {
public:
    LongDate() = default;
    LongDate(int tt) : Date(tt) {
    }
    void print() {
        ti = localtime(&t);
        cout << trans[ti->tm_mon] << " " << ti->tm_mday << "," << ti->tm_year + 1900 << endl;
    }
};

int main(void)
{
    ShortE b(11211122);
    Date a(123223);
    MediumDate c(434324);
    LongDate d;
    a.print();
    b.print();
    c.print();
    d.print();
    return 0;
}