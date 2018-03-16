//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {

    int x;
    while (scanf("%d", &x) != EOF) {
        int ans = 1;
        int len = 0;
        while (ans < x)ans = ans * 10 + 1, len++;
        for (; ans;) {
            int t = ans/x;
            printf("%d", ans / x);
            len++;
            ans %= x;
            if( ans == 0 )break;
            ans = ans * 10 + 1;
        }
        printf(" %d\n", len);
    }

    return 0;
}