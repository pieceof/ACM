#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;
using namespace std;

/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/

/*Kruskal 算法
 *注意：点是从1到n编号
 *Ecnt = 0
 */

typedef int weight_t;
const int SIZE_V = 110;
const int SIZE_E = 110*111;
int Father[SIZE_V];
int Ecnt = 0;
//int n;  // 此处写点的全局变量

//并查集算法
void init(int vn){
    for(int i = 0;i <= vn;++i)
        Father[i] = i;
}
int find(int x){
    return (Father[x] == x) ? x :
         Father[x] = find(Father[x]);
}
inline void unite(int x,int y){
    Father[find(y)] = Father[find(x)];
}

struct edge_t{
    int s,e;
    weight_t w;
    friend bool operator < (edge_t const&a,edge_t const&b){
        if (a.w != b.w) return a.w < b.w;
        if (a.s != b.s) return a.s < b.s;
        return a.e < b.e;
    }
}Edge[SIZE_E];

inline void mkEdge(int a,int b,weight_t w){
    if (a > b)swap(a,b);
    Edge[Ecnt].s = a;
    Edge[Ecnt].e = b;
    Edge[Ecnt++].w = w;
}

weight_t Kruskal(int vn,int en){
//    init(vn);
    sort(Edge,Edge+en);


    weight_t min_ret = INT_MAX;
    bool isok = 0;
//    int cnt = 0;
    for (int l = 0;l < en;++l ){
        init(vn);
        int cnt = 0;
        int maxr = INT_MIN,minr=INT_MAX;
        for (int r = l;r < en; ++r){
            if ( find(Edge[r].s) == find(Edge[r].e))
                continue;

            maxr = max(maxr,Edge[r].w);
            minr = min(minr,Edge[r].w);

            unite(Edge[r].s,Edge[r].e);
            cnt++;
            if ( cnt == vn-1 ){
                isok = 1;
                min_ret = min( min_ret , maxr-minr);
//                deBug(maxr-minr);
//                deBug(maxr);
//                deBug(minr);
                break;
            }
        }

    }
    if ( !isok ) return -1;
    return min_ret;
}
int main()
{
    int n,m;
    while( scanf("%d%d",&n,&m) != EOF ){
        if ( n == 0  && m == 0 ) return 0;
        int a,b,x;
        Ecnt = 0;
        for (int i = 0;i < m;++i ){
            scanf("%d%d%d",&a,&b,&x);
            mkEdge(a,b,x);
        }
        int ans = Kruskal(n,m);
        printf("%d\n",ans);
    }

    return 0;
}
