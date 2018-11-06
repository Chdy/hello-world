//
// Created by 邓岩 on 2018/11/3.
//

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//动态规划处理矩阵链乘法

void print_optimal_parens(int (*s)[7], int i, int j) //这里的7为二维数组s的列数
{
    if (i == j)
        printf("A%d", i);
    else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

void matrix_chain_order(const int * p, int n)
{
    int j;
    int (*m)[n + 1] = calloc((n + 1) * (n + 1), sizeof(int));
    int (*s)[n + 1] = calloc((n + 1) * (n + 1), sizeof(int));
    for (int l = 2; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            j = i + l - 1;
            m[i][j] = INT32_MAX;
            for (int k = i; k < j; ++k) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    for (int i1 = 0; i1 < n + 1; ++i1) {
        for (int i = 0; i < n + 1; ++i) {
            printf("%5d ", m[i1][i]);
        }
        for (int i = 0; i < n + 1; ++i) {
            printf("%5d ", s[i1][i]);
        }
        printf("\n");
    }
    print_optimal_parens(s, 1, 6);
    free(m);
    free(s);
}

int main(void)
{
    int p[] = {30, 35, 15, 5, 10, 20, 25};
    //有六个矩阵，p[0]存放着第一个矩阵的行，其余的p[i]表示第i个矩阵的列数
    matrix_chain_order(p, 6);
}