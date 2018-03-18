//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;
int n;
int a[100];
int b[100];
#define lson(x) ((x)<<1)
#define rson(x) (lson(x)|1)
int node[100000];


bool isRight(int x, int p) {
    int ix, ip;
    for (int i = 0; i < n; ++i) {
        if (b[i] == x) ix = i;
        if (b[i] == p) ip = i;
    }
    return ix > ip;
}

//  l , r 是a的下标, fa 是 node 的下标
void DFS(int l, int r, int fa) {
    if (l > r) return;
    if (isRight(a[r], node[fa])) node[rson(fa)] = a[r];

    int idx = r;
    while (isRight(a[idx], node[fa]) && idx >= l) idx--;
    if (idx >= l)node[lson(fa)] = a[idx];

    DFS(idx + 1, r - 1, rson(fa));
    DFS(l, idx - 1, lson(fa));
}

void dfs(int fa) {
    if (node[lson(fa)] != -1)dfs(lson(fa));
    if (node[rson(fa)] != -1)dfs(rson(fa));
    cout << node[fa] << " ";
}

void BFS() {
    queue<int> q;
    q.push(1);
    printf("%d", node[1]);
    while (!q.empty()) {
        int fa = q.front();
        q.pop();
        if (fa != 1)printf(" %d", node[fa]);
        if (node[lson(fa)] != -1) q.push(lson(fa));
        if (node[rson(fa)] != -1) q.push(rson(fa));
    }
    printf("\n");
}

int main(int argc, char *argv[]) {

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", a + i);
    for (int i = 0; i < n; ++i) scanf("%d", b + i);
    memset(node, -1, sizeof(node));
    node[1] = a[n - 1];
    DFS(0, n - 2, 1);

//    dfs(1);
    BFS();
    return 0;
}