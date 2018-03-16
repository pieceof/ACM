//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    int x;
    char ch[2];
    char str[100000];
    while (scanf("%d%s",&x,ch) != EOF ){
//        scanf("%s",str);
        getchar();
        gets(str);
        int len = strlen(str);
//        printf("%d\n",len);
        if( len >= x ){
            for(int i = len-x;i < len;++i){
                putchar(str[i]);
            }
            printf("\n");
        }else{
            for(int i = 0;i < x-len;++i){
                putchar(*ch);
            }
            printf("%s",str);
            printf("\n");
        }
    }

	return 0;
}