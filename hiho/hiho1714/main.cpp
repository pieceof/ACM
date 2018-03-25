//
// Created by bitwater on 18-3-25.
//

#include<bits/stdc++.h>

using namespace std;

#define SIZE 110000

int n;
int w[SIZE];
double dp[SIZE][2] = {0};//dp[i][0] 0表示不去，dp[i][1]1表示去了
int father[SIZE] = {0};
map<int, vector<int> > child;

void tree_dp(int node) {
    for (auto i: child[node]) {//i为下属
        tree_dp(i);//递归调用孩子结点，从叶子结点开始dp
        //关键
        dp[node][1] += max(dp[i][1] + w[i] / 2.0, dp[i][0]);
        dp[node][0] += max(dp[i][1] + w[i], dp[i][0]);
    }

}

int main() {
    int i;
    int f, c, root;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)scanf("%d", w + i);
    for (i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        father[v] = u;
        child[u].push_back(v);
    }
    root = 1;//记录父结点
    while (father[root])//查找父结点
        root = father[root];
    tree_dp(root);
    printf("%.1f\n", max(dp[root][0], dp[root][1] + w[root]));

    return 0;
}