//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {

    char str[100000];

    while (scanf("%s", str) != EOF) {
        int cnt[4] = {0};
        int len = strlen(str);

        for (int i = 0; i < len; ++i) {
            if (str[i] == 'G' || str[i] == 'g')cnt[0]++;
            if (str[i] == 'P' || str[i] == 'p')cnt[1]++;
            if (str[i] == 'L' || str[i] == 'l')cnt[2]++;
            if (str[i] == 'T' || str[i] == 't')cnt[3]++;
        }
        while (cnt[0] || cnt[1] || cnt[2] || cnt[3]) {

            for (int i = 0; i < 4; ++i) {
                if (cnt[i]) {
                    cnt[i]--;
                    if (i == 0)putchar('G');
                    if (i == 1)putchar('P');
                    if (i == 2)putchar('L');
                    if (i == 3)putchar('T');
                }
            }

        }
        printf("\n");

    }
    return 0;
}