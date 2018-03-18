//
// Created by bitwater on 18-3-18.
//

#include<bits/stdc++.h>

using namespace std;

struct _t {
    double sum, w, p;

    bool friend operator<(const _t &a, const _t &b) {
        return a.p < b.p;
    }
} bing[2000];

int main(int argc, char *argv[]) {
    int n;
    double need;

    while (scanf("%d%lf", &n, &need) != EOF) {
        for (int i = 0; i < n; ++i)scanf("%lf", &bing[i].sum);
        for (int i = 0; i < n; ++i)scanf("%lf", &bing[i].w);
        for (int i = 0; i < n; ++i)bing[i].p = bing[i].w / bing[i].sum;
        sort(bing, bing + n);
        double ans = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (need > bing[i].sum) {
                ans += bing[i].w;
                need -= bing[i].sum;
            } else {
                ans += bing[i].p * need;
                break;
            }
        }
        printf("%.2f\n", ans);
    }

    return 0;
}