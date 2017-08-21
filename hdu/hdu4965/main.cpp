#include <cstdio>
#include <set>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <climits>
//#include <assert.h>
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
typedef int llt;
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



//const int MOD = 1000000007;
const int Cube_SIZE = 10;   //æÿ’Û¥Û–°
struct Cube{
    int col,row;
    llt mat[Cube_SIZE][Cube_SIZE];
    void to_Unit(){ for (int i = 0;i < row;++i )for (int j = 0;j < col;++j )mat[i][j] = (i==j)? 1 : 0;}
};

///æÿ’Û≥À∑®
Cube _Multiply(Cube const&A,Cube const&B,llt mod){
    Cube _tmpCube;
    _tmpCube.row = A.row;
    _tmpCube.col = B.col;
    for (int i = 0;i < A.row;++i)for (int j = 0;j < B.col;++j){
        _tmpCube.mat[i][j] = 0;
        for (int k = 0;k < B.row;++k){
            _tmpCube.mat[i][j] += A.mat[i][k]*B.mat[k][j];
            _tmpCube.mat[i][j] %= mod;
        }
    }
    return _tmpCube;
}
///æÿ’ÛøÏÀŸ√›
Cube power_Cube(Cube &A,llt n,llt mod)
{
    Cube _tmpCube;
    _tmpCube.row = A.row , _tmpCube.col = A.col;
//    assert(A.col == A.row );
    _tmpCube.to_Unit();
    while(n){
        if(n & 1) _tmpCube = _Multiply(_tmpCube, A ,mod);
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
//================================== code line ======= ========================//


llt n,k;
Cube arr1,arr2;

int mat1[1100][1100];
int mat2[1100][1100];

bool read( ){
    if ( EOF == scanf("%d%d",&n,&k) ) return false;
    if ( n == 0 && k == 0 ) return false;
    for (int i = 0;i < n;++i ) for (int j = 0;j < k;++j )
        scanf("%d",&mat1[i][j]);
    for (int i = 0;i < k;++i ) for (int j = 0;j < n;++j )
        scanf("%d",&mat2[i][j]);
    return true;
}

Cube mult(  ){
    Cube _tmpCube;
    _tmpCube.col = _tmpCube.row = k;
    for (int i = 0;i < k;++i)for (int j = 0;j < k;++j){
        _tmpCube.mat[i][j] = 0;
        for (int s = 0;s < n;++s){
            _tmpCube.mat[i][j] += mat2[i][s]*mat1[s][j];
            _tmpCube.mat[i][j] %= 6;
        }
    }
    return _tmpCube;
}

Cube c_c,c_m;
int mata[1100][1100];
int matb[1100][1100];

void mult1( int const m1[][1100],int const m2[][Cube_SIZE],int ma[][1100],int r,int p,int q){
    for (int i = 0;i < r;++i)for (int j = 0;j < q;++j){
        ma[i][j] = 0;
        for (int s = 0;s < p;++s){
            ma[i][j] += m1[i][s]*m2[s][j];
            ma[i][j] %= 6;
        }
    }
}
void mult2( int const m1[][1100],int const m2[][1100],int ma[][1100],int r,int p,int q){
    for (int i = 0;i < r;++i)for (int j = 0;j < q;++j){
        ma[i][j] = 0;
        for (int s = 0;s < p;++s){
            ma[i][j] += m1[i][s]*m2[s][j];
            ma[i][j] %= 6;
        }
    }
}
llt solve() {
    c_c = mult();
    c_c = power_Cube(c_c,n*n-1,6);
    mult1(mat1,c_c.mat,mata,n,k,k);
    mult2(mata,mat2,matb,n,k,n);
//    c_m = _Multiply(arr1,c_c,6);
//    c_m = _Multiply(c_m,arr2,6);
    int ans = 0;
    for (int i = 0 ;i < n;++i )for (int j = 0;j < n;++j )
        ans += matb[i][j];
    return ans;
}
int main(){
//    ios::sync_with_stdio(false);
//    int t;scanf("%d",&t);while(t--){
    while ( read() ){
        printf("%d\n",solve());
    }
    return 0;
}
