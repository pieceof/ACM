#include <cstdio>
#include <algorithm>
#include <cmath>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
const int SIZE = 300000;

int _RMQ_max[SIZE][20]; //预处理数组
int _RMQ_min[SIZE][20]; //预处理数组
void getRMQ( int const a[] ,int n ){
    for (int i = 0;i < n;++i) _RMQ_min[i][0] = a[i],_RMQ_max[i][0] = a[i];;
    for (int j = 1;(1<<j) <= n;++j )
        for (int i = 0;i+(1<<j) <=n;++i )
            _RMQ_min[i][j] = min( _RMQ_min[i][j-1] ,_RMQ_min[i+(1<<(j-1))][j-1] ),
            _RMQ_max[i][j] = max( _RMQ_max[i][j-1] ,_RMQ_max[i+(1<<(j-1))][j-1] );
}
int querry_min(int A,int B){
    int k = (int)(log((double)(B+1-A))/log(2.0));
    return min( _RMQ_min[A][k] , _RMQ_min[B+1-(1<<k)][k] );
}
int querry_max(int A,int B){
    int k = (int)(log((double)(B+1-A))/log(2.0));
    return max( _RMQ_max[A][k] , _RMQ_max[B+1-(1<<k)][k] );
}

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

int a[SIZE];
int main(){
    int n,m;
    while ( scan_d(n) ){
        scan_d(m);
        for (int i = 0;i < n ;++i ) scan_d(a[i]);
        getRMQ(a,n);
        int x,y;
        while( m -- ) {
            scan_d(x),scan_d(y);x--,y--;
            println(querry_max(x,y) - querry_min(x,y));
        }
    }
    return 0;
}
