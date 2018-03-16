//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {

    int n;
    scanf("%d", &n);
    map<int, int> mp;
    int id;
    while (n--) {
        int k;
        scanf("%d", &k);

        while (k--) {
            int x;
            scanf("%d", &x);
            id = x;
            if (mp.count(x)) mp[x]++;
            else mp[x] = 1;
        }

        for (auto i : mp) {
            if (i.second > mp[id]) id = i.first;
            if (i.second == mp[id]) id = max(id, i.first);

        }

    }
    printf("%d %d\n", id, mp[id]);
    return 0;
}