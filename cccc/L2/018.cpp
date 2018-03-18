//
// Created by bitwater on 18-3-18.
//

#include<bits/stdc++.h>

using namespace std;
const int SIZE = 100000;

struct Poly {
    double fac[SIZE]; // 系数
    int n;          // 最大的阶

    // 返回余多项式
    Poly div(Poly const &b) {
        Poly c;
        c.n = n - b.n; // 余多项式的最大阶
        for (int i = n; i >= b.n; --i) {

            int exp = i - b.n;  // 当前计算的余数的阶数
            double t = fac[i] / b.fac[b.n]; // 阶数的系数
            c.fac[exp] = t;

            // 更新 被除多项式
            int ti = i;
            for (int j = b.n; j >= 0; --j)
                x[ti--] -= b.fac[j] * t;
        }
        return c;
    }

    void print() {
        int nn = n;
        n = 0;
        for (int j = nn; j >= 0; --j)
            if (fabs(x[j]) >= 0.05)
                n++;

        if (n == 0)printf("0 0 0.0\n");
        else {
            printf("%d", n);
            for (int j = nn; j >= 0; --j)
                if (fabs(x[j]) >= 0.05)
                    printf(" %d %.1f", j, x[j]);
            printf("\n");
        }
    }
};

int main(int argc, char *argv[]) {
    int n, m;
    Poly a, b;
    while (scanf("%d", &n) != EOF) {
        int x, y;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &x, &y);
            a.x[x] = y;
            if (i == 0) a.n = x; // 保存最大的阶数
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            b.x[x] = y;
            if (i == 0) b.n = x; // 保存最大的阶数
        }
        Poly c = a.div(b);
        c.print();
        a.print();
    }
    return 0;
}