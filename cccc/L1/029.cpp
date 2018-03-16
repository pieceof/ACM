//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    int x;
    while (scanf("%d", &x) != EOF) {
        double n = x;
        n -= 100;
        n *= 0.9;
        n *= 2;
        printf("%.1f\n", n);
    }
    return 0;
}