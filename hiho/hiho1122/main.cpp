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



typedef int weight_t;
/** \二分图匹配（匈牙利算法的DFS实现）
 * 临界表 无向边
 * CALL:ret=hungary();输出最大匹配数
 * 时间复杂度:O(VE);
 * gn gm 为两个集合的大小，从0 ～ n-1 编号
 *********
   初始化Graph 为0；
 *********
 */
// 存储二分图 左边的集合跟右边集合边的信息
// 如果有边为 1 , 没边为 0
const int SIZE_V = 2000+500;
const int SIZE_E = 10000+500;
struct edge_t{
    int node;
    int next;
}Edge[SIZE_E];
int Ecnt ; // = 0
int Ver[SIZE_V];
void mkEdge( int a,int b ){
    Edge[Ecnt].node = b;
    Edge[Ecnt].next = Ver[a];
    Ver[a] = Ecnt++;

    Edge[Ecnt].node = a;
    Edge[Ecnt].next = Ver[b];
    Ver[b] = Ecnt++;
}
void init_Graph(){
    Ecnt = 1;
    CLEAR(Ver);
}
int Link[SIZE_V]; //对于右边集合的 i, link[i]即对应左边集合的 node
bool vis[SIZE_V];
/**< 对于左边的集合的node节点 求增广路径 */
bool DFS( int u){
    /**< 对右边集合的每个结点遍历一次 */
    for (int next = Ver[u];next;next = Edge[next].next ){
        int v = Edge[next].node;
        /**< 如果已经找过 */
        if ( vis[v] )continue; vis[v] = true;
        /**< 如果这个点上未盖点 或者该点还能找到增广路径 */
        if ( Link[v] == -1 || DFS( Link[v] ) ){
            Link[v] = u;
            return true;
        }
    }
    return false;
}

int hungary(int n ){
    int ret = 0;
    memset(Link , -1 ,sizeof(Link));
    //对左边集合的每个点求增广路径
    for (int u = 1;u <= n;++u){
        memset(vis,0,sizeof(vis));
        if (DFS(u)) ret++;
    }
    return ret;
}

int main(){
    int n,m;
//    int t;scanf("%d",&t);while( t-- ){
    while ( scanf("%d%d",&n,&m) != EOF ){
        int x,y;
        init_Graph();
        while ( m-- ){
            scanf("%d%d",&x,&y);
            mkEdge(x,y);
        }
        printf("%d\n",hungary(n)/2);
    }
    return 0;
}
