//
// Created by bitwater on 18-3-22.
//

#include<bits/stdc++.h>

using namespace std;

struct _ {
    int cnt, fen;
    int id;

    friend bool operator<(const _ &a, const _ &b) {
        if (a.fen != b.fen)
            return a.fen > b.fen;
        if (a.cnt != b.cnt)
            return a.cnt > b.cnt;
        return a.id < b.id;
    }
} people[100000];


int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i) {
        people[i].id = i;
        people[i].fen = 0;
        people[i].cnt = 0;
    }
    for (int i = 1; i <= n; ++i) {

        int k;
        scanf("%d", &k);

        for (int j = 0; j < k; ++j) {
            int a, b;
            scanf("%d%d", &a, &b);
            people[a].cnt++;
            people[a].fen += b;
            people[i].fen -= b;
        }
    }
    sort(people + 1, people + 1 + n);
    for (int i = 1; i <= n; ++i) {
        printf("%d %.2f\n", people[i].id, (double) people[i].fen / 100);
    }

    return 0;
}