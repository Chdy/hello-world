# include <iostream>
# include <cstdlib>
# include <cstdio>
# include <string>
# include <vector>
# include <fstream>
# include <forward_list>
# include <list>
# include <deque>
# include <array>

using namespace std;

void swap(int,int);

class Sale_datas{
public:
    Sale_datas() = default;
    Sale_datas(int c):a(c){};
    int b;
    void r()
    {
        cout << this->a << endl;
    };
private:
    int a;
};

int main() {
    int x = 3;
    int y = 4;
    x -= y + 5;
    cout << x << endl;
}

void swap(int & a,int & b)
{
    int t = a;
    a = b;
    b = t;
}
