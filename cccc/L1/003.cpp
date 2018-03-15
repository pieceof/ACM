//
// Created by bitwater on 18-3-14.
//

#include<bits/stdc++.h>
int main(int argc, char *argv[]) {
    char ch[10000];
    int cnt [10];
    while (scanf("%s",ch)!=EOF){
        int len = strlen(ch);
        for( int i = 0;i < len;++i ){
            cnt[ ch[i]-'0' ] ++;
        }
        for (int i = 0;i < 10;++i ){
            if ( cnt[i] ){
                printf("%d:%d\n",i,cnt[i]);
            }
        }
    }

	return 0;
}