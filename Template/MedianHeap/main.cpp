//
// Created by bitwater on 18-3-23.
//

#include<bits/stdc++.h>

using namespace std;

class MedianHeap {
public:
    MedianHeap() { size = 0; }

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
