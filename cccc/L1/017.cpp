//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {

    char str[100];
    while (scanf("%s", str) != EOF) {
        int len = strlen(str);
        double ans = 1;
        int cnt = 0;
        for (int i = 0; i < len; ++i)
            if (str[i] == '2')
                cnt++;
        if (str[0] == '-') len--, ans *= 1.5;
        ans *= cnt / (double) len;
        if ((str[strlen(str) - 1] - '0') % 2 == 0) ans *= 2;

        printf("%.2f%%\n", ans * 100);
    }

    return 0;
}