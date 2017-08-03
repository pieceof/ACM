#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef unsigned long long llt;
using namespace std;

/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/

//bool just( int x ){
//    int tmp = 0;
//    while( x ){
//        if ( tmp == 1 && x % 2 == 1 ) return true;
//        tmp = x % 2 , x >>= 1;
//    }
//    return false;
//}
const int MOD = 1e9+7;
const int SIZE = 1000;
int fib[SIZE];
int ans[SIZE];
int pow2[SIZE];

void init( ){
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2;i < SIZE;++i ){
        fib[i] = (fib[i-1] + fib[i-2] )%MOD;
    }
    pow2[0] = 1;
    for (int i = 1;i < SIZE;++i ){
        pow2[i] = (pow2[i-1]*2LL)%MOD ;
    }
    for (int i = 1;i < SIZE-2;++i ){
        ans[i] = pow2[i] - fib[i+2];
        if ( ans[i] < 0 ) ans[i] += MOD;
        ans[i] %= MOD;
    }
}

int main()
{
//    deBug(MOD);
//    for (int j = 1;j <= 10;++j ){
//        int cnt = 0;
//        for (int i = 0 ;i < (1<<j);++i){
//            if ( just( i ) ){
////                deBug(i);
//                cnt++;
//            }
//        }
//        deBug(cnt);
//
//    }
    init();
//    init
    int n;
    while ( cin>> n ){
//        deBug(pow2[n]);
        cout << (ans[n]+MOD)%MOD << endl;
//        cout << f[n] << endl;
    }
    return 0;
}
