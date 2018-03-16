//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    int x;
    while (cin >> x) {
        x += 2;
        x -= 1;
        x %= 7;
        x += 1;
        cout << x << endl;
    }

    return 0;
}