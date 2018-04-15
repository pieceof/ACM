//
// Created by bitwater on 18-4-15.
//

#include<bits/stdc++.h>

using namespace std;
int nub[110];

int main() {
    int n, p, q, k;
    while (scanf("%d%d%d%d", &n, &p, &q, &k) != EOF) {
        for (int i = 0; i < n; ++i)scanf("%d", nub + i);
        sort(nub, nub + n);
        int ans = 0;
        if (k == 0) {
            int idx = 0;
            for (int i = 0; i < q; ++i)ans -= nub[idx++];
            for (int i = 0; i < p; ++i)ans += nub[idx++];
            ans += nub[idx];
            printf("%d\n", ans);
        } else {
            for (int i = 0; i < n; ++i)ans += nub[i];
            if (q != 0)ans -= 2 * nub[0];
            printf("%d\n", ans);
        }
    }
    return 0;
}