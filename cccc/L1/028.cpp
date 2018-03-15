//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>

using namespace std;
typedef long long llt;

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    while (n--) {
        llt x;
        scanf("%lld", &x);
        if ( x == 1 ) {
            printf("No\n");
            continue;
        }
        bool isok = 0;
        for (llt i = 2;  i * i <= x; ++i) {
            if (x % i == 0) {
                isok = 1;
                break;
            }
        }
        if (isok) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}