# include <iostream>
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

using namespace std;
extern int x = 2;

template <class T> void swap(T * a,T * b)
{
    T c;
    c = *a;
    *a = *b;
    *b = c;
}

template <typename T,int S> class A
{
    public:
        T a;
        T b;
        A(T a)
        {
            this->a = a;
            this->b = S;
        }
        void plu();
};

template <typename T, int S> void A<T,S>::plu()
{
    cout << a << b << endl;
};

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

void read_in(vector<double> homework)
{
    int i = 0;
    double count;
    while(i++!=5)
    {
        cin >> count;
        homework.push_back(count);
    }
}

int c = 3;

using S1 = Sales_item;
typedef int * pstring;

auto change(int (*p)[5]) -> int (*)[5]
{
    return p;
}

void print(string & p)
{
    cout << "this is a quote func" << p <<endl;
}

void print(const string & p = "000")
{
    cout << "this is a const quote func" << p << endl;
}

constexpr int cst(int a)
{
       return a;
}

void print(const vector<int>& p)
{
    for (auto i : p)
        cout << i <<" ";
    cout << endl;
}

bool isShorter(const string &s1,const string &s2)
{
    return s1.size() < s2.size();
}

bool check_size(const string &s1,int sz)
{
    return s1.size() >= sz;
}

int main() {//6.4.1
    ostream_iterator<int> out_iter(cout," ");
    int * p = new int(4);
    unique_ptr<int> p1(p);
    p1.reset();
    *p = 3;
    cout << *p << endl;
}


/*
 *
 *
 *
 * u.reset(q) 使u指向q所指向的对象
 * u.reset() 释放u所指向的对象
 * u.release() u放弃对指针的控制权，不会释放u所指向的对象，返回指针
 * u = nullptr 释放u指向的对象
 * unique_ptr<value_type,d> u(p,d) 创建一个指针指向p，使用类型为d的对象p代替delete释放内存
 * unique_ptr<value_type,d> u 创建一个空指针，使用d代替delete释放内存
 * unique_ptr<value_type> u 创建一个空unique_ptr指针
 * 由于unique_ptr拥有其对象，因此它无法被拷贝或赋值，两种特殊情况除外，第一是从函数返回一个unique_ptr指针，第二是返回一个局部对象的拷贝，这两种情况下编译器都知道返回的对象即将被销毁，会执行一种特殊的拷贝
 * unique_ptr类: unique_ptr拥有它所指向的对象，同一时刻只有一个unique_ptr指向一个给定对象，当unique_ptr被销毁时，它所指向的对象也被销毁
 *
 * p.reset(q,d) p会指向q，并且使用d代替delete完成内存释放
 * p.reset(q) p会指向q
 * p.reset() 如果p是唯一指向其对象的shared_ptr，reset会释放此对象
 * p.unique() 如果p.use_count()为1，则返回true，否则返回false
 * p.use_count() 返回与p共享对象的智能指针数量
 * shared_ptr<value_type> p(q) p是q的拷贝，此操作会增加q中的计数器，q中的指针必须能转换为value_type *
 * make_shared<value_type>(args) 使用args的值初始化一个动态分配的类型为value_type的对象，返回一个shared_ptr的指针，args参数必须能对value_type类型的某个构造匹配
 * p.get() 返回p的指针值，与p是一样的
 * shared_ptr<value_type> p(q,d) 使用p初始化q，使p指向q，并使用d代替delete完成内存释放
 * shared_ptr<value_type> p(q) 使用p初始化q，使p指向q
 * shared_ptr<value_type> p 创建一个空智能指针，可以指向类型为value_type的对象
 * shared_ptr类: shared_prt指针允许多个指针指向同一个对象，智能指针也是模版，当创建一个智能指针时，需要提供额外的信息
 *
 * delete 接受一个动态对象的指针，释放与之关联的内存
 * new 函数在堆中分配空间并返回一个指针
 * 动态内存与智能指针:
 *
 * reserve(n) 重新存储，使得容器可以保存n个元素而不必rehash
 * rehash(n) 重新存储，使得正在使用的桶数量(bucket_count())大于等于n
 * max_load_factor() 容器试图维护的平均桶大小
 * load_factor() 每个桶的平均元素数量
 * 哈希策略:
 * cbegin(n),cend(n) 常量版本
 * end(n) 返回第n个桶中元素的尾后迭代器
 * begin(n) 返回第n个桶中首元素迭代器
 * const_local_iterator 常量版本
 * local_iterator 可以用来访问桶元素的迭代器类型，前面需加命名空间，如unordered_set<string>::local_iterator
 * 桶迭代:
 * bucket(key) 关键字key在第几个桶
 * bucket_size(n) 返回第n个桶中的元素个数，n可以为0
 * max_bucket_count() 容器能容纳的最多的桶的数量
 * bucket_count() 返回正在使用桶的数目
 * 桶接口:
 * 无序容器除了与有序容器相同的操作外，还有一些特定的操作
 * 管理桶: 无序容器在存储上组织为一组桶，每个桶保存零个或多个元素，无序容器使用一个哈希函数将元素映射到桶，为了访问一个元素，容器首先计算元素的哈希值，它指出应该搜索哪个桶，容器将具有一个特定哈希值的所有元素都放在同一个桶中，因此无序容器的性能依赖于哈希函数的质量和桶的大小和数量
 *
 * unordered_multiset 用哈希函数组织的set，关键字可重复出现
 * unordered_multimap 用哈希函数组织的map，关键字可重复出现
 * unordered_set 用哈希函数组织的set
 * unordered_map 用哈希函数组织的map
 * 无序容器: 这些容器不是使用比较运算符来组织元素，而是使用一个哈希函数
 *
 * equal_range(k) 返回一个迭代器pair，表示关键字等于k的元素的范围，若k不存在，则pair中的两个成员均等于尾后迭代器
 * 对于允许重复关键字的容器来说，可以通过掉用lower_bound(k)和upper_bound(k)来获得一个迭代器范围，这个范围内的元素关键字都为k，也可直接调用equal_range获得迭代器范围
 * upper_bound(k) 返回一个迭代器，指向第一个关键字大于k的元素，不适用于无序容器
 * lower_bound(k) 返回一个迭代器，指向第一个关键字不小于k的元素，不适用于无序容器
 * count(k) 返回关键字等于k的元素的数量，对于不允许重复关键字的容器，返回值永远是0或者是1
 * find(k) 返回一个迭代器，指向第一个关键字为k的元素，若k不在容器中，则返回尾后迭代器
 * 访问元素: 关联容器提供多种查找一个指定元素的方法
 *
 * at(val) 成员函数，返回val关键字所对应的值，如果val关键字不存在，则抛出一个out_of_range异常
 * map[val] 会返回关键字对应的值，如果val关键字不存在，则创建此关键字并初始化
 * map的下标运算符参数为一个关键字
 * map的下标操作:
 *
 * erase(start,end) 删除迭代器范围内的元素
 * erase(iterator) 删除迭代器所指向的元素
 * erase(val) 删除关键字为val的元素，返回一个size_type值，指明删除元素的数量
 * 删除元素:
 *
 * 对于multimap和multiset插入元素的返回值总是一个迭代器，因为允许插入重复元素，所以插入永远都会成功
 * insert(emplace)函数的返回值是一个pair类型，first成员是一个迭代器，指向插入元素的位置，second是一个bool值，如果成功插入则是true，如果插入值已经存在则返回false
 * emplace(val) 在容器中已val为参数构造元素
 * insert(val) 将值val插入容器
 * insert(list) 将列表中的数据插入
 * insert(start,end) 插入迭代器范围内的数据
 * 插入数据: 因为map和set包含不重复的关键字，因此插入存在的元素对容器没有任何影响，而且也不用指定插入到容器的哪个位置
 *
 * set的迭代器是const的，虽然set类型同时定义了iterator和const_iterator类型，但这两种都只允许只读访问set中的元素
 * 关联容器迭代器: 当解引用一个关联容器迭代器时，我们会得到一个类型为容器的value_type的值的引用
 *
 * value_type 对于set，与key_type相同，对于map，为pair<const key_type,mapped_type>
 * mapped_type 每个关键字关联的类型，只适用于map
 * key_type 该容器的关键字类型
 * 关联容器操作:
 *
 * second 返回pair的值
 * first 返回pair的关键字
 * make_pair(v1,v2) 返回一个用v1,v2初始化的pair
 * pair<T1,T2> s{v1,v2} 使用v1和v2初始化
 * pair<T1,T2> s(v1,v2) 使用v1和v2初始化
 * pair<T1,T2> T1为关键字，T2为值
 * pair类型: 是一个关键值-值的序对
 *
 * unordered_multiset 用哈希函数组织的set，关键字可重复出现
 * unordered_multimap 用哈希函数组织的map，关键字可重复出现
 * unordered_set 用哈希函数组织的set
 * unordered_map 用哈希函数组织的map
 * 无序集合:
 * multiset 关键字可重复出现的set
 * multimap 关键字可重复出现的map
 * set 关键字即值，即只保存关键字的容器，容器的成员函数find(val)返回指向val的迭代器，如没有val元素，则返回尾后迭代器
 * map 关联数组，保存关键字-值对，可通过在下标中使用关键字得到返回值，map中每个元素的成员函数有first()和second()，分别返回关键字和值，
 * 按关键字有序保存元素(使用比较运算符):
 * 关联容器: 关联容器支持高效的关键字查找和访问，两个主要的关联容器类型是map和set
 *
 * splice参数还可以为p,lst2,b,e，p2为lst2的某处的迭代器，将lst2中b到e迭代器范围内的元素插入
 * splice参数还可以为p,lst2,p2，p2为lst2的某处的迭代器，将范围为p2开始的lst2插入
 * l.splice_after(p.lst2) 将lst2中的元素插入到l中p之后的位置
 * l.splice(p,lst2) 将lst2中的元素插入到l中p之前的位置
 * l.unique(predicate)
 * l.unique() 调用erase删除同一个元素的连续拷贝
 * l.sore(compare) 使用compare进行排序
 * l.sort() 排序l中的元素，默认使用<
 * l.reverse() 反转l中的元素
 * l.remove_if(predicate) 删除使predicate位真的元素
 * l.remove(val) 调用erase删除掉与给定值相等的元素
 * l.merge(l1,compare) 该版本使用compare进行排序
 * l.merge(l1) 将l1的元素合并入l,l和l1必须是有序的，元素将从l1删除，
 * 特定容器算法: 链表类型list和forward_list定义了几个特定的算法
 *
 * _if版本的参数: 接受一个元素值的算法通常有另一个不同名的版本，该版本使用一个谓词来代替元素值，接受谓词参数的算法都附加有if前缀
 *
 * alg(beg,end,beg2,end2,other args)
 * alg(beg,end,beg2,other args)
 * alg(beg,end,dest,other args)
 * alg(beg,end,other args)
 * 大多数算法都具有如下四种形式之一
 * 算法形参模式: 在任何其他算法分类之上，还有一组参数规范
 *
 * 随机访问迭代器: 可读写，多遍扫描，支持全部迭代器运算
 * 双向迭代器: 可读写，多遍扫描，可递增递减
 * 前向迭代器: 可读写，多遍扫描，只能递增
 * 输出迭代器: 只写，不读，单遍扫描，只能递增
 * 输入迭代器: 只读，不写，单遍扫描，只能递增
 * 泛型算法结构: 任何算法最基本的特性都是它要求其迭代器提供哪些操作
 *
 * 移动迭代器: 这些迭代器不是拷贝其中的元素，而是移动它们
 *
 * 反向迭代器的base成员函数将其转换成普通迭代器，并移向右边下一个元素
 * 使用容器的成员函数rbegin和rend()即可获取反向迭代器首和尾，分别指向尾元素和首元素之前位置
 * 反向迭代器: 反向迭代器就是在容器中从尾元素向首元素移动的迭代器，对于反向迭代器，递增以及递减操作会颠倒过来，递增一个反向迭代器(++it)会移动到前一个元素，递减一个迭代器(--it)会移动到下一个元素，除了forward_list之外的标准库容器都有反向迭代器
 *
 * *out_iter,++out_iter,out_iter++ 不会做任何事，每个操作都会返回out_iter
 * copy(a3.begin(),a3.end(),out_iter); 将a3里的数据写入流out_iter
 * ostream_iterator<string> out_iter(out); out_iter = "dy"; 向out流里写入dy字符串
 * ostream_iterator<value_type> 向一个输出流写数据，是一种输出迭代器，有单参数和可选的双参数版本，第二个参数接受一个C风格字符串，在输出每个元素后都会打印此字符串
 *
 * 当in_iter与eof指向同一个地方后，可以看作in_iter已报废，需要重新生成后使用
 * istream_iterator允许使用懒惰求值: 当我们将istream_iterator绑定到一个流时，标准库并不保证迭代器立即从流中读取数据，具体实现可以推迟从流中读取数据，直到真正使用迭代器时才真正读取
 * 与一般的迭代器有相同的操作，*in_iter，in_iter++,++in_iter等等，可看作读取后是生成了某个容器保存这些数据
 * istream_iterator<int> in_iter(cin),eof; vector<int> a(in_iter,eof); 通过读取流里的整形数组生成vector
 * istream_iterator<value_type> 读取输入流，是一种输入迭代器，单参的构造函数参数类型是流类型
 * iostream迭代器:
 * 流迭代器: 这些迭代器被绑定到输入或输出流中，可用来遍历所关联的流
 *
 * *it,++it,it++ 不会做任何事，每个操作都会返回it
 * 可直接用 it = val操作，如果it是inserter函数生成，对it赋值会在p迭代器指向元素之前插入元素，插入后it仍指向p
 * 假如这三个函数的返回值都为it
 * inserter(container,p) 创建一个使用insert的迭代器，p为一个迭代器，指向想插入的容器位置
 * front_inserter(container) 创建一个使用push_back的迭代器
 * back_inserter(container) 创建一个使用push_back的迭代器
 * 插入迭代器: 这些迭代器被绑定到一个容器上，可用来向容器插入元素
 * 迭代器:
 *
 * 绑定引用参数: 如果bind的列表参数的值无法拷贝，则会调用失败，比如bind参数里含有os参数，os无法拷贝，但是os的引用可以，这里使用ref函数，该函数返回一个引用，如ref(cout)
 * 用bind重排参数列表: 比如sort(a5.begin(),a5.end(),[](const string &s1,const string &s2) { return s1.size() < s2.size();}) 按字符串长度从小到大排序，可通过bind实现从大到小排序sort(a5.begin(),a5.end(),bind([](const string &s1,const string &s2) { return s1.size() < s2.size();},placeholders::_2,placeholders::_1))
 * 可通过bind进行更方便的调用: 假如f是一个可调用对象，它有5个参数，则auto g = bind(f,a,b,_2,c,_1)生成一个新的可调用对象，它有两个参数，分别用_2,_1表示，当调用g(_1,_2)时，会映射为f(a,b,_2,c,_1)，f的实参都是通过bind列表参数的值拷贝的
 *
 * auto it = find_if(a5.begin(),a5.end(),[sz](const string & s1) { return s1.size() >= sz; });
 * auto it = find_if(a5.begin(),a5.end(),nCheck);
 *
 * bool check_size(const string &s1,int sz)
 * {
 *   return s1.size() >= sz;
 * }
 *
 * auto newFunc = bind(func,arg_list) 即通过老函数加上参数绑定生成一个新函数，arg_list是由占位符和普通参数的列表，占位符格式为 _n，根据n的值表示这是newFunc第几个参数，_n存在于std::placeholders中
 * 参数绑定: 对于某些函数的参数个数可能有一定的限制，比如find_if的第三个参数需要指定一个单参数谓词，可是如过我想让它接受两个参数，就需要用到该函数
 *
 * lambda: 如果想改变捕获变量的值,无论时值捕获还是引用捕获，都需要添加mutable关键字在参数列表后
 * 混合捕获: 可以对部分变量采用值捕获，其他变量采用引用捕获，[=,list] 默认为值捕获，list里必须为引用捕获，[&,list] 默认为引用捕获，list里必须为值捕获
 * 隐式捕获: 除了显示列出我们希望使用的来自函数的变量之外，还可以让编译器根据lambda体中的代码来推断我么要使用哪些变量，[=]表示值捕获，[&]表示引用捕获
 * 引用捕获: 即在lambda中对被捕获量进行改变会影响到外部的值，由于lambda捕获的是局部变量，因此需要确保在调用lambda时该变量仍然存在，有时引用捕获是有必要的，比如对流进行引用
 * 值捕获: 即当创建lambda时捕获列表中的值会被拷贝到lambda函数，由于被捕获的值是在lambda创建时拷贝，因此随后对其修改不会影响外部的值
 * 当定义一个lambda时，编译器生成一个与lambda对应的新的类类型，如果此时捕获列表的方式为值捕获，那么无论对于显式还是隐式的值捕获，在定义lambda时这个值就已经被确定了，后面调用此函数时就会使用此值，而不是在调用时再去获取，当向一个函数传递一个lambda时，同时定义了一个新类型的一个对象，传递的参数就是此编译器生成的类类型的未命名对象
 * lambda: [capture list](parameter list) -> return type { function expression } 可以忽略参数列表和返回类型，但是一定要有捕获列表和函数体     (当函数体包括除return语句之外的其他语句时，此时lambda的默认返回类型为void，此时需要显式指定返回类型)-------书上这样写，但是经过试验发现默认返回类型不是void
 *
 * a1.erase(unique(a1.begin(),a1.end()),a1.end()) 删除所有重复元素
 * unique(start,end) 重排输入范围，使得每个元素只出现一次，返回指向不重复区域之后一个位子的迭代器，迭代器之后的元素并不能确定
 * stable_sort(start,end,predicate) 如果predicate(双参)是一个比较字符串长度的谓词，此函数可以对长度相等的字符串仍然有以前的相对顺序，可通过先调用sort按字典序排序，再通过stable_sort按长度排序，这样就能对同等长度的字符串进行字典排序
 * stable_sort(start,end) 保持相等元素的原始相等位置
 * sort(start,end,predicate) 根据predicate(双参)对输入范围的元素排序
 * sort(start,end) 将start和end迭代器范围的元素按字典序排序
 * 排列算法:
 *
 * replace(start,end,val,rpval) 将start和end迭代器范围内值为val的元素替换为rpval
 * cope(start1,end1,start2) 将start1和end1迭代器范围内的元素拷贝给从start2迭代器开始的元素
 * 拷贝算法: 向目的位置迭代器指向的输出序列中的元素写入数据的算法，接受三个参数，前两个表示一个输入范围，第三个表示目的序列的起始位置，需要保证目的序列的size大于输入范围的元素个数
 *
 *
 * transform(start1,end1,start2,predicate) 当start1等于start2时，对迭代器start1和end1的每个元素调用predicate(单参)，并将元素原本值替换为函数的返回值
 * back_inserter(vec) 返回一个指向容器的插入迭代器，当对此迭代器解引用赋值时，实际上就是在调用push_back进行插入，因此可以作为fill_n的第一个参数，即使该容器的size小于n
 * fill_n(start,n,vak) 向start开始的n个元素中写入val
 * fill(start,end,val) 将start和end迭代器所指定范围内的元素全部变为va;
 * 写算法: 需要注意的是算法并不会改变容器的大小，如果需要对容器内进行写操作，需要保证容器大于写入的内容，这里的容器大小指的是size而不是capacity
 *
 *
 * for_each(start,end,predicate) 对迭代器范围内的每个元素调用谓词predicate(单参)
 * find_if(start,end,predicate) 在迭代器范围内查找第一个满足谓词predicate(单参)的元素，返回该元素的迭代器
 * count(start,end,val) 在迭代器start和end范围内查找值val出现的次数
 * equal(start1,end1,start2) 将迭代器start1和end1所指定范围的各个元素与start2迭代器开始的同样大范围的各个元素进行比较，相等返回1，否则返回0
 * accumulate(start,end,0) 对迭代器start和end所指定范围内的元素求和，和的初值是0，可用于连接字符串
 * find(start,end,val) 在迭代器start和end范围内查找值val，如果找到，则返回一个指向该元素的迭代器，否则返回第二个参数，该比较内部实现是对start解引用后与val进行比较，因此如果用string作为容器，val只能为字符
 * 只读算法: 一些算法只会读取其输入范围内的元素，从不改变元素
 *
 * 泛型算法: 除了少出例外，标准库算法都是对一个范围内的元素进行操作，将这个范围称为输入范围，接受输入范围的算法总是使用前两个参数来表示此范围，这两个参数分别是指向要处理的第一个元素和尾元素之后位置的迭代器
 *
 * emplace(arg) 由arg构造
 * push(item) 在队列尾端加入一个元素
 * top() 只适用于priority_queue，返回最高优先级元素
 * back() 返回队列的尾元素，不删除值
 * front() 返回队列的首元素，不删除值
 * pop() 删除队列的首元素
 * 队列适配器:
 *
 * top() 返回栈顶元素，但不弹出
 * emplace(arg) 由arg构造
 * push(item) 创建一个新元素加入栈顶
 * pop() 删除栈顶元素
 * 栈适配器:
 *
 * a.swap(b) 等价swap(a,b)
 * swap(a,b) 交换容器a,b的内容
 * a.size 查看容器元素个数
 * a.empty() 查看容器是否为空
 * 关系运算符
 * A a(c) 创建一个名为a的适配器，带有容器c的一个拷贝
 * A a 创建一个名为a的空适配器
 * container_type 实现适配器的底层容器类型
 * value_type 元素类型
 * size_type 容器大小
 * 所有适配器都支持的操作:
 * priority_queue使用vector实现
 * stack queue使用deque实现
 * 容器适配器:
 *
 * string的成员函数empty() size()
 * 不能将两个连续的字符串字面值相加，比如s1 = "12" + "12" + s1错误，s1 = s1 + "12" + "12"正确，因为是从左向有加，s1 + "12"会得到string类型
 * string::size_type
 * getline(cin,s) 类似gets 从标准输入读取字符串，直到遇到换行符(换行符也被读取)，但是并不将换行符存入s
 *
 * stold(s,p) 转长双精度浮点数
 * stod(s,p) 转双精度浮点数
 * stof(s,p) 转浮点数
 * stoull(s,p,b) 转无符号长整形
 * stoll(s,p,b) 转长整形
 * stoul(s,p,b) 转无符号整形
 * stoi(s,p,b) 转整形 s为字符串，p为指针，返回第一个不为数字字符的下标，b为基数，即该字符串表示的数字是几进制的
 * to_string(int) 将整数转换为字符串
 * 数值转换(以下函数不是成员函数):
 *
 * pos,n,cp,n2,len 用字符串中下标为pos开始的n个字符与cp+n2开始的len个字符比较
 * pos,n,cp,n2 用字符串中下标为pos开始的n个字符与cp开始的n个字符比较
 * pos,n,cp 用字符串中下标为pos开始的n个字符与cp比较
 * cp 与c语言风格的字符串比较
 * pos1,n1,s,pos2,n2 用字符串中下标为pos1开始的n1个字符与s2中下标为pos2开始的n个字符进行比较
 * pos,n,s2 用字符串中下标为pos开始的n个字符与s2进行比较
 * s2 直接与s2比较
 * args:
 * compare(agrs)函数:类似于c语言里的strcmp
 *
 * cp,pos,n 查找cp所指向的前n个字符
 * cp,pos 从pos开始处查找cp指针所指向的c风格字符串
 * s2,pos 从字符串中位置为pos开始查找字符串s2
 * c,pos 从字符串中位置为pos开始查找字符c，pos默认值为0
 * arg比较是以下形式:
 * find_last_not_of(args) 在字符串中查找嘴鸥一个不再args中的字符
 * find_first_not_of(args) 在字符串中查找第一个不在args中的字符
 * find_last_of(args) 在字符串中查找args中任何一个字符最后一次出现的位置
 * find_first_of(args) 在字符串中查找args中任何一个字符第一次出现的位置
 * rfind(args) 查找args最后一次出现的下标
 * find(args) 查找args第一次出现的下标
 * 字符串搜索操作:
 *
 * replace(range,arg) 删除range返回内的字符，替换为args指定的字符，range可以为下标加len，也可以是迭代器
 * append(args) 将args追加到到字符串后，返回引用
 * assign() 类似于构造参数
 * erase() 类似于构造参数
 * insert() 类似于构造参数
 * 修改字符串:除了前面已有的，还有特有的版本
 *
 * substr(pos,len) 返回下标为pos开始的len个字符串
 * substr(pos) 返回下标为pos开始的字符串
 * substr() 返回整个字段串
 * 子字符串操作:
 *
 * string s1(string,pos,len) 用string的下表pos开始的len个字符进行初始化
 * string s1(string,n) 用string的下标n开始的元素进行初始化
 * string s1(list,n) 用list数组的前n个字符初始化，这里的list为char []
 * string s1 = s2 使用等号则为拷贝初始化，不使用等号则为直接初始化
 * string s1(n,'c')
 * string s1("")
 * string的初始化:
 * string操作:
 *
 * reserve(n) 分配至少能容纳n个元素的内存空间，即使分配了也无法用指针或者迭代器直接使用，只能通过push_backh或者insert,若reserve的参数小于当前的容量，则什么都不做
 * capacity() 不重新分配空间的话，容器可以保存多少元素
 * shrink_to_fit() 退回不需要的内存空间
 * 管理容器(vector,string,deque可用):由于在创建vector对象时会实现分配更大的空间以避免向vector增加元素时平凡的内存重分配
 *
 * resize(n,t) 调整容器的大小为n，并将多出来的元素初始化为c
 * resize(n) 将容器中的元素调整为n个，若n<c.size() 则多出来的元素被丢弃，但是容器的大小不会减少，若n>c.size() 则对新添加的元素进行值初始化，容器会增大，对forward也可用
 * 改变容器大小(不使用array):
 *
 * erase_after(iterator start,iterator end) 删除start之后end之前的元素
 * erase_after(iterator) 删除迭代器所指向的后一个元素，返回最后一个被删除元素之后元素的迭代器
 * insert_after(iterator,li) 在迭代器后插入列表li
 * insert_after(iterator,iterator start,iterator end) 在迭代器后面插入由start和end迭代器所指定范围内的元素
 * insert_after(iterator,n,t) 在迭代器所指向之后的位置插入n个t
 * emplace_after(iterator,t) 在迭代器所指向之后创建一个元素
 * insert_after(iterator,t) 在迭代器所指向之后的位置插入元素t
 * cbefore_begin()返回常量迭代器
 * before_begin() 返回首元素之前元素的迭代器，不能对该迭代器解引用
 * forward_list成员函数:
 *
 * forward_list元素操作:forward_list中没有定义insert,emplace,erase,因为这些函数都是处理迭代器之前的元素，即使是erase处理的是迭代器指向的元素，但是由于forward的结构，删除元素后需要被删除元素的前一个元素的next指针指向下一个元素，但是forward无法简单的过去到元素的前驱
 *
 * c.clear() 删除c中的所有元素
 * c.erase(b,e) 删除迭代器b,e返回中包含的元素，返回最后一个被删除元素之后元素的迭代器
 * c.erase(iterator) 删除迭代器指定的元素
 * c.pop_front() 删除c中的头元素，vector，string不支持
 * c.pop_back() 删除c中的尾元素，forward_list()不支持
 * 删除元素:
 *
 * c.at(n) 返回给定下标元素的引用，如果c是const类型，则返回的引用都含有底层const
 * c.back() 返回c尾元素的引用，forword_list不支持
 * c.front() 返回c首元素的引用，如果用auto作为类型，需要用auto &，否则只是接受了拷贝
 * 访问元素:
 *
 * c.insert(iterator,li) 插入列表li中给定的值
 * c.insert(iterator,iterator start,iterator end) 将start和end间的数据插入c
 * c.insert(iterator,n,arg) 插入n个arg
 * c.insert(iterator,arg) c.emplace(iterator,arg) 将arg中的元素插入iterator迭代器之前，insert是创建对象后拷贝进容器，emplace是直接在容器中构造元素，insert返回第一个新加入元素的迭代器
 * c.push_front(t) c.emplace_front(arg) 在c的头部插入元素，string和vector不支持
 * c.push_back(t) c.emplace_back(arg) 在c的尾部插入元素，forward_list不支持
 * 向顺序容器添加元素(array除外):
 *
 * 容器的关系运算符:容器进行比较时，比较方式如同string的比较方式，即对容器的元素依次比较，实际上比较时使用元素的关系运算符对进行相应的关系运算，如果容器元素并没有定义关系运算，比如某些类，则不能比较该类型的容器
 * array类型:定义时不仅要指定元素类型，还需要指定容器大小，比如array<int,10>
 *
 * c.crbegin(),c.crend() 返回const_reverse_iterator
 * c.rbegin(),c.rend() 返回指向c的尾元素和首元素之前的迭代器
 * const_reverse_iterator 不能修改元素的逆序迭代器
 * reverse_iterator 按逆序寻址元素的迭代器
 * 反向容器的额外成员(不支持forward_list):
 *
 * c.cbegin(),c.cend()返回const_iterator
 * c.begin(),c.end() 返回c的首元素和尾元素之后位置的迭代器
 * 获取迭代器:
 *
 * c.empty() 若容器为空，返回1，否则返回0
 * c.max_size() c可保存的最大元素数目
 * c.size() 返回c中元素的数目(forward_list不支持)
 * 容器大小:
 *
 * a.assign(il) 用列表il中的值替换a，
 * a.assign(n,t) 用n个t值替换a中的值
 * a.assign(b,e) 将a中的元素替换为b,e迭代器返回中的元素
 * a.swap(b) 交换a,b，swap(a,b)与a.swap(b)等价，除了array以外都不会交换真正的元素，只交换数据结构，调用swap后除了元素string类型以外的指针引用迭代器都不会失效(可以理解成成员为string的容器交换了元素，原本的指针指向了新的量)
 * c1 = c2，c1 = {a,b,c,d}
 * 赋值与swap与assign:
 *
 * value_type c{a,b,d} 列表初始化
 * value_type c(b,e) 将迭代器b和e指定返回内的元素拷贝到c(不适用array)，不需要容器类型相同，只要容器类元素能相互转换即可
 * value_type c(n,t) 包含n个t元素
 * value_type c(n) 包含n个元素
 * value_type c(c1) 用另一个容器进行初始化，需要有相同的容器类型和元素类型
 * value_type c，调用默认构造函数，构造空容器
 * 构造函数:
 *
 * 类型别名:iterator 迭代器; const_iterator 常量迭代器; size_type 容器大小，无符号整型; differece_type 用于迭代器之间距离大小，有符号整型; reference 左值类型，等价value_type&; const_reference const左值类型，相当于常量引用
 *
 * string 与vector相似，专门用于保存字符
 * array 固定大小数组
 * forward_list 单向链表
 * list 双向链表
 * deque 双端队列(静态队列，应该是用数组形式实现的)，在头和尾插入数据很快，支持随机访问
 * vector 可变大小数组，在尾部插入数据很快
 * 顺序容器:
 *
 * stringstream:istringstream从string中读取数据，ostringstream向string中写入数据，stringstream可以读写字符串，构造方法有无参和单参，单参参数为字符串型，用于在流中保存一个参数的拷贝，成员函数有.str()和.str(s)，分别为返回流中字符串的拷贝和将流拷贝进字符串，拷贝进的字符串会使以前的字符串消失，一般用于getline读取一行后分别处理单个单词

 * 只有以in模式或者out|app模式打开时不会截断数据，其他情况打开文件，文件数据都会消失，而对0_WRONLY打开的文件进行写时只会造成数据覆盖
 * 文件模式:in|out|app|ate|trunc|binary 分别为以读方式打开，写方式打开，写追加，打开后定位到尾部，截断文件，以二进制打开，当使用这些常量时，需在前面加上所属的命名空间，以ifstream类型打开时默认指定in文件模式(O_RDONLY)，ofstream会指定out模式(O_WRONLY)，fstream以in和out模式打开(O_RDWR)
 * fstream:fstream;可以理解为FILE *类型，fstream(s);可以理解位fopen，fstream(s,mode)带模式的fopen，fstream.open(s)与fstrm(s)差不多，fstream().close()，fstream.is_open()返回一个bool查看是否正确打开
 * 流关联:当从输入流读取时，会将所关联的输出流的传冲去的数据输出，可以使用流的成员函数tie()进行操作，无参数版本返回当前所关联的流，也有一个参数的重载版本，将流与参数的流相关联，如用null指针作为参数则可取消其关联的流，一个流只能关联一个流，但一个ostream流可以被多个流同时关联
 * 管理输出缓冲:可在 << 操作符后接上endl,ends,flush中的一个冲刷缓冲区，分别会在结尾加上换行符，一个空字符，什么都不加，用cout << unitbuf;后会使接下来的每一次输出操作都刷新缓冲区，使用cout << nounitbuf可以恢复正常的缓冲方式
 * IO条件状态:以下类型均在某种IO类型的命名空间内所定义的常量，括号类表示其常量值，如iostream::iostate，iostate:表示条件状态，badbit(4):指出流已经崩溃，failbit(1):指出IO操作失败，eofbit(2):指出流已经到达文件尾端，goodbit(0):指出流未处于错误状态，成员函数:eof()，fail()，bad()，good()分别返回对应位的信息，若已置位，则返回true，clear()复位所有状态位，clear(iostate falg)复位falg所指定的位，setstate(iostate flag)设置对应的位置位，rdstate()，返回当前的条件状态
 * IO对象无拷贝或赋值，可以通过引用传递和返回流
 * IO类:头文件iostream:istream,wistream从流中读取数据，ostream,wostream向流中写入数据，iostream，wiostream读写流；头文件fstream:ifstream,wifstream向文件读取数据，ofstream,wofstream向文件写入数据，fstream，wfstream读写文件；istringstream,wstringstream从string中读取数据，ostringstream，wostringstream向string中写入数据，stringstream，wstringstream读写string
 * IO类型间的关系:ifstream istringstream都继承istream类，则在使用isteam类的地方可以使用ifsteam和istringstream
 * 静态成员的使用场合:静态数据成员类型可以是不完全类型，比如它可以是它所属的类类型，或者是将其作为默认实参
 * 类的静态成员:在成员的声明前面添加static即可，静态成员只与类有关，与类所生成的对象无关，可在函数内部声明，外部定义，外部定义时不能添加static，因为内部已经有static声明了，static不能和const共存，静态成员函数也类似，它们没有this指针，因此静态成员函数不能使用类中的成员，可以使用静态成员
 * 对explicit的构造函数进行强制调用:使用static_cast将构造函数里的参数类型转换成类类型即可
 * 抑制构造类型的隐式转换:在构造函数前增加关键字explicit，只能在类内部使用，外部定义的构造函数不可用,关键字explicit只对一个实参的构造函数生效，因为需要多个参数的构造函数不能用于隐式转换
 * 隐式的类类型转换:对于只有一个的构造函数构造函数来说，在需要使用类类型的地方，可以使用构造参数的类型来代替，包括值初始化处，如Sales_data &combine (const Sales_data&) 是一个成员函数，参数为类类型，此时可以用单参数构造函数里的参数类型，编译器会将这个参数通过调用构造函数转换成一个类类型，编译器只运行一步类类型转换，即如果构造函数参数是string，此时使用字符串常量作为conbine参数会失败，因为需要先将字符串常量转换成string，再由string转换成类类型
 * 要想使用默认构造函数，应使用Sales_data s;而不是Sales_data s()
 * 委托构造函数:即某个构造函数通过调用其他构造函数实现初始化
 * 类的作用域:类的返回类型属于类的外部作用域，如果返回类型是类内所定义的类型，则需要在前面加上类名，而类的成员函数的参数和函数体都属于内部作用域，不需要在类型前面加上类名
 * 类类型:对于两个类来说，即使它们的成员完全一样，这两个类也是不同的类型，在创建类对象时，可以增加关键字class或者struct，也可以省略
 * 基于const的重载:可以针对成员函数是否是const对其进行重载，如果类是常量类型，类中的非const成员函数将不可用，所以需要重载一个对应的常量成员函数
 * 类内初始化值:必须用 = 或者 {}进行初始化
 * 可变数据成员:采用mutable关键字修饰，该种类型的成员总是可以改变，一个可变数据成员永远不会是const，即使它是const对象的成员，因此，即使是一个const成员函数，也能改变可变数据成员的值
 * 重载成员函数:成员函数也可以被重载，具体原理和操作与非成员函数十分类似
 * 类型成员:在类内使用typedef xx x或者using xx = x来定义一个类型成员，类型成员必须先定义后使用，因此类型成员通常出现在类的最前面
 * 函数重载与友元:尽管重载函数的名字相同，但它们仍然是不同的函数，因此，如果需要把一组成员函数设置成友元，需要对这组函数中的每一个分别声明
 * 成员函数作为友元:当声明了友元类后，整个友元类的成员函数都可以对该类的所有成员进行访问，为了减少访问权限，可只对某个类中的部分成员函数开放权限，即将成员函数设置成友元，如friend xx::x(); 需要指明是哪个类中的函数
 * 友元类:在类中加上friend class xx代码，即将xx声明为友元类，友元类的成员函数可以访问此类包括非公有成员的所有成员，友元不具有传递性，即如果1是2的友元，2是3的友元，但是1不能访问3的成员
 * 友元:类可以允许其他类或者函数访问它的非公有成员，方法是另其他类或者函数成为它的友元，如果类想把一个函数作为它的友元，只需要加一条以friend关键字开始的函数声明语句即可
 * class关键值和struct关键值:如果使用struct关键值，则定义在第一个访问说明符之前的成员是public的，如果使用class，则那些成员是private的，使用class和struct的唯一区别就是默认的访问权限
 * 访问说明符:public和private
 * 默认实参与构造函数:可以为构造函数内的参数提供默认实参，如构造函数只有一个参数的情况下，且为其提供了默认实参，则等于同时定义了无参数的构造函数
 * 构造函数初始化列表:初始化发生在构造函数体运行之前，正如它所存在的位置，存在与构造函数参数之后，函数体之前，格式为: xx(a),x(b)，此初始化和在构造函数体内赋值是不同的操作，一个是初始化一个是赋值，具体有什么影响取决于函数的类型，如果类中有常量，引用，或者某种没有默认构造函数的类类型，则必须初始化,还有string对象只有在初始化时才能使用()，而在赋值时并不可以
 * 构造函数:类中的构造函数没有返回类型，且构造函数不能被声明为const，如果存在类内的初始值，用它类初始化成员，否则，默认初始化该成员，使用 = defult生成默认构造函数，如果 = default出现在类的内部，则默认构造函数是内联的，如果default出现在外部，即在类内声明，内外定义，则它是不内联的
 * 类中的成员不一定要在成员函数前定义，编译器分两部处理类，首先编译成员的声明，然后才轮到成员函数体
 * 常量成员函数:成员函数名后的const用于修改this指针的类型，假如this指针本为 void * const类型，加上const后会编程const void * const类型，这是因为如果this指向某个常量，必须要有底层const
 * 函数指针:即指向函数的指针，样列为:返回类型 (*指针名)(参数列表) 其返回类型与参数列表需要与所指向的函数完全相同
 * constexpr函数:在函数的返回值前加上constexpr关键值，constexpr函数是指能用于常量表达式的函数，隐式的被指定为内联函数，其参数必须为字面值类型，不能为变量名，因为在编译阶段就需要将所有对constexpr函数的调用替换成其结果值
 * 内联函数:在函数返回类型前加上inline关键字，内联说明只是向编译器发出一个请求，编译器可以选择忽略这个请求，一般用于规模较小，调用频繁，调用直接的函数，定义在类内部的成员函数是自动inline的
 * 局部变量不能作为默认实参，即可使用全局变量和全局函数
 * 默认实参:当某个形参被赋予了默认值后，这个值后其余的形参也需要被赋予默认值 void print(const string & p = "000");可对引用类型赋予默认值，该函数可不用参数即可调用
 * reinterpret_cast:一般用于转换指针类型
 * static_cast:只要类型不包含底层const，都可以使用static_cast进行强制类型转换
 * const_cast<string &>(r) 如果r是常量引用，则可将它转换成非常量引用，可在重置中根据参数是常量引用还是非常量引用返回与其相同的类型，比如非常量版本可以通过调用常量版本，通过const_cast将常量版本的返回值转换成非常量版本然后返回，string &s4 = const_cast<string &>(s3);
 * 命名的强制类型转换:cast-name<type>(expression) type是需要转换的目标类型，如果type是引用类型，则结果是左值
 * 重载时不区分顶层const，但区分底层const(指常量指针和常量引用)，即参数为int *和const int *是不同的函数，因为底层const必须继承，如果定义int a;const int * b = &a，以b作为参数的话，函数必须要是const int *型的参数，这样才能保证函数不会改变指针指向的值
 * 函数重载:同一个内的几个函数名字相同但形参列表不同
 * 使用或者已知定义了某个数组，比如int a[5]，使用decltype(a)作为返回类型
 * 尾置返回类型:auto func(int i) -> int (*)[10] 返回一个指针，指向含有十个整数的数组
 * 声明一个返回数组指针的函数，int (*func(int c))[10] (*func)表示我们可以对函数调用的结果执行解引用操作，(*func(int c))[10]表示解引用func的调用将得到一个大小是10的数组
 * initializer_list<T> 若函数形参类型都相同，则可用该对象做变长参数，参数使用列表形式，如{1,2,3,4,5,6,7,8}
 * 把函数定义成不会改变的形参定义成引用是一种常见的错误，尽量使用常量引用作为参数类型，因为常量引用可以接受字面值作为参数
 * try {statement}catch (exception error){ }
 * 在用范围for语句处理多维数组时，除了最内层的循环外，其他所有循环的控制变量都应该是引用类型
 * begin() end()函数 类似于容器内的成员函数，但是数组这类对象没有成员函数，故用begin和end，对于多位数组不适用
 * const_iterator 相当于常量指针
 * vector的成员函数 size(),empty(),push_back(c),pop_back() begin() end() cbegin() cend() 用于返回const_iterator，
 * 用圆括号()初始化可以看作是构造函数的参数，而花括号{}看作是直接赋值
 * vector的初始化 vector<int> v1;vector<int> v2(v1);vector<int> v2 = v1;vector<int> v3(n,val);vector<int> v4(n);vector<int> v5{a,b,c,d};vector<int> v6 = {a,b,c,d};vector<int> v(begin(buf),end(buf))
 * for (auto &c : s1) 用于改变s1的值
 * for (auto c : s1) 用于不改变s1的值
 * isalnum(c)字母或数字字符 isalpha(c)字母 iscntrl(c)控制字符 isdigit(c)数字字符 isgraph(c)除空格的可打印字符 islower(c)小写字母 isprint(c)可打印字符 ispunct(c)标点字符 isspace(c)空格 isupper(c)大写字母 isxdigit(c)十六进制数字字符 tolower(c)转换成小写，toupper(c)转换成大写，但返回值是int，需要转换成char

 * 类的初始化，放在花括号里，放在等号右边，S1 S{};或S1 S = {};
 * decltype()为类型指示符，根据括号内表达式的类型确定后面说定义数据的类型，如果括号类是解引用表达式，如int j = 3,*p = &j;decltype(*p) i = x;则i是一个引用类型，而不是int型，如果decltype()括号中的变量加了括号，那么会将其视为一个表达式，返回引用类型，如decltype((i)) = x;
 * 可以为常量引用绑定字面值，比如const auto &j = 43;
 * typedef int * pstring; const pstring是常量指针，等于int * const，而不是直接带入成const int *
 * using SI = Sales_item 新的别名声明的方法，也可用typedef
 * constexpr int * 是指针常量，等于是int * const，属于顶层const，constexpr const int * 等于是const int * const
 * 用constexpr类型声明的的变量一定是一个常量表达式(const int a = getpid()不是常量表达式，因为无法在编译阶段获取它的值)，由编译器来验证，即如果用一个函数作为constexpr的初始化会报错，如constexpr int a = getpid();
 * 底层const:表示指针所指向的对象是一个常量，底层const只不过是指针或者引用的属性而已，与它所指向的量是否是常量没有关系
 * 顶层const:表示这个对象是个常量，顶层const的量复制给其他量时不需要在意是否有顶层const，但是对其的指针和引用需要有底层const
 * 常量指针 表示指向的对象是常量，不允许通过指针修改所指向的值const int *
 * 指针常量 int * const 表示这个指针本身是常量，初始化后它的值不会改变，但是它指向的值可以改变，除非定义const int * const，这样代表指向常量的指针常量，即不可改变指针的值也不可改变指针指向的值
 * 指向常量的指针和引用只是说不能使用指针和引用去改变它们而已，其本质上并不一定是常量，const ptr *(&)
 * 当使用int &去引用一个浮点数时，这种行为是错误的，本质上来说可以理解为int *型指针无法指向double型的数据，可使用const int &引用一个浮点数，此时它引用的是一个被转换成int型的临时量
 * int * p;int * &a = p;定义指针的引用
 * int * p = nullptr;初始化为空指针
 * int a = 2;int * p = &a;int &b = *p;此时b是对a的引用，因此*p应该看作是变量a，而不是2
 * 引用必须初始化，且其类型必须与引用的类型相同(有两个例外，一个是使用常量引用非常量的变量)，初始化后绑定的引用对象在之后不可更改，引用本质上是指针实现的，可将它看为对象的别名，引用不是对象，不能定义引用的引用，即int &&类型
 * 可用::x特指全局变量
 * extern int i; 为声明语句，在后面对该值进行赋值将引发错误，一般用于对外部变量的使用，extern int i = 2; 为定义语句，等价int i = 2;
 * 初始化不是赋值，四种初始化的方式，int a = 0;int a(0);int a{0};int a = {0}，使用{}初始化称作为列表初始化，当使用列表初始化切初始化存在丢失信息的风险时，编译器会报错
 * 一个表达式中如果既有无符号数又有int时，得到的结果是无符号数
 * sort(begin(),end()) 排序容器
 * vector<double>::iterator 定义vector内部数据类型为double的迭代器，若在循环中定义可用auto代替
 * setprecision(int) 设置流输出浮点数的精度，放在流中作为一部分，并且此后流输出的浮点数均为此精度，cout << setprecision(int)
 * cout.precision() 获取流输出浮点数的精度
 * vector本质是数组，list是链表 以vector为类型定义的变量，并不是指针，类 类型作为函数参数传递时，传递的是类的拷贝，而不是类的地址
 */