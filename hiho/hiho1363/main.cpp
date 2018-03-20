//
// Created by bitwater on 18-3-20.
//
#include<bits/stdc++.h>

using namespace std;
const double eps = 1e-9;

const int SIZE = 5000;
double a[SIZE][SIZE];//增广矩阵
double x[SIZE];//解的数目
bool free_x[SIZE];///判断是不是自由变元
int equ, var;//equ个方程 var个变量

// 高斯消元法解方程组(Gauss-Jordan elimination).(0表示无解，1表示唯一解，大于1表示无穷解，并返回自由变元的个数)
int Gauss() {
//    equ=n,var=n;//多少个方程，多少个变量
    int i, j, k;
    int max_r; // 当前这列绝对值最大的行.
    int col; // 当前处理的列.
    double temp;
    int free_x_num;
    int free_index;
    // 转换为阶梯阵.
    col = 0; // 当前处理的列.
    fill(free_x, free_x + var + 1, 1);
    for (k = 0; k < equ && col < var; k++, col++) {
        max_r = k;
        for (i = k + 1; i < equ; i++)
            if (fabs(a[i][col]) - fabs(a[max_r][col]) > eps)
                max_r = i;
        if (max_r != k) // 与第k行交换.
            for (j = k; j < var + 1; j++)
                swap(a[k][j], a[max_r][j]);
        if (fabs(a[k][col]) < eps) { // 说明该col列第k行以下全是0了，则处理当前行的下一列.
            k--;
            continue;
        }
        for (i = k + 1; i < equ; i++) // 枚举要删去的行.
            if (fabs(a[i][col]) > eps) {
                temp = a[i][col] / a[k][col];
                for (j = col; j < var + 1; j++) {
                    a[i][j] = a[i][j] - a[k][j] * temp;
                }
            }
    }
    for (i = k; i < equ; i++)
        if (fabs(a[i][col]) > eps)
            return 0;
    if (k < var) {
        for (i = k - 1; i >= 0; i--) {
            free_x_num = 0;
            for (j = 0; j < var; j++)
                if (fabs(a[i][j]) > eps && free_x[j])
                    free_x_num++, free_index = j;
            if (free_x_num > 1) continue;
            temp = a[i][var];
            for (j = 0; j < var; j++)
                if (fabs(a[i][j]) > eps && j != free_index)
                    temp -= a[i][j] * x[j];
            x[free_index] = temp / a[i][free_index];
            free_x[free_index] = 0;
        }
        return var - k;
    }

    for (i = var - 1; i >= 0; i--) {
        temp = a[i][var];
        for (j = i + 1; j < var; j++)
            if (fabs(a[i][j]) > eps)
                temp -= a[i][j] * x[j];
        x[i] = temp / a[i][i];
    }
    return 1;
}

double mata[500][500];

int main() {
    int h, w, d;
    scanf("%d%d%d", &h, &w, &d);
    var = d * d;
    equ = (h - d + 1) * (w - d + 1);

    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            scanf("%lf", &mata[i][j]);

    int idx = 0;
    for (int i = 0; i < h - d + 1; ++i)
        for (int j = 0; j < w - d + 1; ++j)
            scanf("%lf", &a[idx++][var]);
    for (int r = 0; r < equ; ++r) {
        for (int c = 0; c < var; ++c) {
            a[r][c] = mata[r / (w - d + 1) + c / d][(c % d) + r % (w - d + 1)];
        }
    }
    int ret = Gauss();
    idx = 0;
    for (int i = 0; i < var; ++i)
        if (fabs(x[i]) < eps)x[i] = 0;
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < d - 1; ++j)printf("%.0f ", x[idx++]);
        printf("%.0f\n", x[idx++]);
    }
    return 0;
}