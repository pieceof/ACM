#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;
typedef long long int_t;
using namespace std;

/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/


//计算a^b%mod
llt powerMod(llt a,llt b,llt mod){
    llt ret = 1LL;
    a %= mod;
    while( b ){
        if ( b & 1LL ) ret = a*ret%mod,--b;
        b >>= 1LL;
        a = a*a%mod;
    }
    return ret;
}

//非递归的扩展欧几里德算法
//返回a、b的gcd，同时x、y满足ax+by=gcd
int_t exEuclid(int_t a,int_t b,int_t&x,int_t&y){
    int_t x0 = 1, y0 = 0;
    int_t x1 = 0, y1 = 1;
    x = 0; y = 1;
    int_t r = a % b;
    int_t q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}


//求a相对于p的逆元，a、p互质才存在逆元
int_t inv(int_t a,int_t p){
    int_t x,y;
    int_t r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}
const int SIZE = 20000;

llt nub[SIZE];
int main()
{
    int t;
    cin>>t;
    while ( t-- ){
        llt e,p,q;
        int m;
        cin>>e>>p>>q>>m;
        for (int i = 0 ;i < m;++i )
            cin>>nub[i];

        llt n = p*q;
        llt fn = (p-1)*(q-1);
        llt d = inv(e,fn);
        for (int i = 0 ;i < m-1;++i ){
            cout << powerMod( nub[i] , d,n ) << " " ;
        }
        cout << powerMod( nub[m-1] , d,n ) << endl;
    }
    return 0;
}
