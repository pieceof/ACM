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



int main(){
    double a[3],l;
    int t;scanf("%d",&t);while(t--){
        scanf("%lf%lf%lf%lf",a+0,a+1,a+2,&l);
        sort(a,a+3);
        double ans = 0;
        /**< 先把最短的边 添到第二长 */
        if ( a[1]-a[0] >= l ){
            a[0] += l ; l = 0;
        }else{
            l -= a[1]-a[0] ; a[0] = a[1];
            /**< 再把两个第二长 添到第一长 */
            if ( (a[2]-a[1])*2 >= l ){
                a[0] += l/2;
                a[1] += l/2;
            }else{
                l -= (a[2]-a[1])*2;
                /**< 最后把三个边一起加 */
                a[1] = a[0] = a[2];
                a[0] += l/3;
                a[1] += l/3;
                a[2] += l/3;
            }
        }
//        deBug(a[0]);
//        deBug(a[1]);
//        deBug(a[2]);
        printf("%.9f\n",Heron(a[0],a[1],a[2]));
    }
}
