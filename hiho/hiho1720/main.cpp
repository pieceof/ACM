//
// Created by bitwater on 18-4-10.
//

//
// Created by bitwater on 18-3-14.
//
#include<bits/stdc++.h>

using namespace std;

set<int> nub;
int cnt[10];

int main() {
    int p, q;
    while (cin >> p >> q) {
        memset(cnt, 0, sizeof(cnt));
        nub.clear();
        while (!nub.count(p)) {
            nub.insert(p);
            p *= 10;
            cnt[p / q]++;
            p %= q;
        }
        for (int i = 0; i < 10; ++i)
            if (cnt[i])
                cout << i;
        cout << endl;
    }
    return 0;
}
