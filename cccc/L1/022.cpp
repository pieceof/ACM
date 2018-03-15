//
// Created by bitwater on 18-3-15.
//


#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    int n;

    while (scanf("%d", &n) != EOF) {

        int x;
        int a = 0, b = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &x);
            if (x % 2 == 0) a++;
            else b++;
        }
        printf("%d %d\n",b,a);
    }


    return 0;
}