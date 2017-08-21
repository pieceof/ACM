#include <cstdio>
#include <set>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <climits>
#include <assert.h>
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



const int MOD = 20071027;


///*
struct node_t {
    node_t* child[27];//26个儿子
//	int idx;//对应解释的序号
//    bool suffix;//是否为后缀
    int cnt;
}Node[1100000];
int toUsed = 1;

//插入单词
void Insert(char const word[] ) {
    node_t* loc = Node;
    for(int i = 0; word[i]; ++i) {
//        loc->cnt++;
        int sn = word[i] - 'a';
        if ( !loc->child[sn] ) loc->child[sn] = Node + toUsed ++;
        loc = loc->child[sn];
    }
    loc->cnt++;
//    loc->suffix = 1;
}

const int SIZE = 310000;
char str[SIZE] , word[200];
int dp[SIZE];

//查找单词,返回出现的次数
void Find(char const word[],int idx) {
    node_t* loc = Node;
    for(int i = 0; word[i] ; ++i) {
//        if ( loc->suffix ) return 1;
        int sn = word[i] - 'a';
        if ( !loc->child[sn] ) return ;
        loc = loc->child[sn];
        if ( loc->cnt ){
            dp[idx] += (dp[idx+i+1] * loc->cnt)%MOD;
            dp[idx] %= MOD;
        }
    }
//    dp[idx] += (dp[idx+strlen(word)] + loc->cnt)%MOD;
//    dp[idx] %= MOD;
//    return loc->cnt;
}
//*/

bool read( ){
    if ( EOF == scanf("%s",str ) )return false;
    int n; scanf("%d",&n);
    ///====== init ====== //
    toUsed = 1;
    CLEAR(Node);
    CLEAR(dp);
    ///================= //
    for ( int i = 0;i < n;++i ){
        scanf("%s",word);
        Insert(word);
//        cout << word << endl;
    }
    return true;
}
int solve( ){
    int len = strlen(str);
    dp[len] = 1;
    for (int i = len-1;i >= 0;--i )
        Find(str+i,i);
    return dp[0];
}
int kase = 1;
int main(){
    while ( read() )
        printf("Case %d: %d\n",kase++,solve());
    return 0;
}

