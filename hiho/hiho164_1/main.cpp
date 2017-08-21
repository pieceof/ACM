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


const int SIZE = 2000;
int lz[SIZE],rz[SIZE];
char str[SIZE];
int main(){
    int t;scanf("%d",&t);while ( t-- ){
        CLEAR(lz);CLEAR(rz);
        scanf("%s",str);
        int len = strlen(str);
        lz[0] = (str[0] == '1') ? 1:0;
        for (int i = 1;i < len ;++i )
            lz[i] = (str[i] == '1')? lz[i-1]+1 : lz[i-1];
        rz[len-1] = (str[len-1] == '0') ? 1:0;
        for (int i = len-2; i >= 0;--i )
            rz[i] = (str[i] == '0')? rz[i+1]+1 : rz[i+1];
//        ArrayDisp(lz,len);
//        ArrayDisp(rz,len);
        int ans = INT_MAX;
        for ( int i = 0;i < len;++i )
            ans = min( ans,lz[i]+rz[i]-1);
        Ans(ans);
    }
    return 0;
}
