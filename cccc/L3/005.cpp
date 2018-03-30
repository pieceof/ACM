//
// Created by bitwater on 18-3-30.
//

#include<bits/stdc++.h>

using namespace std;
int n, m, k, d;
const int SIZE = 1050;

struct _t {
    int v, w;

    _t(int vv, int ww) : v(vv), w(ww) {};
};

vector<_t> vt[SIZE];

void add(int a, int b, int c) {
//    printf("(%d %d %d)\n", a, b, c);
    vt[a].push_back(_t(b, c));
    vt[b].push_back(_t(a, c));
}

int D[SIZE];
bool flag[SIZE];

void spfa(int s) {
    fill(D, D + n + m, INT_MAX);
    fill(flag, flag + n + m, 0);
    queue<int> q;
    q.push(s);
    D[s] = 0;
    flag[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        flag[u] = false;
        for (auto to : vt[u]) {
            int v = to.v;
            if (D[u] < D[v] - to.w) {
                D[v] = D[u] + to.w;
                if (!flag[v]) {
                    flag[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}


int main() {
    for (int i = 0; i < SIZE; ++i) vt[i].clear();
    scanf("%d%d%d%d", &n, &m, &k, &d);
    char ch1[5], ch2[5];
    int a, b, c;
    for (int i = 0; i < k; ++i) {
        scanf("%s%s%d", ch1, ch2, &c);
        if (*ch1 == 'G')sscanf(ch1, "G%d", &a);
        else {
            sscanf(ch1, "%d", &a);
            a += m;
        }
        if (*ch2 == 'G')sscanf(ch2, "G%d", &b);
        else {
            sscanf(ch2, "%d", &b);
            b += m;
        }
        a--, b--;
        add(a, b, c);
    }
    int ansid = -1;
    double ansd = 0, sum = INT_MIN;
    for (int i = 0; i < m; ++i) {
        spfa(i);
        double mind = INT_MAX;
        double tmp_sum = 0;
        for (int j = m; j < n + m; ++j) {
            if (D[j] > d) {
                mind = -1;
                break;
            }
            if( mind > D[j] ) mind = D[j];
            tmp_sum += D[j];
        }
        if (mind == -1)continue;
        if (ansd < mind || (ansd == mind && sum > tmp_sum)) {
            ansd = mind;
            sum = tmp_sum;
            ansid = i;
        }
    }
    if (ansid == -1)
        printf("No Solution\n");
    else
        printf("G%d\n%.1lf %.1lf\n", ansid + 1, ansd, sum / n);
    return 0;
}