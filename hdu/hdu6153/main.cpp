#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <assert.h>
#include <climits>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
typedef long long llt;
using namespace std;

const llt MOD  = 1000000007;
int const SIZE = 6005000;
llt sum[SIZE];
llt sum2[SIZE];

template<class DATA>
void getKMPNext(DATA const P[],int *Next,int n ) {
    Next[0] = -1;
    int i = 0, k = -1;n++ ; // kmp循环匹配多算一位
    while( i < n ) {
        while( k >= 0 && P[i] != P[k] )
            k = Next[k];
        ++i,++k;
        if ( i == n ) return;
        Next[i] = ( P[i] == P[k] ) ? Next[k] : k;
    }
}

/**< 循环kmp匹配的时候要多算一位next  */
template<class DATA >
llt KMP(DATA const T[],int tlen,DATA const P[],int plen,int Next[]) {
    llt ans = 0;
    int tp = 0, pp = 0;
    while( tp < tlen ) {
        if ( -1 == pp || T[tp] == P[pp] ){
            if ( T[tp] == P[pp] )
                ans = (ans+pp+1)%MOD;
            ++tp,++pp;
        }
        else
            pp = Next[pp];
        if ( plen == pp  ) {
            pp = Next[pp]; //可以重叠
            ans = (ans+sum2[pp])%MOD;
        }
    }
    return ans;
}
char tar[SIZE];
char par[SIZE];
int Next[SIZE];

int main(){
    sum[0] = 0;
    sum2[0] = 0;
    for (int i = 1;i < SIZE;++i ){
        sum[i] = (sum[i] + i + sum[i-1] ) % MOD;
        sum2[i] = (sum2[i-1] + sum[i] ) %MOD;
    }
    int t; scanf("%d",&t);while( t-- ){

        scanf("%s",tar);
        int tlen = strlen( tar );
        reverse(tar,tar+tlen);

        scanf("%s",par);
        int plen = strlen( par );
        reverse(par,par+plen);

        plen = min(plen,tlen);
        par[plen] = '\0';

        getKMPNext( par,Next,plen );
        llt ans = KMP(tar,tlen,par,plen,Next);
        printf("%lld\n",ans);
    }

    return 0;
}
