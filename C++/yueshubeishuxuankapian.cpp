//
// Created by 邓岩 on 2019/5/22.
//

/*
 * 约数倍数选卡片
问题描述
　　闲暇时，福尔摩斯和华生玩一个游戏：
　　在N张卡片上写有N个整数。两人轮流拿走一张卡片。要求下一个人拿的数字一定是前一个人拿的数字的约数或倍数。例如，某次福尔摩斯拿走的卡片上写着数字“6”，则接下来华生可以拿的数字包括：
　　1，2，3, 6，12，18，24 ....
　　当轮到某一方拿卡片时，没有满足要求的卡片可选，则该方为输方。
　　请你利用计算机的优势计算一下，在已知所有卡片上的数字和可选哪些数字的条件下，怎样选择才能保证必胜！
　　当选多个数字都可以必胜时，输出其中最小的数字。如果无论如何都会输，则输出-1。
输入格式
　　输入数据为2行。第一行是若干空格分开的整数（每个整数介于1~100间），表示当前剩余的所有卡片。
　　第二行也是若干空格分开的整数，表示可以选的数字。当然，第二行的数字必须完全包含在第一行的数字中。
输出格式
　　程序则输出必胜的招法！！
样例输入
2 3 6
3 6
样例输出
3
样例输入
1 2 2 3 3 4 5
3 4 5
样例输出
4
 */


# include <iostream>
# include <vector>
# include <iterator>
# include <sstream>
# include <string>
# include <algorithm>

using namespace std;

int all[101];
vector<int> valid[101];

int ax;

void getvalid() {
    for (int v = 1; v <= ax; v++) {
        if (all[v] != 0) {
            all[v]--;
            for (int i = 1; i <= ax; i++) {
                if (all[i] != 0 && (i%v == 0 || v%i == 0))
                    valid[v].push_back(i);
            }
            all[v]++;
        }
    }
}

int ans = -1;

int minimax(vector<int> &x, bool player) {
    for (int i = x.size() - 1; i >= 0; i--) { //必须反序输出速度才够，原因应该是由于alpha-beta算法来说，每一步的选择越优，那么就可以进行越多的减枝，因为大的数的倍数和约数相对会少很多，所以优先选择大的数会有更好的减枝效果
        if (all[x[i]]) {
            all[x[i]]--;
            if (minimax(valid[x[i]], !player) == player) {
                ans = x[i];
                all[x[i]]++;
                return player;
            }
            all[x[i]]++;
        }
    }
    return !player;
}

int main(void)
{
    while (1) {
        int i;
        scanf("%d", &i);
        ax = max(i, ax);
        all[i]++;
        if (getchar() == '\n')
            break;
    }

    while (1) {
        int i;
        scanf("%d", &i);
        valid[0].push_back(i);
        if (getchar() == '\n')
            break;
    }

    getvalid();

    reverse(valid[0].begin(), valid[0].end()); //同样也要反序，这一行花了我2个小时才找出来原因

    if (minimax(valid[0], 1) == 1)
        cout << ans << endl;
    else
        cout << -1 << endl;
    return 0;
}


/* 仍然超时严重，需要想办法增加速度
# include <iostream>
# include <vector>
# include <iterator>
# include <sstream>
# include <string>
# include <algorithm>

using namespace std;

vector<int> getvalid(vector<int> &all, int v) {
    vector<int> ret;
    for (int i = 0; i < all.size(); i++) {
        if (all[i]%v == 0 || v%all[i] == 0)
            ret.push_back(all[i]);
    }
    return ret;
}

int ans = -1;

int minimax(vector<int> &all, vector<int> &valid, bool player) {
    for (int i = 0; i < valid.size(); i++) {
        vector<int> tmp = all;
        tmp.erase(find(tmp.begin(), tmp.end(), valid[i]));
        vector<int> tmpvalid = getvalid(tmp, valid[i]);
        if (minimax(tmp, tmpvalid, !player) == player) {
            ans = valid[i];
            return player;
        }
    }
    return !player;
}

int main(void)
{
    vector<int> all;
    vector<int> valid;
    string a;
    getline(cin, a);
    istringstream s(a);
    copy(istream_iterator<int>(s), istream_iterator<int>(), back_inserter(all));
    getline(cin, a);
    istringstream b(a);
    copy(istream_iterator<int>(b), istream_iterator<int>(), back_inserter(valid));
    if (minimax(all, valid, 1) == 1)
        cout << ans << endl;
    else
        cout << -1 << endl;
    return 0;
}
*/

/*
// 从下面这个代码可以让我改到了上面那个，加深了我对minimax的理解
 # include <iostream>
# include <vector>
# include <iterator>
# include <sstream>
# include <string>
# include <algorithm>

using namespace std;

vector<int> getvalid(vector<int> &all, int v) {
    vector<int> ret;
    for (int i = 0; i < all.size(); i++) {
        if (all[i]%v == 0 || v%all[i] == 0)
            ret.push_back(all[i]);
    }
    return ret;
}

int ans = -1;

int minimax(vector<int> all, vector<int> valid, bool player) {
    if (valid.empty())
        return !player;

    if (player == 1) { //如果轮到我下子
        for (int i = 0; i < valid.size(); i++) {
            vector<int> tmp = all;
            tmp.erase(find(tmp.begin(), tmp.end(), valid[i]));
            vector<int> tmpvalid = getvalid(tmp, valid[i]);
            if (minimax(tmp, tmpvalid, !player) == player) {
                ans = valid[i];
                return player;
            }
        }
        return !player;
    } else { //player == 0
        bool ret = 1;
        for (int i = 0; i < valid.size(); i++) {
            vector<int> tmp = all;
            tmp.erase(find(tmp.begin(), tmp.end(), valid[i]));
            vector<int> tmpvalid = getvalid(tmp, valid[i]);
            ret &= minimax(tmp, tmpvalid, !player);
        }
        if (ret) //这里可以的一个改进是对于min来说，只要他现在能下的某一步能赢，那么这步的前一步对于max来说就是不可取的，所以可以改成和上面一摸一样的形式，而不是需要计算每一步都是min方输，只需要得到一个是max赢即可，也就是达到了剪枝的效果，然后我发现两边的代码居然一摸一样，那么再次改进。甚至觉得神奇
            return !player;
        else
            return player;
    }
}

int main(void)
{
    vector<int> all;
    vector<int> valid;
    string a;
    getline(cin, a);
    istringstream s(a);
    copy(istream_iterator<int>(s), istream_iterator<int>(), back_inserter(all));
    getline(cin, a);
    istringstream b(a);
    copy(istream_iterator<int>(b), istream_iterator<int>(), back_inserter(valid));
    if (minimax(all, valid, 1) == 1)
        cout << ans << endl;
    else
        cout << -1 << endl;
    return 0;
}
 */