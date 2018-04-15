//
// Created by bitwater on 18-4-15.
//

#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;
#define V 200005
#define E 500005
struct edge {
    int to, next;
} Edge[E], newEdge[E];
int head[V], e, n;
int newhead[V];
int belong[V], low[V], dfn[V], scc, cnt;
int S[V], top;
bool vis[V];

int addedge(int u, int v) {
    Edge[e].to = v;
    Edge[e].next = head[u];
    head[u] = e++;
    return 0;
}

int newaddedge(int u, int v) {
//    cout << u << " " << v<< endl;

    newEdge[e].to = v;
    newEdge[e].next = newhead[u];
    newhead[u] = e++;
    return 0;
}

void tarjan(int u) {
    int v;
    dfn[u] = low[u] = ++cnt;
    S[top++] = u;
    vis[u] = true;
    for (int i = head[u]; i != -1; i = Edge[i].next) {
        v = Edge[i].to;
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = low[u] < low[v] ? low[u] : low[v];
        } else if (vis[v] && low[u] > dfn[v])
            low[u] = dfn[v];
    }
    if (dfn[u] == low[u]) {
        ++scc;
        do {
            v = S[--top];
            vis[v] = false;
            belong[v] = scc;
        } while (u != v);
    }

}

int solve() {
    scc = top = cnt = 0;
    memset(dfn, 0, sizeof(int) * (n + 1));
    memset(vis, false, sizeof(bool) * (n + 1));
    for (int u = 1; u <= n; ++u)
        if (dfn[u] == 0)
            tarjan(u);
    return scc;
}

int cntfenliang[V];


int dp[V];
int wei[V];

int dfs(int vt) {
    if (dp[vt])
        return dp[vt];
//    cout << " " << vt << endl;
    int ret = 0;
    for (int i = newhead[vt]; i != -1; i = newEdge[i].next) {
        int v = newEdge[i].to;
        ret = max(ret, dfs(v));
    }
    return dp[vt] = ret + wei[vt];

}

namespace fastIo {
    template<typename T>
    inline bool scan_d(T &ret) {
        char c;
        int sgn;
        if (c = getchar(), c == EOF) return 0; //EOF
        while (c != '-' && (c < '0' || c > '9'))
            if ((c = getchar()) == EOF) return 0;
        sgn = (c == '-') ? -1 : 1;
        ret = (c == '-') ? 0 : (c - '0');
        while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
        ret *= sgn;
        return 1;
    }

    template<typename T>
    void print(T x) {
        static char s[33], *s1;
        s1 = s;
        if (!x) *s1++ = '0';
        if (x < 0) putchar('-'), x = -x;
        while (x) *s1++ = (x % 10 + '0'), x /= 10;
        while (s1-- != s) putchar(*s1);
    }

    template<typename T>
    void println(T x) {
        print(x);
        putchar('\n');
    }

}

int main() {
    int m;
    while (~scanf("%d%d", &n, &m)) {
        e = 0;
        int u, v;
        memset(head, -1, sizeof(int) * (n + 1));
        for (int i = 1; i <= m; i++) {
            fastIo::scan_d(u);
            fastIo::scan_d(v);
//            scanf("%d%d", &u, &v);
            addedge(u, v);
        }

        int scc = solve();
//        count_deg();

        memset(cntfenliang, 0, sizeof(int) * (n + 1));
        for (int i = 1; i <= n; i++)
            cntfenliang[belong[i]]++;
        memset(newhead, -1, sizeof(int) * (n + 2));
//        memset(newhead, -1, sizeof(newhead));
        e = 0;
        for (int j = 1; j <= n; j++) {
            for (int i = head[j]; i != -1; i = Edge[i].next) {
                int temp = Edge[i].to;
                if (belong[j] != belong[temp]) {
                    newaddedge(belong[j], belong[temp]);
                }
            }
        }
        memset(dp, 0, sizeof(int) * (scc + 1));
        memset(wei, 0, sizeof(int) * (scc + 1));
        for (int i = 1; i <= n; ++i) {
            wei[belong[i]]++;
        }
        int ans = 0;
        for (int i = 1; i <= scc; ++i) {
            dfs(i);
            ans = max(ans, dp[i]);
        }

        printf("%d\n", ans);
    }
}