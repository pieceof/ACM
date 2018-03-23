//
// Created by bitwater on 18-3-23.
//

//#include"../../headers.h"

#include "bits/stdc++.h"

using namespace std;

map<string, int> nameId;
vector<string> nameCache;
int nameCnt;

void init1() {
    nameId.clear();
    nameCache.clear();
    nameCnt = 0;
}

int getNameId(string const &name) {
    if (nameId.count(name)) return nameId[name];
    nameCache.push_back(name);
    return nameId[name] = nameCnt++;
}

const int SIZE = 10000;
int fa[SIZE];

void init2() {
    for (int i = 0; i < SIZE; ++i)fa[i] = i;
}

int findAncestors(int x) {
    return fa[x] == x ? x : fa[x] = findAncestors(fa[x]);
}

void unite(int x, int y) {
    if (nameCache[findAncestors(x)] < nameCache[findAncestors(y)]) swap(x, y);
    fa[findAncestors(x)] = findAncestors(y);
}

int area[SIZE];
int houseCnt[SIZE];
int partyCnt[SIZE];

void init() {
    init1();
    init2();
    memset(area, 0, sizeof(area));
    memset(houseCnt, 0, sizeof(houseCnt));
    memset(partyCnt, 0, sizeof(partyCnt));
}

string nam1, nam2, nam3, nams;

int cmp(int x, int y) {
    double a = (double) area[x] / partyCnt[x];
    double b = (double) area[y] / partyCnt[y];
    if (a != b) return a > b;
    return nameCache[x] < nameCache[y];
}

vector<int> party;

int main() {
    int n;
    scanf("%d", &n);
    init();
    for (int i = 0; i < n; ++i) {
        int scnt;
        cin >> nam1 >> nam2 >> nam3 >> scnt;
        int n1id = getNameId(nam1);
        if (nam2 != "-1")
            unite(n1id, getNameId(nam2));
        if (nam3 != "-1")
            unite(n1id, getNameId(nam3));
        while (scnt--) {
            cin >> nams;
            unite(n1id, getNameId(nams));
        }
        int a, b;
        cin >> a >> b;
        houseCnt[n1id] += a;
        area[n1id] += b;

    }
    for (int i = 0; i < nameCache.size(); ++i) {
        findAncestors(i);

        if (fa[i] == i)
            party.push_back(i);
        else {
            houseCnt[fa[i]] += houseCnt[i];
            area[fa[i]] += area[i];
        }
        partyCnt[fa[i]]++;
    }
    sort(party.begin(), party.end(), cmp);
    cout << party.size() << endl;
    for (auto i : party) {
        cout << fixed << setprecision(3)
             << nameCache[i] << " "
             << partyCnt[i] << " "
             << (double) houseCnt[i] / partyCnt[i] << " "
             << (double) area[i] / partyCnt[i] << endl;
    }
    return 0;
}