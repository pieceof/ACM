//
// Created by bitwater on 18-3-23.
//
#include<bits/stdc++.h>

#define  lson(x) (x)<<1
#define  rson(x) lson(x)|1
using namespace std;

int tree[1000];

void init() {
    memset(tree, -1, sizeof(tree));
}

void insert(int node, int x) {
    if (tree[node] == -1) tree[node] = x;
    else {
        if (x > tree[node])
            insert(lson(node), x);
        else
            insert(rson(node), x);
    }
}

void bfs() {
    queue<int> q;
    q.push(1);
    printf("%d", tree[1]);
    while (!q.empty()) {
        int f = q.front();
        q.pop();
        if (f != 1)printf(" %d", tree[f]);
        if (tree[lson(f)] != -1)
            q.push(lson(f));
        if (tree[rson(f)] != -1)
            q.push(rson(f));
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    init();
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        insert(1, x);
    }
    bfs();
    bool isok = 1;
    for (int i = 1; i <= n; ++i) {
        if (tree[i] == -1)
            isok = 0;
    }
    if (isok) printf("YES\n");
    else printf("NO\n");
    return 0;
}