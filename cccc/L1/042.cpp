//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    int x, y, z;
    while (scanf("%d-%d-%d", &x, &y, &z) != EOF) {
        printf("%04d-%02d-%02d\n", z, x, y);
    }

    return 0;
}