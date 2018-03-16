//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    int n;
    while (cin >> n) {
        while (n--) {
            string name;
            int x, y;
            cin >> name >> x >> y;
            if (x < 15 || x > 20 || y < 50 || y > 70) cout << name << endl;

        }
    }

    return 0;
}