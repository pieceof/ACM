//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int just(double a, double b) {
    a -= 100;
    a *= 0.9;
    b *= 0.5;
    double cha = a * 0.1;
    if (abs(b - a) < cha)return 0;
    if (b - a >= cha) return 1;
    if (b - a <= cha) return -1;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    while (n--) {
        double a, b;
        scanf("%lf%lf", &a, &b);
        if (just(a, b) == 0)
            printf("You are wan mei!\n");
        if (just(a, b) < 0)
            printf("You are tai shou le!\n");
        if (just(a, b) > 0)
            printf("You are tai pang le!\n");

    }

    return 0;
}