//
// Created by bitwater on 18-3-19.
//
#include<bits/stdc++.h>

using namespace std;
set<int> st;

int main(int argc, char *argv[]) {
    int n, x;
    scanf("%d%d", &n, &x);
    st.insert(x);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &x);
        if (x < *st.rbegin())
            st.erase(st.upper_bound(x));
        st.insert(x);
    }
    printf("%d\n", st.size());
    return 0;
}
