//
// Created by bitwater on 18-3-15.
//


#include<bits/stdc++.h>

using namespace std;
int w[17] =
        {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
int m[11] = {
        1, 0, 10, 9, 8, 7, 6, 5, 4, 3, 2
};s

int Hash(char const nub[]) {
    int ans = 0;
    for (int i = 0; i < 17; ++i) {
        if (nub[i] < '0' || nub[i] > '9') return INT_MAX;
        int x = nub[i] - '0';
        ans += x * w[i];
    }
    return m[ans % 11];
}

int main(int argc, char *argv[]) {

    int flag = 0;
    char code[20];
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", code);
        int h = Hash(code);
//        printf("hash = %d\n",h);
        if (h == INT_MAX) {
            flag = 1;
            printf("%s\n", code);
        } else {
            int tar = code[17] - '0';
            if (code[17] == 'X') tar = 10;
//            printf("tar %d\n",tar);
            if (h != tar) {
                flag = 1;
                printf("%s\n", code);
            }
        }

    }
    if (flag == 0) printf("All passed\n");
    return 0;
}