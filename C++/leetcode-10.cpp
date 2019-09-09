//
// Created by 邓岩 on 2018/11/25.
//

# include <iostream>
# include <string>

using std::cout;
using std::endl;

int main(void)
{
     std::string s = "aaa";
    std::string p = "a*a";
    char tmp;
    auto bs = s.begin();
    auto bp = p.begin();
    if(*bp == '*')
        return 0;
    while(bp != p.end())
    {
        if(*bp != '*')
        {
            tmp = *bp;
            if(tmp == '.')
                bs++;
            else if(tmp == *bs)
                bs++;
            else if(bp != p.end() && *(++bp) == '*')
                ;
            else
                return 0;
        }
        else if(tmp == '.')
        {
            if(bp == p.end() - 1)
                return 1;
            else
                return 0;
        }
        else {
            while (*bs == tmp) {
                bs++;
                if (bs == s.end() && bp + 1 != p.end());

            }
        }
        bp++;
        if(bs > s.end())
            return 0;
    }
    if(bs == s.end())
        cout << "ok" << endl;
        //return 0;
    else
        cout << "no"  << endl;
        //return -1;

}
