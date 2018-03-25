//
// Created by bitwater on 18-3-25.
//

#include<bits/stdc++.h>

using namespace std;

int idx[30];

vector<string> vt;

char str[1000];
string word;

int cmp(string const &a, string const &b) {
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (idx[a[i] - 'a'] != idx[b[j] - 'a']) {
            return idx[a[i] - 'a'] < idx[b[j] - 'a'];
        } else i++, j++;
    }
    if (i == a.size()) return 1;
    else return 0;
}

int main() {
    int n;
    cin >> n >> str;

    int len = strlen(str);
    for (int i = 0; i < len; ++i)
        idx[str[i] - 'a'] = i;

    while (n--) {
        cin >> word;
        vt.push_back(word);
    }
    sort(vt.begin(), vt.end(), cmp);
    for (auto i : vt) cout << i << endl;


    return 0;
}