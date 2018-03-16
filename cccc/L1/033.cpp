//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int dif(int x) {
    int nub[10] = {0};
    for (int i = 0; i < 4; ++i) {
        nub[x % 10]++;
        x  /= 10;
    }
    int cnt = 0;
    for(int i = 0;i < 10;++i){
        if(nub[i])cnt++;
    }
    return  cnt;
}

int main(int argc, char *argv[]) {
    int x, n;
    while (scanf("%d%d", &x, &n) != EOF) {
        int lx = x;
        while (1) {
            if (dif(x) == n) {
                printf("%d %04d\n", x - lx, x);
                break;
            } else
                x++;

        }

    }
    return 0;
}