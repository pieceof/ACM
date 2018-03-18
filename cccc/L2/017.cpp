//
// Created by bitwater on 18-3-18.
//

#include<bits/stdc++.h>

using namespace std;

const int SIZE = 100000;

int huo[SIZE];

int main(int argc, char *argv[]) {
    int n;
    while (scanf("%d", &n) != EOF) {
        int lcnt = 0, rcnt = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", huo + i);
            rcnt += huo[i];
        }
        sort(huo, huo + n);
        for (int i = 0; i < n / 2; ++i) {
            lcnt += huo[i];
            rcnt -= huo[i];
        }
        if (n % 2 == 0) {
            printf("Outgoing #: %d\n", n / 2);
            printf("Introverted #: %d\n", n / 2);
            printf("Diff = %d\n", rcnt - lcnt);
        } else {
            printf("Outgoing #: %d\n", n / 2 + 1);
            printf("Introverted #: %d\n", n / 2);
            printf("Diff = %d\n", rcnt - lcnt);
        }


    }


    return 0;
}