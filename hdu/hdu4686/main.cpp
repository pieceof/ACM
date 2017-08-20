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
llt a,b,n,m;

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
llt solve(llt A0,llt AX,llt AY,llt B0,llt BX,llt BY,llt n) {
    arr.spec = 5;
    llt (*mat)[Cube_SIZE] = arr.mat;
    mat[0][0] = 1;mat[0][1] = AX*BX%MOD;mat[0][2] = AX*BY%MOD;mat[0][3] = AY*BX%MOD;mat[0][4] = AY*BY%MOD;
    mat[1][0] = 0;mat[1][1] = AX*BX%MOD;mat[1][2] = AX*BY%MOD;mat[1][3] = AY*BX%MOD;mat[1][4] = AY*BY%MOD;
    mat[2][0] = 0;mat[2][1] = 0;        mat[2][2] = AX%MOD;   mat[2][3] = 0;        mat[2][4] = AY%MOD;
    mat[3][0] = 0;mat[3][1] = 0;        mat[3][2] = 0;        mat[3][3] = BX%MOD;   mat[3][4] = BY%MOD;
    mat[4][0] = 0;mat[4][1] = 0;        mat[4][2] = 0;        mat[4][3] = 0;        mat[4][4] = 1;

    if ( n == 0 ) return 0;

    if ( n == 1 ) { return A0*B0%MOD; }
//    if ( n == 2 ) { return }

    arr = power_Cube(arr,n-1,MOD);
    return (
            ( (mat[0][0]*(A0*B0%MOD)%MOD) + (mat[0][1]*(A0*B0%MOD)%MOD) )%MOD
            +
            ( (mat[0][2]*(A0)%MOD) + (mat[0][3]*(B0%MOD)%MOD) )% MOD +
                mat[0][4]
            )%MOD;
//        ArrayDisp((llt*)arr.mat,2,2,15);
}
int main(){
//    ios::sync_with_stdio(false);
    llt A0,AX,AY,B0,BX,BY;
//    int t;scanf("%d",&t);
    while ( scanf("%I64d",&n) != EOF ){
        scanf("%I64d%I64d%I64d",&A0,&AX,&AY);
        scanf("%I64d%I64d%I64d",&B0,&BX,&BY);
        llt ans = solve(A0,AX,AY,B0,BX,BY,n);
        printf("%I64d\n",ans);
    }
    return 0;
}
