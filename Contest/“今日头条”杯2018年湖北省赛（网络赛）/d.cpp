//
// Created by bitwater on 18-4-15.
//

#include<bits/stdc++.h>

using namespace std;
const int SIZE = 5000000;
int ans[SIZE] = {0};
char op[20];

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int idx = 1;
        int x, xo = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%s%d", op, &x);
            if (op[1] == 'o') {
                xo ^= x;
                ans[idx] = xo;
            } else {
                xo = ans[x];
                ans[idx] = xo;
            }
            printf("%d\n", ans[idx++]);
        }
    }
    return 0;
}