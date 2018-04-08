//
// Created by bitwater on 18-4-9.
//

#include <cstdio>
#include <cstring>

using namespace std;

const int TRIE_SIZE = 100000;
struct node_t {
    node_t *child[2];
    bool isFull;
} Node[TRIE_SIZE];
int toUsed;


void Insert(int const word[], int len, int flag, int p) {

    node_t *loc = Node;
    for (int i = 0; i < 40; ++i) {
        if (flag == 0 && i >= len)break;
        int sn = word[i];
        if (!loc->child[sn]) {
            memset(Node + toUsed, 0, sizeof(node_t));
            loc->child[sn] = Node + toUsed++;
        }
        if (i > len && sn == p && flag == 1) {
            if (!loc->child[p ^ 1]) {
                memset(Node + toUsed, 0, sizeof(node_t));
                loc->child[p ^ 1] = Node + toUsed++;
            }
            loc->child[p ^ 1]->isFull = 1;
        }
        loc = loc->child[sn];
    }
    loc->isFull = true;
}

char str[2000];
int bit1[40], bit2[40];
int nub1[10], nub2[10];

void add1() {
    sscanf(str, "%d.%d.%d.%d.%d-%d.%d.%d.%d.%d", nub1 + 0, nub1 + 1, nub1 + 2, nub1 + 3, nub1 + 4,
           nub2 + 0, nub2 + 1, nub2 + 2, nub2 + 3, nub2 + 4);
    memset(bit1, 0, sizeof(bit1));
    memset(bit2, 0, sizeof(bit2));

    for (int i = 0; i < 5; ++i)
        for (int j = 7, x = nub1[i], y = nub2[i]; j >= 0; --j, x >>= 1, y >>= 1)
            bit1[j + i * 8] = x % 2, bit2[j + i * 8] = y % 2;

    int len = 0;
    while (len < 40 && bit1[len] == bit2[len])len++;

    Insert(bit1, len, 1, 0);
    Insert(bit2, len, 1, 1);
}

void add2() {
    int b;
    sscanf(str, "%d.%d.%d.%d.%d/%d", nub1 + 0, nub1 + 1, nub1 + 2, nub1 + 3, nub1 + 4, &b);

    memset(bit1, 0, sizeof(bit1));
    for (int i = 0; i < 5; ++i)
        for (int j = 7, x = nub1[i]; j >= 0; --j, x >>= 1)
            bit1[j + i * 8] = x % 2;

    Insert(bit1, b, 0, 0);
}


void dfs(node_t *root) {
    if (root->isFull) return;
    if (root->child[0])dfs(root->child[0]);
    if (root->child[1])dfs(root->child[1]);
    if (root->child[0] && root->child[1] && root->child[0]->isFull && root->child[1]->isFull)
        root->isFull = 1;
}

int cnt;
int ans[20000][6];
int ip[40];

void Search(node_t *loc, int idx) {
    if (loc->isFull) {
        for (int i = idx; i < 40; ++i)ip[i] = 0;
        for (int i = 0; i < 5; ++i) {
            ans[cnt][i] = 0;
            for (int j = 7, x = 1; j >= 0; --j, x <<= 1)
                ans[cnt][i] += x * ip[j + i * 8];
        }
        ans[cnt++][5] = idx;
        return;
    }
    if (loc->child[0]) {
        ip[idx] = 0;
        Search(loc->child[0], idx + 1);
    }
    if (loc->child[1]) {
        ip[idx] = 1;
        Search(loc->child[1], idx + 1);
    }

}

int main() {
//    freopen("i.in", "r", stdin);
//    freopen("i.ans", "w", stdout);
    int n;
    while (scanf("%d", &n) != EOF && n) {
        toUsed = 1;
        memset(Node, 0, sizeof(Node));
        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            for (int j = 0; str[j]; ++j) {
                if (str[j] == '-')add1();
                if (str[j] == '/')add2();
            }
        }
        dfs(Node);
        cnt = 0;
        Search(Node, 0);
        printf("%d\n", cnt);
        for (int i = 0; i < cnt; ++i)
            printf("%d.%d.%d.%d.%d/%d\n", ans[i][0], ans[i][1], ans[i][2], ans[i][3], ans[i][4], ans[i][5]);

    }

    return 0;
}