//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int a[120][120];
int b[120][120];
int c[120][120];

int main(int argc, char *argv[]) {

    int ra, ca, rb, cb;
    cin >> ra >> ca;
    for (int i = 0; i < ra; ++i)
        for (int j = 0; j < ca; ++j)
            cin >> a[i][j];

    cin >> rb >> cb;
    for (int i = 0; i < rb; ++i)
        for (int j = 0; j < cb; ++j)
            cin >> b[i][j];

    if (ca != rb) {
        printf("Error: %d != %d\n", ca, rb);
    } else {

        for (int i = 0; i < ra; ++i) {
            for (int j = 0; j < cb; ++j) {
                c[i][j] = 0;
                for (int k = 0; k < ca; ++k) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        printf("%d %d\n",ra,cb);
        for(int i = 0;i < ra;++i){
            for(int j = 0;j < cb-1;++j){
                printf("%d ",c[i][j]);
            }printf("%d\n",c[i][cb-1]);
        }
    }

    return 0;
}