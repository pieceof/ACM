//
// Created by bitwater on 18-3-18.
//

#include<bits/stdc++.h>

using namespace std;

int nub[52][11000];

int len[52];

map<pair<int, int>, double> mp;

int tmp[22000];

double cal(int a, int b) {
    int idx = 0;
    for (int i = 0; i < len[a]; ++i)
        tmp[idx++] = nub[a][i];
    for (int i = 0; i < len[b]; ++i) {
        tmp[idx++] = nub[b][i];
    }
    sort(tmp, tmp + len[a] + len[b]);
    double ucnt = unique(tmp, tmp + len[a] + len[b]) - tmp;
    return (len[a] + len[b] - ucnt) / ucnt;
}


int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int m;
        scanf("%d", &m);
        len[i] = m;
        for (int j = 0; j < m; ++j) {
            scanf("%d", nub[i] + j);
        }
        sort(nub[i], nub[i] + m);
        len[i] = unique(nub[i], nub[i] + m) - nub[i];

    }
    int k;
    scanf("%d", &k);
    while (k--) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%.2f%%\n", cal(a-1, b-1) * 100);
    }

    return 0;
}