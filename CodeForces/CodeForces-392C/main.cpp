//////////////////////////////////////////////////////////
//                       _oo0oo_                        //
//                      o8888888o                       //
//                      88" . "88                       //
//                      (| -_- |)                       //
//                      0\  =  /0                       //
//                    ___/`---'\___                     //
//                  .' \\|     |// '.                   //
//                 / \\|||  :  |||// \                  //
//                / _||||| -:- |||||- \                 //
//               |   | \\\  -  /// |   |                //
//               | \_|  ''\---/''  |_/ |                //
//               \  .-\__  '-'  ___/-. /                //
//             ___'. .'  /--.--\  `. .'___              //
//          ."" '<  `.___\_<|>_/___.' >' "".            //
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |          //
//         \  \ `_.   \_ __\ /__ _/   .-` /  /          //
//     =====`-.____`.___ \_____/___.-`___.-'=====       //
//                       `=---='                        //
//                                                      //
//                                                      //
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      //
//                                                      //
//               佛祖保佑         永无BUG               //
//////////////////////////////////////////////////////////

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
typedef long long llt;
double const PI = acos(-1.0);

///-------------------------   math ------------------------///

inline double ln(double const&x ){ return log(x)/log(exp(1.0));}
/**< 圆锥截体 体积 输入上圆半径r1, 下圆半径r2 ,高h */
inline double Vfrustum( double const&r1,double const&r2,double const&h ){
    return PI * h * ( r1*r1 + r2*r2 + r1*r2 )/3;
}
/**< 海伦公式 ,已知三角形三边求面积 */
inline double Heron( double a,double b,double c ){
    double _p = (a+b+c)/2.0;
    return sqrt( _p*(_p-a)*(_p-b)*(_p-c) );
}

///----------------------- debug tools ---------------------///

template <typename T>
void ArrayCin( T *a ,int n ,int pos = 0){ for (int i = pos;i < n;++i ) cin>>a[i];}

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



const llt MOD = 1000000007;
const int Cube_SIZE = 100;   //矩阵大小
struct Cube{
    int spec;
    llt mat[Cube_SIZE][Cube_SIZE];
    void init(){
        CLEAR(mat);
        for (int i = 0;i < spec;++i ) for (int j = 0;j < spec;++j )
            if ( i == j ) mat[i][j] = 1;
    }
};
//单位矩阵

///矩阵乘法
Cube _Multiply(Cube const&A,Cube const&B,llt mod){
    Cube _tmpCube;
    _tmpCube.spec = A.spec;
    for (int i = 0;i < A.spec;++i)
    for (int j = 0;j < A.spec;++j){
        _tmpCube.mat[i][j] = 0;
        for (int k = 0;k < A.spec;++k){
            _tmpCube.mat[i][j] += A.mat[i][k]*B.mat[k][j]%MOD;
            _tmpCube.mat[i][j] %= mod;
        }
    }
    return _tmpCube;
}
///矩阵快速幂
Cube power_Cube(Cube &A,llt n,llt mod)
{
    Cube _tmpCube;
    _tmpCube.spec = A.spec;
    _tmpCube.init();
    while(n){
        if(n & 1)
            _tmpCube = _Multiply(_tmpCube, A ,mod);
        A = _Multiply(A, A, mod);
        n >>= 1;
    }
    return _tmpCube;
}

const int SIZE = 100;
llt C[SIZE][SIZE] = {0};
llt fib[SIZE] = {1,1};
llt bini[SIZE] = {1};
void initC( ){
    C[0][0] = C[1][0] = C[1][1] = 1;
    for (int i = 2;i < SIZE;++i )
        for (int j = 1;j <= i ;++j)
            C[i][0] = 1,
            C[i][j] = (C[i-1][j] + C[i-1][j-1])% MOD ;
    for (int i = 2;i < SIZE;++i )
        fib[i] = (fib[i-1] + fib[i-2]) % MOD;
    for (int i = 1;i < SIZE;++i ){
        bini[i] = bini[i-1] * 2 % MOD;
    }
}

llt n,k;

llt orz[100];
int main(){
//    readfile("in.txt");
//    writefile("out.txt");
    initC();
    Cube arr;
//    int t;scanf("%d",&t);
    while ( scanf("%I64d%I64d",&n,&k) != EOF ){
        llt n1 = fib[1];
        llt n2 = (fib[1]+ fib[2]*bini[k]%MOD  )%MOD;
        if ( n == 1 ){
            printf("%I64d\n",n1);continue;
        }
        if ( n == 2 ){
            printf("%I64d\n",n2 );continue;
        }
        arr.spec = (k+1)*2+1;
        const int &sp = arr.spec;
        CLEAR(arr.mat);
        for (int i = 0;i <= k;++i ){
            for (int j = 0;j <= i;++j ){
                if ( i <= k ) arr.mat[i][j+k+1] = C[i][j];
                arr.mat[i][j] = arr.mat[i+k+1][j] = C[i][j];
            }
        }
        arr.mat[sp-1][k] = arr.mat[sp-1][k+k+1] = arr.mat[sp-1][sp-1] = 1;
//        for (int i = 0;i < sp;++i ){ for (int j = 0;j < sp;++j ){printf("%2d ",arr.mat[i][j]);}printf("\n"); }
        arr = power_Cube(arr,n-2,MOD);
//        for (int i = 0;i < sp;++i ){ for (int j = 0;j < sp;++j ){printf("%2d ",arr.mat[i][j]);}printf("\n"); }
        llt tmp = 1;
        for (int i = 0;i <= k;++i ){
            orz[i] = fib[2]*tmp%MOD;
            orz[i+k+1] = fib[1]*tmp%MOD;
            tmp = tmp*3%MOD;
        }
        orz[sp-1] = n2;
        llt ans = 0;
        for (int i = 0;i < sp;++i ){
            ans += arr.mat[sp-1][i]*orz[i]%MOD;
            ans %= MOD;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

