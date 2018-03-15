//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    int n;
    while(scanf("%d",&n)!=EOF){
        int ans = 1;
        for(int i = 0;i< n;++i){
            ans *=2;
        }
        printf("2^%d = %d\n",n,ans);
    }
	return 0;
}