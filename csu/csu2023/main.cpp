//
// Created by bitwater on 18-4-2.
//

#include<iostream>
#include<string>
#include <cstring>

using namespace std;


int lenCnt[200000];

//*
const int TRIE_SIZE = 900000;
struct node_t {
    node_t *child[30];
    node_t *failer;
    bool suffix; /*!< 是否为结束 */
    int idx; /*!< 第一次走该路径的单词id */

} Node[TRIE_SIZE];
int toUsed;

inline int tr(char ch) {
    return (ch >= 'a' && ch <= 'z') ? ch - 'a' : 29;
}

//插入单词
void Insert(char const word[], int idx) {
    node_t *loc = Node;
    int len = lenCnt[idx];
    for (int i = 0; i < len; ++i) {
        if (!loc->idx) loc->idx = idx;
        int sn = tr(word[i]);
        if (!loc->child[sn]) {
            memset(Node + toUsed, 0, sizeof(node_t));
            loc->child[sn] = Node + toUsed++;
        }
        loc = loc->child[sn];
    }
    if (!loc->idx) loc->idx = idx;
    loc->suffix = 1;
}


int Find(char const word[]) {
    node_t *loc = Node;
    int ret = 0;
    int slen = strlen(word);
    for (int i = 0; i < slen;) {

        bool isfrist = 1;
        int tj = i;
        int lastIdx = loc->idx;
        while (tj < slen) {
            int sn = tr(word[tj]);

            if (!loc->child[sn]) {
                if (isfrist) return slen - i + ret;
                else break;
            }
            if (loc->child[sn]->idx != lastIdx) {
                if (isfrist) lastIdx = loc->child[sn]->idx;
                else break;
            }
            isfrist = 0;
            loc = loc->child[sn];
            tj++;
        }

        int a1 = tj - i;
        int a2 = 2 + lenCnt[loc->idx] - tj;

        ret += min(a1, a2);
        i = tj;
    }
    return ret;
}


//*/
inline void initTrie() {
    toUsed = 1;
    memset(Node, 0, sizeof(node_t));
}

char tmp[1000000];

int main() {
    int n, m;
    int kase = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (kase++)printf("\n");
        initTrie();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", tmp);
            lenCnt[i] = strlen(tmp);
            Insert(tmp, i);
        }
        while (m--) {
            scanf("%s", tmp);
            printf("%d\n", Find(tmp));
        }
    }
    return 0;
}
