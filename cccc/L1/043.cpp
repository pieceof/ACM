//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int cal(int x, int y, int a, int b) {
    if (b < x) b += 60, a--;
//    if (a < x) a += 24;
    return 60 * (a - x) + (b - y);
}

int main(int argc, char *argv[]) {

    int n;
    scanf("%d", &n);

    int x;
    char ch[2];
    int a, b;
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        int time = 0;
        map<int, pair<int, int> > mp;
        while (1) {
            scanf("%d%s%d:%d", &x, ch, &a, &b);
            if (x == 0) break;
            if (*ch == 'S') {
//                if (mp.count(x))continue;

                mp[x] = make_pair(a, b);
            } else {
                if (mp.count(x) == 0)continue;

                cnt++;
                int tmp = cal(mp[x].first, mp[x].second, a, b);
                time += tmp;
                mp.erase(x);
            }
        }
        if (cnt == 0)
            printf("0 0\n");
        else{

            int ans = (int)( (double)time/cnt+0.5 );
            printf("%d %d\n", cnt, ans);
        }
    }
    return 0;
}