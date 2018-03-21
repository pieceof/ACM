//
// Created by bitwater on 18-3-21.
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
inline bool isLeft(int x,int p){
    return  !isRight(x,p);
}

//  l , r 是a的下标, fa 是 node 的下标
void DFS(int l, int r, int fa) {
    if (l > r) return;
    if (isLeft(a[l], node[fa])) node[lson(fa)] = a[l];

    int idx = l;
    while (isLeft(a[idx], node[fa]) && idx <= r) idx++;
    if (idx <= r)node[rson(fa)] = a[idx];

    DFS(l+1, idx - 1, lson(fa));
    DFS(idx + 1, r, rson(fa));
}

void dfs(int fa) {
    cout << node[fa] << " ";
    if (node[lson(fa)] != -1)dfs(lson(fa));
    if (node[rson(fa)] != -1)dfs(rson(fa));
}

void BFS() {
    queue<int> q;
    q.push(1);
    printf("%d", node[1]);
    while (!q.empty()) {
        int fa = q.front();
        q.pop();
        if (fa != 1)printf(" %d", node[fa]);

        if (node[rson(fa)] != -1) q.push(rson(fa));
        if (node[lson(fa)] != -1) q.push(lson(fa));
    }
    printf("\n");
}

int main(int argc, char *argv[]) {

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", b + i);
    for (int i = 0; i < n; ++i) scanf("%d", a + i);
    memset(node, -1, sizeof(node));
    node[1] = a[0];
    DFS(1, n - 1, 1);
//    dfs(1);
    BFS();
    return 0;
}
