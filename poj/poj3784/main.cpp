//
// Created by bitwater on 18-3-23.
//

#include"../../headers.h"

class MedianHeap {
public:
    MedianHeap() { size = 0; }

    void clear() {
        size = 0;
        lSet.clear();
        rSet.clear();
        while (!st.empty()) st.pop();

    }

    bool getMedian(int &x) {
        if (size <= 0)return 0;
        x = *lSet.rbegin();
        return 1;
    }

    bool push(int x) {
        st.push(x);
        if (lSet.size() == 0) {
            if (rSet.size() == 0 || x <= *rSet.begin())
                lSet.insert(x);
            else
                rSet.insert(x);
        } else if (x <= *lSet.rbegin()) lSet.insert(x);
        else rSet.insert(x);
        this->splay();
        size++;
        return 1;
    }

    bool pop(int &x) {
        if (size <= 0) return 0;
        x = st.top();
        st.pop();
        if (lSet.count(x))lSet.erase(lSet.find(x));
        else if (rSet.count(x))rSet.erase(rSet.find(x));
        this->splay();
        size--;
        return 1;
    }

private:
    int size;
    multiset<int> rSet;
    multiset<int> lSet;
    stack<int> st;

    void splay() {
        int smi = lSet.size();
        int sma = rSet.size();
        if (sma == smi || smi == sma + 1) return;
        if (sma == smi + 1) {
            lSet.insert(*rSet.begin());
            rSet.erase(rSet.find(*rSet.begin()));
        }
        if (smi == sma + 2) {
            rSet.insert(*lSet.rbegin());
            lSet.erase(lSet.find(*lSet.rbegin()));
        }
    }
};

int main(int argc, char *argv[]) {
    MedianHeap mhp;
    int p;
    scanf("%d", &p);
    while (p--) {
        mhp.clear();
        int x, m;
        scanf("%d%d", &x, &m);
        printf("%d %d\n", x, m / 2 + 1);
        for (int i = 1; i <= m; ++i) {
            scanf("%d", &x);
            mhp.push(x);
            if (i & 1) {
                mhp.getMedian(x);
                printf("%d", x);
                if (i % 20 == 19) printf("\n");
                else printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}