//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {

    char str[100];
    while (scanf("%s", str) != EOF) {
        int len = strlen(str);
        int cnt[10] = {0};
        for (int i = 0; i < len; ++i)
            cnt[str[i] - '0']++;

        printf("int[] arr = new int[]{");
        bool isfirst = 1;

        int idx = 0;
        int newidx[10];
        for (int i = 9; i >= 0; --i) {
            if (cnt[i]) {
                newidx[i] = idx++;
                if (isfirst) {
                    isfirst = 0;
                    printf("%d", i);
                } else
                    printf(",%d", i);
            }
        }
        printf("};\n");

        printf("int[] index = new int[]{");
        isfirst = 1;
        for (int i = 0; i < len; ++i) {
            if (isfirst) {
                printf("%d", newidx[str[i] - '0']);
                isfirst = 0;
            } else {
                printf(",%d", newidx[str[i] - '0']);
            }
        }

        printf("};\n");

    }

    return 0;
}