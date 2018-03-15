//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>
using  namespace std;

char str1[11000],str2[11000];

int flag[300];

int main(int argc, char *argv[]) {
    while(gets(str1)){
        gets(str2);
        int len2 = strlen(str2);
        fill(flag,flag+300,0);
        for (int i = 0;i < len2;++i){
            flag[ str2[i] ] = 1;
        }
        int len1 = strlen(str1);
        for(int i = 0; i< len1;++i){
            if ( flag[str1[i]] ) continue;
            printf("%c",str1[i]);
        }
        printf("\n");
    }

	return 0;
}