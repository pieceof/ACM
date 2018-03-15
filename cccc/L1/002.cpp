//
// Created by bitwater on 18-3-14.
//

//#include"../../headers.h"
#include<bits/stdc++.h>

int main(int argc, char *argv[]) {

    int x;
    char ch[2];
    while (scanf("%d%s", &x, ch) != EOF) {
        int s = 3;
        int left = x - 1;
        while (left >= s * 2) {
            left -= s * 2;
            s += 2;
        }
//        deBug(s);
        s -= 2;
        int tmp = 0;
        for ( int i = s;i > 1;i-=2){
            for (int j = 0;j < tmp;++j)printf(" ");
            for (int j = 0;j < i;++j )printf("%s",ch);
            //for (int j = 0;j < tmp;++j)printf(" ");
            printf("\n");
            tmp ++;
        }

        for (int i = 0;i < (s-1)/2;++i) printf(" ");
        printf("%s\n",ch);
        //for (int i = 0;i < (s-1)/2;++i) printf(" ");

        tmp = (s-1)/2-1;
        for (int i = 3;i <=s ;i+=2){
            for (int j = 0;j < tmp;++j)printf(" ");
            for (int j = 0;j < i;++j)printf("%s",ch);
            //for (int j = 0;j < tmp;++j)printf(" ");
            printf("\n");
            tmp--;
        }


        printf("%d\n", left);

    }

    return 0;
}