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
#include <stack>
#include <queue>

#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a),-1,sizeof(a))
#define varName(x) #x
#define deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define deBugp(exp1, exp2) cout<< " == > " << "(" << #exp1<<" : "<< (exp1) << "," << #exp2 << " : " << (exp2) << ")" << endl
#define Case   printf("Case %d:\n",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path)  freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
#define eps 1e-9
using namespace std;
typedef long long llt;
double const PI = acos(-1.0);

template<typename T>
T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }

template<typename T>
inline T lcm(T a, T b) { return a / gcd(a, b) * b; }



///-------------------------   math ------------------------///

inline double ln(double const &x) { return log(x) / log(exp(1.0)); }

/**< 圆锥截体 体积 输入上圆半径r1, 下圆半径r2 ,高h */
inline double Vfrustum(double const &r1, double const &r2, double const &h) {
    return PI * h * (r1 * r1 + r2 * r2 + r1 * r2) / 3;
}

/**< 海伦公式 ,已知三角形三边求面积 */
inline double Heron(double a, double b, double c) {
    double _p = (a + b + c) / 2.0;
    return sqrt(_p * (_p - a) * (_p - b) * (_p - c));
}

///----------------------- debug tools ---------------------///

template<typename T>
void ArrayCin(T *a, int n, int pos = 0) { for (int i = pos; i < n; ++i) cin >> a[i]; }

template<typename T>
void ArrayDisp(T *a, int n) {
    cout << "===> : ";
    for (int i = 0; i < n; ++i)cout << std::right << setw(2) << a[i] << " ";
    cout << endl;
}

template<typename T>
void ArrayDisp(T *a, int n, int m, int twoLen) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << std::right << setw(2) << *(a + i * twoLen + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
///------------------- faster IO --------------------//

namespace fastIo {
    template<typename T>
    inline bool scan_d(T &ret) {
        char c;
        int sgn;
        if (c = getchar(), c == EOF) return 0; //EOF
        while (c != '-' && (c < '0' || c > '9'))
            if ((c = getchar()) == EOF) return 0;
        sgn = (c == '-') ? -1 : 1;
        ret = (c == '-') ? 0 : (c - '0');
        while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
        ret *= sgn;
        return 1;
    }

    template<typename T>
    void print(T x) {
        static char s[33], *s1;
        s1 = s;
        if (!x) *s1++ = '0';
        if (x < 0) putchar('-'), x = -x;
        while (x) *s1++ = (x % 10 + '0'), x /= 10;
        while (s1-- != s) putchar(*s1);
    }

    template<typename T>
    void println(T x) {
        print(x);
        putchar('\n');
    }

}

/// ------------------------------ code line ------------------------------//


