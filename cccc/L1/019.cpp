//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    int x, y;
    while (scanf("%d%d", &x, &y) != EOF) {
        int tx = x, ty = y;
        int n, a, b, c, d;
        scanf("%d",&n);
        while (n--) {
            scanf("%d%d%d%d", &a, &b, &c, &d);
            int sum = a + c;
            if (x < 0 || y < 0)continue;
            if (b == sum && d != sum)x--;
            if (b != sum && d == sum)y--;
        }
        if (x < 0)
            printf("A\n%d\n", ty - y);
        if (y < 0)
            printf("B\n%d\n", tx - x);
    }
    return 0;
}