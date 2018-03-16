//
// Created by bitwater on 18-3-16.
//


#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {

    char ch[2];
    double x;
    int n;
    cin >> n;
    while (n--) {

        cin >> ch >> x;
        if (*ch == 'F') {
            printf("%.2f\n", x * 1.09);
        } else {
            printf("%.2f\n", x / 1.09);
        }

    }
    return 0;
}