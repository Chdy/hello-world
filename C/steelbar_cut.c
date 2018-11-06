//
// Created by 邓岩 on 2018/11/3.
//

# include <stdio.h>
# include <stdlib.h>
#include <string.h>

//动态规划切钢条

void bottom_to_up(int n) //自底向上法
{
    int rr[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int * r = (int *)calloc(n + 1, sizeof(int));
    memcpy(r, rr, sizeof(int) * 11);
    int * s = (int *)calloc(n + 1, sizeof(int));

    for (int i = 1; i < n+1; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (r[i] < r[j] + r[i - j]) {
                r[i] = r[j] + r[i - j];
                s[i] = j;
            }
        }
    }
    printf("  长度: ");
    for (int k = 0; k < n + 1; ++k) {
        printf("%3d ", k);
    }
    printf("\n  价格: ");
    for (int k = 0; k < n + 1; ++k) {
        printf("%3d ", r[k]);
    }
    printf("\n  切割: ");
    for (int k = 0; k < n + 1; ++k) {
        printf("%3d ", s[k]);
    }
}

int up_to_bottom(int n, int * rr, int * r) //带备忘的自顶向下法
{
    if (r[n] > 0)
        return r[n];
    for (int i = 1; i < n + 1; ++i) {
        if (r[n] < rr[i] + up_to_bottom(n - i, rr, r)) {
            r[n] = rr[i] + up_to_bottom(n - i, rr, r);
        }
    }
    return r[n];
}

int main(void)
{
    int n ;
    printf("请输入钢条长度: ");
    scanf("%d", &n);
    int t[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int * rr = (int *)calloc(n + 1, sizeof(int));
    memcpy(rr, t, sizeof(int) * 11);
    int * r = (int *)calloc(n + 1, sizeof(int));
    printf("%d", up_to_bottom(n, rr, r));
}