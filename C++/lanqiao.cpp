# include <iostream>
# include <vector>
# include <map>
//# include <set>
# include <algorithm>
# include <iomanip>
# include <queue>
# include <unordered_map>
# include <functional>
# include <stack>
# include <list>
# include <random>
# include <fcntl.h>
# include <unistd.h>
# include <sstream>
# include <iterator>
# include <functional>

using std::cin;
using std::cout;
using std::endl;

using namespace std;

int isprimer(int i) //素数返回-1
{
    if (i < 4)
        return -1;
    int j;
    int threshold = i / 2 + 1;
    for (j = 2; j < threshold; ++j) {
        if (i % j == 0)
            break;
    }
    return j == threshold?-1:j;
}

/*
 * std::ios::sync_with_stdio(false); 解除c++与c流的同步，解除后切勿混合调用cin和scanf，cout和printf
 * cin.tie(); 解除因每次cin调用而导致调用fflush冲刷输出缓冲区
 */

static const auto io_sync_off = []()
{
    // turn off sync
    std::ios::sync_with_stdio(false);
    // untie in/out streams
    std::cin.tie(nullptr);
    return nullptr;
}();

struct ListNode {
         int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
         int val;
         TreeNode *left;
         TreeNode *right;
         TreeNode(int x) : val(x), left(NULL), right(NULL) {}
     };

void nextPermutation(vector<int>& nums) {
    auto idx = std::adjacent_find(nums.rbegin(), nums.rend(), std::greater<int>());
    if (idx++ == nums.rend()) { //因为idx指向的是需要交换处的后一个位子
        std::reverse(nums.begin(), nums.end());
        return;
    }
    auto s = std::find_if(nums.rbegin(), idx, [idx] (int a) { return a > *idx; });
    std::iter_swap(idx, s);
    std::reverse(idx.base(), nums.end());
}

int recursive(vector<int> &a, int l, int count, int up)
{
    if (a.size() == l + 1)
        return count + (a[l] <= up);
    else if (up < a[l])
        return recursive(a, l + 1, count, up);
    else
        return std::max(recursive(a, l + 1, count + 1, a[l]), recursive(a, l + 1, count, up));
}


// 对图进行遍历需要建立一个数组用来保存是否访问过，而树结构就没有这个问题
// 回溯法可以终止，可以参考剪格子

int n;

long long execute(vector<string>::iterator l, vector<string>::iterator r) { //执行迭代器l和r之间的指令
    static int curbase = -1;
    long long sum = 0;
    while (l < r) {
        long long v = atoll((*l).data() + 1);
        if ((*l)[0] == 'V') {
            if (v <= n)
                sum++;
            else if (curbase == (v - 1)/n + 1)
                sum++;
            else {
                curbase = (v - 1)/n + 1;
                sum += 2;
            }
            l++;
        } else if ((*l)[0] == 'R') {
            int count = 1;
            vector<string>::iterator index;
            for (index = l + 1; index < r; index++) {
                if ((*index)[0] == 'R')
                    count++;
                if ((*index)[0] == 'E')
                    count--;
                if (count == 0)
                    break;
            }
            sum += v * execute(l + 1, index) + execute(index + 1, r);
            break;
        }
    }
    return sum;
}

int array_value(vector<int> &v, int l , int r) {
    int sum = 0;
    while (l < r) {
        sum = sum * 10 + v[l++];
    }
    return sum;
}

int l;

int backtrack(int (*a)[3], int v, int n) {
    static int count = 0;
    if (n == l) {
        count++;
        return count;
    }
    for (int i = 0; i < 3; i++) {
        if (*(*a + i) >= v)
            backtrack(a + 1, *(*a + i), n + 1);
    }
    return count;
}

class Set {
public:
    void insert(int v) {
        for (auto i = s.begin(); i != s.end(); i++) {
            if (*i > v) {
                s.insert(i, v);
                return;
            }
            if (*i == v)
                return;
        }
        s.push_back(v);
    }
    void remove(int v) {
        s.erase(find(s.begin(), s.end(), v));
    }
    int size() {
        return s.size();
    }
    void print() {
        for (int i : s) {
            cout << i << " ";
        }
        cout << endl;
    }
    Set intersect(Set &t) {
        Set c;
        set_intersection(s.begin(), s.end(), t.s.begin(), t.s.end(), back_inserter(c.s));
        return c;
    }
    Set sunion(Set &t) {
        Set c;
        set_union(s.begin(), s.end(), t.s.begin(), t.s.end(), back_inserter(c.s));
        return c;
    }
    Set difference(Set &t) {
        Set c;
        set_difference(s.begin(), s.end(), t.s.begin(), t.s.end(), back_inserter(c.s));
        return c;
    }
    vector<int> s;
};

int main(void) {


    return 0;
}

/*
void backtrack(vector< vector<int> > &in, int m, int c, int sum, int goal, int deep) {
    for (int i = 0; i < in[0].size(); i++) {
        sum += in[deep][i];
        if (sum == goal) {
            v = c + i + 1;
            break;
        } else if (sum > goal || deep == m) //减枝
            continue;
        backtrack(in, m, c + i + 1,sum, goal, deep + 1);
    }
}

// 对图进行遍历需要建立一个数组用来保存是否访问过，而树结构就没有这个问题

int main(void) { //剪格子，但是不能减成环
    int m, n, sum;
    cin >> n >> m;
    queue<int> q;
    stack<int> s;
    vector< vector<int> > in(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> in[i][j];
            sum += in[i][j];
        }
    }

    int goal = sum/2;
    while (m > 0 && n > 0) {
        backtrack(in, m - 1, 0, 0, goal, 0);
        if (v != 0)
            break;

    }
    cout << v << endl;
    return 0;
}
 */

/*
    string s;
    vector<int> a;
    getline(cin, s);
    std::istringstream str(s);
    std::istream_iterator<int> in(str), eof;
    std::copy(in, eof, std::back_inserter(a));
    cout << std::max(recursive(a, 1, 1, a[0]), recursive(a, 1, 0, 30000)) << endl;
    int n = 0, max;
    while (a.size()) {
        max = a[0];
        a.erase(a.begin());
        for (int i = 0; i < a.size(); i++) {
            if (max >= a[i]) {
                max = a[i];
                a.erase(a.begin() + i);
                --i;
            }
        }
        n++;
    }
    cout << n << endl;
 */

/*
 * std::istringstream s("|abc|||def||ksd"); //split实现
    string a;
    while (std::getline(s, a, '|'))
        cout << a << endl;
 */

/*
 *     int n = 8;
    double tmp;
    std::vector<double> x;
    std::vector<double> y;
    for (int i = 0; i < 8; ++i) {
        cin >> tmp;
        if (i%2 == 0)
            x.push_back(tmp);
        else
            y.push_back(tmp);
    }

    if (std::max(x[0], x[1]) <= std::min(x[2], x[3]) || std::max(x[2], x[3]) <= std::min(x[0], x[1])) {
        printf("0.00");
        return 0;
    }
    if (std::max(y[0], y[1]) <= std::min(y[2], y[3]) || std::max(y[2], y[3]) <= std::min(y[0], y[1]))
    {
        printf("0.00");
        return 0;
    }

    cout << x[2] - x[1] << endl;
    cout << y[2] - y[1] << endl;

    sort(x.begin(),x.end());
    sort(y.begin(),y.end());
    cout << std::fixed << std::setprecision(2) <<  (y[2] - y[1]) * (x[2] - x[1]);
 */