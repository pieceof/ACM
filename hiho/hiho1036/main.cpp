//
// Created by bitwater on 18-3-26.
//
#include"../../headers.h"

//*
const int TRIE_SIZE = 4000000;
struct node_t {
    node_t *child[30];
    node_t *failer;
//	int idx;//对应解释的序号
//    bool suffix; /*!< 是否为结束 */
    int cnt;    /*!< 以该节点结束字符串的数量*/

} Node[TRIE_SIZE];
int toUsed;

inline int tr(char ch) {
    return (ch >= 'a' && ch <= 'z') ? ch - 'a' : 29;
}

//插入单词
void Insert(char const word[]) {
    node_t *loc = Node;
    for (int i = 0; word[i]; ++i) {
//        loc->cnt++;
        int sn = tr(word[i]);

        if (!loc->child[sn]) {
            memset(Node + toUsed, 0, sizeof(node_t));
            loc->child[sn] = Node + toUsed++;
        }
        loc = loc->child[sn];
    }
    loc->cnt++;
//    loc->suffix = 1;
}

void ACbuild() {
    Node[0].failer = NULL; /*!< root节点的failer为空  */
    queue<node_t *> q;
    for (int i = 0; i < 26; ++i) {
        node_t *p = Node[0].child[i];
        if (p) {
            p->failer = Node;
            q.push(p);
        }
    }
    while (!q.empty()) {
        node_t *fa = q.front();
        q.pop();

        for (int i = 0; i < 26; ++i) {
            node_t *p = fa->child[i];
            if (p) {
                node_t *v = fa->failer;
                while (v && !v->child[i]) v = v->failer;
                if (!v) p->failer = Node;
                else p->failer = v->child[i];
                q.push(p);
            }
        }
    }
}


//查找单词,返回出现的次数
int Find(char const word[]) {
    node_t *loc = Node;
    for (int i = 0; word[i]; ++i) {
//        if ( loc->suffix ) return 1;
        int sn = tr(word[i]);
        if (!loc->child[sn]) return 0;
        loc = loc->child[sn];
    }
    return loc->cnt;
}
//*/

int Search(char const word[]) {
    int ans = 0;
    node_t *loc = Node;
    for (int i = 0; word[i]; ++i) {
        int sn = word[i] - 'a';
        while (loc && !loc->child[sn])
            loc = loc->failer;
        loc = loc ? loc->child[sn] : Node;
        node_t *p = loc;
        while (p != NULL && p->cnt >= 0) {
            ans += p->cnt;
            p->cnt = -1;
            p = p->failer;
        }
    }
    return ans;
}

inline void initTrie() {
    toUsed = 1;
    memset(Node, 0, sizeof(node_t));
}

const int SIZE = 1003000;
char par[SIZE];
char tar[SIZE];


int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        initTrie();
        for (int i = 0; i < n; ++i) {
            scanf("%s", par);
            Insert(par);
        }
        ACbuild();
        scanf("%s", tar);
        int ans = Search(tar);
//        printf("%d\n", ans);
        printf(ans ? "YES\n" : "NO\n");
    }

    return 0;
}
