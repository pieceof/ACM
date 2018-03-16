//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {

    int cnt = 0;
    int x;
    int ans = -1;
    while (cin >> x) {
        cnt++;
        if (ans == -1 && x == 250)ans = cnt;
    }
    cout << ans << endl;
    return 0;
}