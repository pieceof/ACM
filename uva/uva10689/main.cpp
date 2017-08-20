#include <cstdio>
#include <set>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <climits>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <set>
#include <queue>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define  deBugPair(exp1,exp2) cout<< " == > " << "(" << #exp1<<" : "<< (exp1) << "," << #exp2 << " : " << (exp2) << ")" << endl
#define Case printf("Case %d:\n",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
///-------------------------   math ------------------------///
typedef long long llt;
const double eps = 1e-9;
const double PI = acos(-1);
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
//    std::cout << varName(a) << "  : ";
    cout << "===> : ";
    for (int i = 0;i < n;++i )cout << std::right << setw(2)<<a[i]<<" ";cout << endl;
}
template <typename T>
void ArrayDisp(T *a,int n,int m ,int twoLen){
    for (int i = 0;i < n;++i ){
        for (int j = 0;j < m;++j ){
            cout << std::right << setw(2)<< *(a +i*twoLen +j) << " ";
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
        while (c != '-' && (c < '0' || c > '9') ) {
            if((c = getchar()) == EOF) return 0;
        }
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



const int MOD = 1000000007;
const int Cube_SIZE = 15;   //矩阵大小
struct Cube{
    int spec;
    llt mat[Cube_SIZE][Cube_SIZE];
};
//单位矩阵
Cube const _UnitCube = {15,
{
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
}
};
///矩阵乘法
Cube _Multiply(Cube const&A,Cube const&B,llt mod){
    Cube _tmpCube;
    _tmpCube.spec = A.spec;
    for (int i = 0;i < A.spec;++i)
    for (int j = 0;j < A.spec;++j){
        _tmpCube.mat[i][j] = 0;
        for (int k = 0;k < A.spec;++k){
            _tmpCube.mat[i][j] += A.mat[i][k]*B.mat[k][j];
            _tmpCube.mat[i][j] %= mod;
        }
    }
    return _tmpCube;
}
///矩阵快速幂
Cube power_Cube(Cube &A,llt n,llt mod)
{
    Cube _tmpCube = _UnitCube;
    _tmpCube.spec = A.spec;
    while(n){
        if(n & 1)
            _tmpCube = _Multiply(_tmpCube, A ,mod);
        A = _Multiply(A, A, mod);
        n >>= 1;
    }
    return _tmpCube;
}

llt pow_mod( llt x, llt n,llt mod){
    llt ans = 1LL;
    while(n){
        if ( n&1 ) ans = (ans*x)%mod;
        n >>= 1;
        x = (x*x)%mod;
    }
    return ans;
}
Cube arr;
llt mod[5] = {1,10,100,1000,10000};
llt solve(llt a,llt b,llt n,llt m) {
    arr.spec = 2;
    llt (*mat)[Cube_SIZE] = arr.mat;
    mat[0][0] = 1;mat[0][1] = 1;
    mat[1][0] = 1;mat[1][1] = 0;
    if ( n == 0 ) return a%mod[m];
    if ( n == 1 ) return b%mod[m];

//        ArrayDisp((llt*)mat,2,2,15);
    arr = power_Cube(arr,n-1,mod[m]);
    return (mat[0][0]*b%mod[m] + mat[0][1]*a%mod[m])%mod[m] ;
}
int main(){
//    ios::sync_with_stdio(false);
    llt a,b,n,m;
    int t;scanf("%d",&t);while(t--){
        scanf("%lld%lld%lld%lld",&a,&b,&n,&m);
        llt ans = solve(a,b,n,m);
        printf("%lld\n",ans);
    }
    return 0;
}
