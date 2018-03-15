//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    int ans[11] = {1};
    for (int i = 1; i <= 10; ++i)ans[i] = ans[i - 1] * i;
    for (int i = 2; i <= 10; ++i)ans[i] += ans[i - 1];
    int n;
    while (scanf("%d", &n) != EOF)printf("%d\n", ans[n]);

    return 0;
}