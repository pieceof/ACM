//
// Created by bitwater on 18-4-17.
//

#include<bits/stdc++.h>

using namespace std;

map<string, int> mp;
string tmp;

int main(int argc, char *argv[]) {

    int n;
    while (cin >> n) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            cin >> tmp;
            if (mp.count(tmp)) mp[tmp]++;
            else mp[tmp] = 1;
            for (int i = 0; i < tmp.size(); ++i) {
                for (int j = i + 1; j < tmp.size(); ++j) {
                    if (tmp[i] == tmp[j]) continue;
                    swap(tmp[i], tmp[j]);
                    ans += mp[tmp];
                    swap(tmp[i], tmp[j]);
                }
            }
        }
        cout << ans << endl;
    };

    return 0;
}