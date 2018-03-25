//
// Created by bitwater on 18-3-25.
//

#include<bits/stdc++.h>

using namespace std;

set<int> st;
map<int, int> Next, value;

int main() {
    int start, n;
    scanf("%d%d", &start, &n);
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if(Next.count(a))while (1);
        Next[a] = c;
        if(value.count(a))while (1);
        value[a] = b;
    }
    int s = start;
    int dstart = -1;
    int tal = -1;
    int pre = -1;
    while (s != -1) {
        if (Next.count(s) == 0) break;
        if (st.count(abs(value[s])) == 0) {
            st.insert(abs(value[s]));
            pre = s;
            s = Next[s];
        } else {
            int ne = Next[s];
            if (pre != -1) Next[pre] = Next[s];

            if (dstart == -1) dstart = s;
            if (tal != -1) Next[tal] = s;
            Next[tal = s] = -1;

            s = ne;
        }

    }
    s = start;
    while (s != -1) {
        if (Next.count(s) == 0) break;
        if (Next[s] != -1)
            printf("%05d %d %05d\n", s, value[s], Next[s]);
        else
            printf("%05d %d -1\n", s, value[s]);
        s = Next[s];
    }

    s = dstart;
    while (s != -1) {
        if (Next.count(s) == 0) break;
        if (Next[s] != -1)
            printf("%05d %d %05d\n", s, value[s], Next[s]);
        else
            printf("%05d %d -1\n", s, value[s]);
        s = Next[s];
    }
    return 0;
}