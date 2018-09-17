//
// Created by 邓岩 on 2018/9/9.
//

#ifndef C_CLASS_DY_H
#define C_CLASS_DY_H
//extern int x = 2;

auto arr = [](int x){
    return [&](int y){
        return [&](int z){
            cout << "x " << x << endl;
            cout << "y " << y << endl;
            cout << "z " << z << endl;
            return 1;
        };
    };
};

void read_in(std::vector<double> homework)
{
    int i = 0;
    double count;
    while(i++!=5)
    {
        cin >> count;
        homework.push_back(count);
    }
}


using S1 = Sales_item;
typedef int * pstring;

auto change(int (*p)[5]) -> int (*)[5]
{
    return p;
}

void print(std::string & p)
{
    cout << "this is a quote func" << p <<endl;
}

void print(const std::string & p = "000")
{
    cout << "this is a const quote func" << p << endl;
}

constexpr int cst(int a)
{
    return a;
}

void print(const std::vector<int>& p)
{
    for (auto i : p)
        cout << i <<" ";
    cout << endl;
}

bool isShorter(const std::string &s1,const std::string &s2)
{
    return s1.size() < s2.size();
}

bool check_size(const std::string &s1,int sz)
{
    return s1.size() >= sz;
}

class HasPtr{
    friend void swap(HasPtr &,HasPtr &);
public:
    explicit HasPtr(const std::string & p = ""): s(new std::string(p)) {}
    HasPtr(const HasPtr & T) { s = new std::string(*T.s); }
    HasPtr &operator=(const HasPtr & T) { auto q = new std::string(*T.s); delete s; s = q; return *this; }
    ~HasPtr() { delete s; }
    std::string get() { return *s; }
private:
    std::string * s;
};

inline void swap(HasPtr & l,HasPtr & r)
{
    swap(l.s,r.s);
}

class Folder;

class Message{
    friend class Folder;
public:
    explicit Message(const std::string & str = ""): contents(str) {}
    Message(const Message &);
    Message &operator=(const Message &);
    ~Message();
    void save(Folder & s) { folders.insert(&s); }; // 从给定Folder中添加此Message
    void remove(Folder &); // 从给定Folder中删除此Message
private:
    std::string contents;
    std::set<Folder *> folders;
    void add_to_folders(const Message); //
    void remove_from_folders(); // 从folders中的每个Folder中删除本Message
};

struct absInt
{
    int operator()(int val) const {
        return val<0?-val:val;
    }
};

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book,double sales_price): bookNo(book),price(sales_price) {}
    std::string isbn() const  { return bookNo; };
    virtual double net_price(std::size_t n) const { return n * price; };
    virtual ~Quote() = default;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string & book,double p,std::size_t qty,double disc) : Quote(book,p),quantity(qty),discount(disc) {}
    double net_price(std::size_t) const = 0;
private:
    std::size_t  quantity = 0;
    double discount = 0.0;
};

class Bulk_quote final: public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string & book,double pri,std::size_t qty,double disc) : Disc_quote(book,pri,qty,disc) {}
    double net_price(std::size_t) const override;
};

/*double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= quantity)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}*/

class Base {
public:
    int pub = 1;
    virtual void p() { cout << "Base" << endl; }
protected:
    int pro = 2;
private:
    int pri = 3;
};

class pub_base : public Base {
public:
    void p() { cout << qqq << endl; }
    int pub = 5;
    int print(const pub_base &b)
    {
        return b.pro;
    }
private:
    int qqq = 4;
};

template <typename > class BlobPtr;
template <typename > class Blob;

template <typename T> class Blob {
    template <typename X> friend class BlobPtr;
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    Blob() : data(std::make_shared<std::vector<T>>()) {};
    Blob(std::initializer_list<T> il) : data{std::make_shared<std::vector<T>>(il)} { };
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    T& back();
    T& operator[](size_type t);
private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i,const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blod");
    return data->back();
}

template <typename T>
T& Blob<T>::operator[](size_type t)
{
    check(t,"subscript out of range");
    return (*data)[t];
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0,"pop_back on empty Blob");
    data->pop_back();
}

template <typename T> class BlobPtr {
public:
    BlobPtr(): curr(0) {};
    BlobPtr(Blob<T> &a,size_t sz = 0): wptr(a.data),curr(sz) {}
    T& operator*() const
    {
        auto p = check(curr,"dereference past end");
        return (*p)[curr];
    }
    BlobPtr& operator++();
    BlobPtr& operator--();
private:
    std::shared_ptr<std::vector<T>> check(std::size_t,const std::string &) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};

template<typename T> using twin = std::pair<T,T>;

class Wiget {
private:
    enum { Win,Sat };
    static const int num = 5;
public:
    void print()
    {
        cout << Win << endl;
    }
};

//const int Wiget::num;

template <typename type,int dim>
class Point1 {
public:
    Point1();
    Point1(type * coords)
    {
        for (int i = 0; i < dim; ++i) {
            _coords[i] = coords[i];
        }
    }
    void print()
    {
        cout << dim << endl;
    }
private:
    type _coords[dim];
};

class W {
public:
    char s;
    int w;
};

class A {
public:
    //A(char a = 65) : x(a) {}
    virtual void o() = 0;
    virtual void o() const = 0;
    virtual void f() { cout << "x = " << x << endl; }
    void h() { cout << "h()" << endl; }
protected:
    A(char a = 66,char b = 54) : x(a) {};
    char x;
};

class B : public A{
public:
    void o() { cout << "o()" << endl; }
    virtual void g() { cout << "g()" << endl; }
    void f() override { cout << x << endl; A::f(); }
    char y = 3;
};

class C : public A, public B {
public:
    virtual void q() { cout << "q()" << endl; }
    char z;
};

class Point {
public:
    Point(float x = 0.0, float y = 0.0) : _x(x),_y(y) { cout << "constructor" << endl;};
    Point(const Point &rhs)
    {
        _x = rhs._x;
        _y = rhs._y;
    }
    ~Point() { cout << "Point object destroy" << endl; }
protected:
    float _x;
    float _y;
};

class Point3D : virtual public Point {
public:
    Point3D(float x = 0.0,float y = 0.0,float z = 0.0) : Point(x,y),_z(z) {}
    Point3D &operator=(const Point3D &rhs)
    {
        this->Point::operator=(rhs);
        _z = rhs._z;
        return *this;
    }
    ~Point3D() { cout << "Point3D object destroy" << endl; }
protected:
    float _z;
};


#endif //C_CLASS_DY_H
