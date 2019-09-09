//
// Created by 邓岩 on 2018/7/9.
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
# include "/usr/local/mysql-5.7.20-macos10.12-x86_64/include/mysql.h"

using std::cin;
using std::cout;
using std::endl;

class StrVec{
public:
    StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec &);
    StrVec(StrVec &&) noexcept ;
    StrVec &operator=(const StrVec &);
    StrVec &operator=(StrVec &&) noexcept ;
    StrVec &operator=(std::initializer_list<std::string>);
    std::string &operator[](std::size_t n) { return elements[n]; }
    const std::string &operator[](std::size_t n) const { return elements[n]; }
    ~StrVec();
    void push_back(const std::string &);
    void push_back(std::string &&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string * begin() const { return elements; }
    std::string * end() const { return first_free; }
private:
    std::allocator<std::string> alloc;
    void chk_n_alloc() { if (size() == capacity()) { reallocate(); } }
    std::pair<std::string *,std::string *> alloc_n_copy(const std::string *,const std::string *);
    void reallocate();
    void free();
    std::string * elements;
    std::string * first_free;
    std::string * cap;
};

StrVec::StrVec(const StrVec & s)
{
    auto data = alloc_n_copy(s.begin(),s.end());
    elements = data.first;
    first_free = cap = data.second;
}

StrVec::StrVec(StrVec && s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec& StrVec::operator=(StrVec && s) noexcept
{
    if (this != &s)
    {
        free();
        elements = s.elements;
        first_free = s.first_free;
        cap = s.cap;
        s.elements = s.first_free = s.cap;
    }
    return *this;
}

StrVec& StrVec::operator=(std::initializer_list<std::string> li)
{
    auto data = alloc_n_copy(li.begin(),li.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec & s)
{
    auto data = alloc_n_copy(s.begin(),s.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
{
    auto newcap = size()?2*size():1;
    auto data = alloc.allocate(newcap);
    uninitialized_copy(std::make_move_iterator(elements),std::make_move_iterator(first_free),data);
    free();
    first_free = data + size();
    elements = data;
    cap = elements + newcap;
}

void StrVec::push_back(const std::string & s) //string s = "done"; push_back(s)会调用此函数
{
    chk_n_alloc();
    alloc.construct(first_free++,s);
}

void StrVec::push_back(std::string && s) //当使用push_back("done")会调用此函数
{
    chk_n_alloc();
    alloc.construct(first_free++,std::move(s));
}

std::pair<std::string *,std::string *> StrVec::alloc_n_copy(const std::string * begin, const std::string * end)
{
    auto data = alloc.allocate(end - begin);
    return {data,uninitialized_copy(begin,end,data)};
}

void StrVec::free()
{
    if(elements) {
        for (auto p = first_free; p!=elements ;) {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements,cap - elements);
    }
}


int main(void)
{
    StrVec a;
    a = {"dengyan","yuanling"};
    std::ostream_iterator<std::string> out(cout," ");
    copy(a.begin(),a.end(),out);
}