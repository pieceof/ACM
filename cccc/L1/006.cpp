//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>

typedef long long llt;
using namespace std;

int main(int argc, char *argv[]) {

    llt x;
    while (scanf("%lld", &x) != EOF) {
        bool isok = 0;
        for (int i = 12; i > 1 ; --i) {
            llt s = 1;
            llt l = 2, r = 2;
            for (int j = 0; j < i; ++j) {
                s *= r;
                r++;
            }

            for (; s <= x;) {
                if (x % s == 0) {
                    printf("%d\n%lld", i, l);
                    for (llt k = l + 1; k < r; ++k)printf("*%lld", k);
                    printf("\n");
                    isok = 1;
                    break;
                }
                s = s / l * r;
                l++, r++;
            }
            if (isok)break;

        }
        if(!isok){
            for(llt i = 2;i *i <= x ;++i ){
                if (x %i == 0 ){
                    printf("1\n%lld\n",i);
                    isok = 1;
                    break;
                }
            }

        }

        if(!isok)printf("1\n%lld\n",x);
    }

    return 0;
}