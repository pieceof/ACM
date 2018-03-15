//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {

    int n;
    while (scanf("%d", &n) != EOF) {
        char ch[2];
        scanf("%s", ch);
        int row = int(n / 2.0 + 0.5);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < n; ++j) {
                printf("%s", ch);
            }
            printf("\n");
        }
    }
    return 0;
}