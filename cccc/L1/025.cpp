//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int just(char const str[]) {
//    cout << str << endl;
    int len = strlen(str);
    if (len <= 0 || len > 4)return -1;
    for (int i = 0; i < len; ++i)if (str[i] < '0' || str[i] > '9') return -1;
    int ret;
    sscanf(str, "%d", &ret);
    if (ret > 1000 || ret == 0) return -1;
    return ret;
}

int main(int argc, char *argv[]) {
    int x, y;
    char xn[10000], yn[10000];
    char str[10000];
    while (gets(str)) {
        int len = strlen(str);
        int idx = 0;
        while (str[idx] != ' ')xn[idx] = str[idx], idx++;
        xn[idx] = '\0';
        idx++;
        int idx2 = idx;
        while (str[idx2]) {
            yn[idx2 - idx] = str[idx2], ++idx2;
        }
        yn[idx2 - idx] = '\0';

        x = just(xn);
        y = just(yn);
        if (x > 0 && y > 0)
            printf("%d + %d = %d\n", x, y, x + y);
        if (x < 0 && y > 0)
            printf("? + %d = ?\n", y);
        if (x > 0 && y < 0)
            printf("%d + ? = ?\n", x);
        if (x < 0 && y < 0)
            printf("? + ? = ?\n");

    }
    return 0;
}