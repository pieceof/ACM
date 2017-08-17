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
typedef long long llt;
///-------------------------   math ------------------------///
const double eps = 1e-9;
const double PI = acos(-1);
inline double ln(double const&x ){ return log(x)/log(exp(1));}
inline double Vfrustum( double const&r1,double const&r2,double const&h ){
    return PI * h * ( r1*r1 + r2*r2 + r1*r2 )/3;
}

///----------------------- debug tools ---------------------///
void ArrayCin( int *a ,int n ,int pos = 0){
    for (int i = pos;i < n;++i ) scanf("%d",a+i);
}
void ArrayDisp(int *a,int n ){
//    std::cout << varName(a) << "  : ";
    printf("===> : ");
    for (int i = 0;i < n;++i )printf("%4d ",a[i]);printf("\n");
}
template <typename T>
void ArrayDisp(T **a,int n,int m ){
    for (int i = 0;i < n;++i ){
        for (int j = 0;j < m;++j ){
            cout << *((int*)a + n*i + j) << " ";
        }cout << endl;
    }cout << endl;
}
///------------------- faster IO --------------------//
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
/// ------------------------------ code line ------------------------------//




const int SIZE = 5000;

map<string,int> strID;
int StrCnt;
int getStrId( string const&str ){
    if ( strID.count(str) )return strID[str];
    return strID[str] = StrCnt++;
}
void init1( ){
    StrCnt = 0;
    getStrId("English");
}
struct edge_t{
    int node;
    llt value;
    int next;
}Edge[SIZE<<1];
int Ecnt ; // = 0
int Ver[SIZE];
void mkEdge( int a,int b ,llt v){
    Edge[Ecnt].node = b;
    Edge[Ecnt].value = v;
    Edge[Ecnt].next = Ver[a];
    Ver[a] = Ecnt++;

    Edge[Ecnt].node = a;
    Edge[Ecnt].value = v;
    Edge[Ecnt].next = Ver[b];
    Ver[b] = Ecnt++;
}
void init2(){
    Ecnt = 1;
    CLEAR(Ver);
}

int layer[SIZE];
void bfs( ){
    CLEAR(layer);
    layer[0] = 1;
    queue<int> q;
    q.push(0);
    while ( !q.empty( ) ){
        int u = q.front(); q.pop();
        for (int next = Ver[u]; next ; next = Edge[next].next){
            int v = Edge[next].node;
            if ( layer[v] == 0 ){
                layer[v] = layer[u] + 1;
                q.push(v);
            }

        }
    }
//    for (int i = 0;i < 5;++i )cout << layer[i] << endl;
}

int n,m;
llt cost[SIZE];
int pre[SIZE];
bool vis_layer[SIZE];
void bfs2(){
    queue<int> q;
    q.push(0);
    int now_layer = 1;
    CLEAR(vis_layer);
    fill( cost,cost+n,INT_MAX );
    vis_layer[1] = 1;
    while (!q.empty() ){
        int u = q.front(); q.pop();
        if ( layer[u] != now_layer){
            vis_layer[now_layer+1] = 1;
            now_layer = layer[u];
        }
        for (int next = Ver[u]; next ; next = Edge[next].next){
            int v = Edge[next].node;
            llt c = Edge[next].value;
            if ( vis_layer[ layer[v] ] ) continue;
            if ( cost[v] >  c ) { cost[v] = c;
                q.push(v);
            }
        }
    }
}

string str,str2;
bool read( ){
    init1();
    init2();
    if ( !(cin>>n>>m ) )return false;

    for (int i = 0;i < n;++i ){
//        scanf("%s",str.c_str());
        cin>>str;
        getStrId(str);
    }
    n++;
    llt v;
    for (int i = 0;i < m;++i ){
        cin>>str>>str2>>v;
//        scanf("%s%s%d",str.c_str(),str2.c_str(),&v);
        int x = getStrId(str);
        int y = getStrId(str2);
//        deBugPair(x,y);
        mkEdge(x,y,v);
    }
    return true;
}

void solve( ){
    bool isok = 1;
    llt ans = 0;
    for (int i = 1;i < n;++i ){
        if ( cost[i] == INT_MAX )isok = 0;
        ans += cost[i];
    }
    if ( isok )cout << ans << endl;
    else printf("Impossible\n");
}
int main(){
    while (read()){

        bfs();
        bfs2();
        solve();
    }
}
