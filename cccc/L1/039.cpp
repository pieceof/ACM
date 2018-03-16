//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

int main(int argc, char *argv[]) {
    int row;
    char str[10000];
    while (scanf("%d", &row) != EOF) {
        getchar();
        gets(str);
        int len = strlen(str);

        int bei = len / row;
        int yu = len % row;
        if (yu) bei++;

        for (int i = 0; i < row; ++i) {
            int s = row * bei - 1 - (row - i - 1);
            while (s >= 0) {
                if (s >= len)printf(" ");
                else putchar(str[s]);
                s -= row;
            }
            printf("\n");
        }


    }

    return 0;
}