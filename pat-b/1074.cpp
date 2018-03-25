//
// Created by bitwater on 18-3-25.
//

#include <bits/stdc++.h>

using namespace std;

char table1[200];
int table[200];
char nuba[200], nubb[200];
int ans[200] = {0};

int main() {

    scanf("%s%s%s", table1, nuba, nubb);

    reverse(table1, table1 + strlen(table1));

    int lentale = strlen(table1);
    for (int i = 0; i < lentale; ++i) {
        if (table1[i] == '0') table[i] = 10;
        else table[i] = table1[i] - '0';
    }
    for (int i = lentale; i < 199; ++i) {
        table[i] = 10;
    }
    reverse(nuba, nuba + strlen(nuba));
    reverse(nubb, nubb + strlen(nubb));
    int lenmi = min(strlen(nuba), strlen(nubb));
    int lenma = max(strlen(nuba), strlen(nubb));
    int lena = strlen(nuba);
    int lenb = strlen(nubb);

    for (int i = 0; i < lenmi; ++i) {
        int x = nuba[i] - '0';
        int y = nubb[i] - '0';
        ans[i] += x + y;
        ans[i + 1] += ans[i] / table[i];
        ans[i] %= table[i];
    }

    char *nub = (lena > lenb) ? nuba : nubb;

    for (int i = lenmi; i < lenma; ++i) {
        ans[i] += nub[i] - '0';
        ans[i + 1] += ans[i] / table[i];
        ans[i] %= table[i];
    }
    for (int i = lenma; i < 199; ++i) {
        if (ans[i] == 0)break;
        ans[i + 1] += ans[i] / table[i];
        ans[i] %= table[i];
    }

    int maxl = 199;
    while (maxl >= 0 && ans[maxl] == 0) maxl--;
    for (int i = maxl; i >= 0; --i)
        printf("%d", ans[i]);
    if (maxl == -1)printf("0");
    printf("\n");

    return 0;
}