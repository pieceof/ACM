//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>
typedef  long long llt;

template <typename T>
T gcd(T a,T b){  return b==0?a:gcd(b,a%b); }
using  namespace std;


llt fenzi ,fenmu;
llt add(llt x,llt y){
    fenzi = fenzi*y+fenmu*x;
    fenmu = fenmu*y;
    llt g = gcd(fenmu,fenzi);
    fenmu/=g;
    fenzi/=g;
}

int main(int argc, char *argv[]) {
    int n;
    while(scanf("%d",&n)!=EOF){
        scanf("%lld/%lld",&fenzi,&fenmu);
        for(int i = 1; i < n;++i ){
            llt x,y;
            scanf("%lld/%lld",&x,&y);
            add(x,y);
        }
//        printf("%lld,%lld\n",fenzi,fenmu);
        llt x = fenzi/fenmu;
        fenzi%=fenmu;

        if(x && fenzi )printf("%lld ",x);
        else if(x) printf("%lld\n",x);

        if( fenzi )printf("%lld/%lld\n",fenzi,fenmu);
//        printf("%d",gcd(fenzi,fenmu));
        if ( fenzi == 0 && x == 0 ) printf("0\n");
    }

	return 0;
}