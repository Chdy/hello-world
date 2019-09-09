//
// Created by 邓岩 on 2018/11/3.
//

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

void LCS_PRINT(char ** t, char * y, int i, int j)
{
    int n = strlen(y);
    char (*b)[n + 1] = t;
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == '\\') {
        LCS_PRINT(t, y, i - 1, j - 1);
        printf("%c", y[j - 1]);
    } else if (b[i][j] == '|') {
        LCS_PRINT(t, y, i - 1, j);
    } else {
        LCS_PRINT(t, y, i, j - 1);
    }
}

void LCS_LENGTH(char * x, char * y)
{
    int len1 = strlen(x);
    int len2 = strlen(y);
    char (*b)[len2 + 1] = calloc((len1 + 1) * (len2 + 1), sizeof(char));
    int (*c)[len2 + 1] = calloc((len1 + 1) * (len2 + 1), sizeof(int));
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (*(x + i - 1) == *(y + j - 1)) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '\\';
            } else if (c[i - 1][j] >= c[i][j - 1]) { //c[i][j]，c[i - 1][j]，c[i][j - 1]是相邻的，也就是说箭头指向有较大最大LCS的方向
                c[i][j] = c[i - 1][j];
                b[i][j] = '|';
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = '-';
            }
        }
    }
    /*for (int i = 0; i <= len1; ++i) {
        for (int j = 0; j <= len2; ++j) {
            printf("%d ", c[i][j]);
        }
        for (int j = 0; j <= len2; ++j) {
            printf("%c ", b[i][j]);
        }
        printf("\n");
    }*/
    LCS_PRINT(b, y, len1, len2);
}

int main(void)
{
    char * file1 = "/Users/dengyan/exam.c";
    char * file2 = "/Users/dengyan/exam";
    struct stat stat1;
    stat(file1, &stat1);
    char * x = (char *)malloc(stat1.st_size + 1);
    int fdx = open(file1, O_RDONLY);
    read(fdx, x, stat1.st_size);
    x[stat1.st_size] = 0;
    stat(file2, &stat1);
    char * y = (char *)malloc(stat1.st_size + 1);
    int fdy = open(file2, O_RDONLY);
    read(fdy, y, stat1.st_size);
    y[stat1.st_size] = 0;

    //char x[100] = "ABCBDAB";
    //char y[100] = "BDCABA";
    LCS_LENGTH(x, y);
}
