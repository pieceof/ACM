//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    char str[10000];
    gets(str);
    int ans = 0;
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        int l, r;
        l = r = i;
        int cnt = 0;
        while (l >= 0 && r < len && str[l] == str[r])cnt++, l--, r++;
        ans = max(ans, (cnt - 1) * 2 + 1);
        cnt = 0;
        l = i, r = i + 1;
        while (l >= 0 && r < len && str[l] == str[r])cnt++, l--, r++;
        ans = max(ans, cnt * 2);

    }
    printf("%d\n", ans);


    return 0;
}