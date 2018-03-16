//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;
map<int, int> mp;


int main(int argc, char *argv[]) {


    int n;
    scanf("%d", &n);
    while (n--) {
        int k;
        scanf("%d", &k);
        for (int i = 0; i < k; ++i) {
            int x;
            scanf("%d", &x);
            if (k == 1)continue;
            mp[x] = 1;
        }
    }
    int m;
    scanf("%d", &m);
    vector<int> v;
    while (m--) {
        int x;
        scanf("%d", &x);
        if (mp.count(x) == 0) {
            v.push_back(x);
            mp[x] = 1;
        }
    }
    if (v.size() == 0)
        printf("No one is handsome\n");
    else {
        printf("%05d", v[0]);
        for (int i = 1; i < v.size(); ++i)
            printf(" %05d", v[i]);
        printf("\n");
    }

    return 0;
}