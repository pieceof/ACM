//
// Created by bitwater on 18-3-25.
//

#include<bits/stdc++.h>

typedef long long llt;
using namespace std;

const int SIZE = 100000 + 200;
int fa[SIZE];
int dedao[SIZE];
double beishu[SIZE];
int depth[SIZE];
map<int, vector<int> > mp;


int dfs(int node, int d) {
    depth[node] = d;
    for (auto i : mp[node]) {
        dfs(i, d + 1);
    }
}

int main() {
    int n;
    double z, r;
    scanf("%d%lf%lf", &n, &z, &r);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);
        if (k == 0) {
            dedao[cnt] = i;
            scanf("%lf", beishu + cnt);
            cnt++;
        } else {
            while (k--) {
                int tmp;
                scanf("%d", &tmp);
                mp[i].push_back(tmp);
                fa[tmp] = i;
            }
        }
    }
    dfs(0, 0);
    double ans = 0;
    for (int i = 0; i < cnt; ++i) {
        int son = dedao[i];
        double sum = z;
        sum *= pow((100 - r) / 100, depth[son]);
        sum *= beishu[i];
        ans += sum;
    }
    printf("%d\n", (int) ans);
    return 0;
}