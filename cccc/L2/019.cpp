//
// Created by bitwater on 18-3-19.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    set<string> names, ans;
    int n, m;
    string name;
    cin >> n;
    while (n--) {
        cin >> name;
        names.insert(name);
    }
    cin >> m;
    vector<string> vt;
    double cnt[20000];
    double sum = 0, x;
    for (int i = 0; i < m; ++i) {
        cin >> name >> x;
        cnt[i] = x;
        sum += x;
        vt.push_back(name);
    }
    double p = sum / m;
    for (int i = 0; i < m; ++i) {
        if (cnt[i] > p && 0 == names.count(vt[i])) {
            ans.insert(vt[i]);
        }
    }
    for (auto i: ans) {
        cout << i << endl;
    }
    if (ans.size() == 0)
        cout << "Bing Mei You" << endl;
    return 0;
}