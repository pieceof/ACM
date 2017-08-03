#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;
using namespace std;

/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/
const int MOD = 1000000007;

llt powerMod(llt a,llt b,llt mod){
    llt ret = 1LL;
    a %= mod;
    while( b ){
        if ( b & 1LL ) ret = ret*a%mod,--b;
        b >>= 1LL;
        a = a*a%mod;
    }
    return ret;
}

int main()
{
    int n;
    while ( scanf("%d",&n) != EOF ){
        printf("%d\n",powerMod(2,n,MOD)-1);
    }
    return 0;
}
