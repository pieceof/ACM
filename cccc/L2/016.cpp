//
// Created by bitwater on 18-3-22.
//

#include<bits/stdc++.h>

using namespace std;

map<string, string> fa, ma;
map<string, string> sex;
string a, b, c, ch;


void dfs(string const &node, int depth, set<string> &st) {
    if (depth <= 0) return;
    if (fa.count(node) && fa[node] != "-1") {
        st.insert(fa[node]);
        dfs(fa[node], depth - 1, st);
    }
    if (ma.count(node) && ma[node] != "-1") {
        st.insert(ma[node]);
        dfs(ma[node], depth - 1, st);
    }
}

set<string> st1, st2, si;

bool just(string const &a, string const &b) {

    st1.clear();
    st2.clear();
    si.clear();
    dfs(a, 4, st1);
    dfs(b, 4, st2);
    set_intersection(st1.begin(), st1.end(), st2.begin(), st2.end(),
                     inserter(si, si.begin()));
    return si.size() == 0;

}

int main(int argc, char *argv[]) {
    int n;
    cin >> n;
    while (n--) {
        cin >> a >> ch >> b >> c;
        fa[a] = b;
        ma[a] = c;
        sex[a] = ch;
        sex[b] = "M";
        sex[c] = "F";

    }
    int m;
    cin >> m;
    while (m--) {
        cin >> a >> b;
        if (sex[a] == sex[b]) {
            cout << "Never Mind" << endl;
        } else {
            if (just(a, b)) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    return 0;
}