//
// Created by bitwater on 18-3-14.
//
#include<bits/stdc++.h>
using  namespace std;
typedef long long llt;
map<llt,llt> trid,realid;

int main(int argc, char *argv[]) {
    int n;
    while(scanf("%d",&n)!=EOF){
        trid.clear();
        realid.clear();
        llt x,y,z;
        for (int i = 0;i < n;++i ){
            scanf("%lld%lld%lld",&x,&y,&z);
            trid[y] = x;
            realid[y] =z;
        }
        int m;
        scanf("%d",&m);
        for(int i = 0; i < m;++i){
            int x;
            scanf("%d",&x);
            printf("%lld %lld\n",trid[x],realid[x]);
        }
    }

	return 0;
}
