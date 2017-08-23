#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <cstring>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <set>
#include <queue>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a),-1,sizeof(a))
#define varName(x) #x
#define deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define deBugPair(exp1,exp2) cout<< " == > " << "(" << #exp1<<" : "<< (exp1) << "," << #exp2 << " : " << (exp2) << ")" << endl
#define Case   printf("Case %d:\n",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path)  freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
///-------------------------   math ------------------------///
typedef long long llt;
double const PI = acos(-1.0);
inline double ln(double const&x ){ return log(x)/log(exp(1));}
inline double Vfrustum( double const&r1,double const&r2,double const&h ){
    return PI * h * ( r1*r1 + r2*r2 + r1*r2 )/3;
}


///----------------------- debug tools ---------------------///

template <typename T>
void ArrayCin( T *a ,int n ,int pos = 0){
    for (int i = pos;i < n;++i ) cin>>a[i];
}

template <typename T>
void ArrayDisp(T *a,int n ){
    cout << "===> : ";
    for (int i = 0;i < n;++i )cout << std::right << setw(2)<<a[i]<<" ";cout << endl;
}
template <typename T>
void ArrayDisp(T *a,int n,int m ,int twoLen){
    for (int i = 0;i < n;++i ){
        for (int j = 0;j < m;++j ){
            cout << std::right << setw(2)<< *( a + i*twoLen + j ) << " ";
        }cout << endl;
    }cout << endl;
}
///------------------- faster IO --------------------//

namespace fastIo{
    template <typename T>
    inline bool scan_d (T &ret) {
        char c;
        int sgn;
        if (c = getchar(), c == EOF) return 0; //EOF
        while (c != '-' && (c < '0' || c > '9') )
            if((c = getchar()) == EOF) return 0;
        sgn = (c == '-') ? -1 : 1;
        ret = (c == '-') ? 0 : (c - '0');
        while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
        ret *= sgn;
        return 1;
    }
    template<typename T>
    void print(T x) {
        static char s[33], *s1; s1 = s;
        if (!x) *s1++ = '0';
        if (x < 0) putchar('-'), x = -x;
        while(x) *s1++ = (x % 10 + '0'), x /= 10;
        while(s1-- != s) putchar(*s1);
    }
    template<typename T>
    void println(T x) {
        print(x); putchar('\n');
    }

}

/// ------------------------------ code line ------------------------------//



typedef llt int_t;
/**< 非递归的gcd */
int_t gcd(int_t a,int_t b){
    if (0L == a || 0L == b) return 1;
    if ( a < 0 ) a = -a;
    if ( b < 0 ) b = -b;
    while(b){
        int_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

/** \非递归的扩展欧几里德算法
 *返回a、b的gcd，同时x、y满足ax+by=gcd
 */
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
/**< 求a相对于p的逆元，a、p互质才存在逆元 */
int_t inv(int_t a,int_t p){
    int_t x,y , r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    return ( x < 0 ) ? x+p : x;
}

/**< 快速乘取模 */
int_t multiMod(int_t a,int_t b,int_t mod){
    int_t ret = 0LL;
    a %= mod;
    while( b ){
        if ( b & 1LL ) ret = ( ret + a ) % mod, --b;
        b >>= 1LL;
        a = ( a + a ) % mod;
    }
    return ret;
}
/**< 快速幂取模 */
int_t Pow_Mod( int_t x,int_t n , int_t mod ){
    int_t ans = 1LL;
    x %= mod;
    while ( n ){
        if ( n & 1LL ) ans = multiMod(ans,x,mod); //ans = ans*x%mod;
        n >>= 1; x = multiMod(x,x,mod); //x = x*x%mod;
    }
    return ans;
}

/**<  Miller-Rabin测试,测试n是否为素数 */
bool Miller_Rabin(int_t n,int repeat){
    if ( 2LL == n || 3LL == n ) return true;
    if ( !( n & 1LL ) ) return false;

    /**< 将n分解为2^s*d */
    int_t d = n - 1LL;
    int s = 0;
    while( !( d & 1LL ) ) ++s, d>>=1LL;

    //srand((unsigned)time(0));
    for(int i=0;i<repeat;++i){ /**< 重复repeat次  */
        int_t a = rand() % ( n - 3 ) + 2;//取一个随机数,[2,n-1)
        int_t x = Pow_Mod(a,d,n);
        int_t y = 0LL;
        for(int j=0;j<s;++j){
            y = multiMod(x,x,n);
            if ( 1LL == y && 1LL != x && n-1LL != x ) return false;
            x = y;
        }
        if ( 1LL != y ) return false;
    }
    return true;
}



/** \Pollard-Rho方法分解整数因子
 *  n == 1 特判 会死循环
 *
 */
int const Repeat = 5; /**< Miller_Rabin 测试次数 */
int_t Fac[100]; /**< 质因数分解结果（刚返回时是无序的） */
int FCnt; /**<  质因数的个数。数组小标从0开始 */
int_t Pollard_Rho(int_t n,int_t c){
    int_t k = 2;
    int_t x = rand() % n;
    int_t y = x;
    for (llt i = 1;;i++){
        x = ( multiMod(x,x,n) - c ) % n;
        if ( x < 0 ) x += n;
        int_t d = gcd(y-x,n);
        if (d!=1LL && d!=n) return d;
        if (y == x) return n;
        if ( i == k ) y = x, k <<= 1;
    }
}
void Find_fac(llt n){
    if ( Miller_Rabin(n,Repeat) ){
        Fac[FCnt++] = n;
        return;
    }
    llt p;
    while( ( p = Pollard_Rho(n,rand()%(n-3)+3) ) == n );
    Find_fac(p);
    Find_fac(n/p);
}


int main(){
    int_t n;
    while ( scanf("%I64d",&n) != EOF){
        if ( n == 1LL ) {
            printf("is not a D_num\n");
            continue;
        }
        FCnt = 0;
        Find_fac(n);
        sort(Fac,Fac+FCnt);
        if ( FCnt == 3 && Fac[0] == Fac[1] && Fac[1] == Fac[2] )
            printf("%I64d %I64d %I64d\n",Fac[0],Fac[0]*Fac[0],n);
        else if ( FCnt == 2 && Fac[0] != Fac[1] )
            printf("%I64d %I64d %I64d\n",Fac[0],Fac[1],n );
        else printf("is not a D_num\n");
    }

    return 0;
}
