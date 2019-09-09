//
// Created by 邓岩 on 2019/3/5.
//

// 最长增长子序列

# include <stdio.h>
# include <stdlib.h>
# include <string.h>


/*
 * 这里dp[i]保存的是以s[i]结尾的最长递增子序列
 * 可以这么写的原因是因为最后求的最长增长子序列中的结尾必然是这里面字符串中的其中一个
 * 那么以该字符结尾的最长公共子序列就可以变换成一个子问题，也就是以该字符串前一个字符结尾的最长子序列的长度是多少
 */

void recursion(char * s, int * prev, int n) {
    prev[n] != -1?recursion(s, prev, prev[n]):0;
    printf("%c", s[n]);
}


int LIS(char * s) {
    int prev[strlen(s)], i, maxarg = 0;
    int dp[strlen(s)], max = 0;
    for (i = 0; i < strlen(s); i++) {
        dp[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            if (s[i] >= s[j] && dp[i] <= dp[j]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
    }

    for (i = 0; i < strlen(s); i++) {
        if (dp[i] > max) {
            max = dp[i];
            maxarg = i;
        }
    }
    recursion(s, prev, maxarg);
    printf("\n");
    return max;
}

int main(void)
{
    char buf[100], str[100];
    scanf("%s", buf);
    printf("%d\n", LIS(buf));
    return 0;
}
