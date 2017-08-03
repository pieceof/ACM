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
const int SIZE_V = 1050;
const int SIZE_E = SIZE_V*SIZE_V;
int Father[SIZE_V];
int Ecnt = 0;
int n;  // 此处写点的全局变量

//并查集算法
void _init_set(int vn){
    for(int i = 0;i <= vn;++i)
        Father[i] = i;
}
int _find(int x){
    return (Father[x] == x) ? x :
         Father[x] = _find(Father[x]);
}
inline void _unite(int x,int y){
    Father[_find(y)] = Father[_find(x)];
}

struct point_t{
    int x,y;
    point_t( int xx = 0,int yy = 0):x(xx),y(yy) {};
}Point[SIZE_V];

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
inline int Dist( const point_t&a,const point_t&b ){
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

void init_edge( int n ){
    for (int i = 1;i <= n;++i ){
        for (int j = i+1; j <= n ;++j ){
            mkEdge(i,j,Dist(Point[i],Point[j]));
        }
    }
}

int used_edge[SIZE_V];
int used_edge_cnt = 0;


weight_t Kruskal_1(int vn,int en){
    _init_set(vn);
    sort(Edge,Edge+en);

    weight_t ret = 0;
    for (int i = 0;i < en; ++i){
        if ( _find(Edge[i].s) == _find(Edge[i].e))
            continue;
        ret += Edge[i].w;
        used_edge[used_edge_cnt++] = i;
        _unite(Edge[i].s,Edge[i].e);
        --vn;
        if (1 == vn)break;
    }
    return ret;
}
weight_t Kruskal_2(int vn,int c){
//    sort(Edge,Edge+Ecnt);
    weight_t ret = 0;
    for (int i = 0;i < Ecnt; ++i){
        if ( _find(Edge[i].s) == _find(Edge[i].e))
            continue;
        ret += Edge[i].w;
        _unite(Edge[i].s,Edge[i].e);
        c++;
        if ( c == Ecnt )break;
    }
    return ret;
}


void select_edge( ){
    for (int i = 0 ;i < used_edge_cnt;++i )
        Edge[i] = Edge[ used_edge[i] ];
}


int sub[10][SIZE_V];
int cost[10];
int sub_cnt[10];
int main()
{

    int t;scanf("%d",&t);while(t--){
        int n,q;
        scanf("%d%d",&n,&q);
        for ( int i = 0;i < q;++i ){
            scanf("%d%d",sub_cnt+i,cost+i);
            for (int j = 0; j < sub_cnt[i];++j)
                scanf("%d",&sub[i][j]);
        }
        for (int i = 1;i <= n;++i)
            scanf("%d%d",&Point[i].x,&Point[i].y);

        used_edge_cnt = 0;
        Ecnt=0;
        init_edge(n);
        Kruskal_1(n,Ecnt);
        select_edge();
        Ecnt = used_edge_cnt;
//        deBug( used_edge_cnt == n-1);

        int  ret = INT_MAX;
//        deBug(q);
        for (int i = 0;i < (1<<q) ;++i ){

            int ans = 0;
            _init_set(n);
            int c = 0;
            for ( int j = 0;j < q;++j ){
                if ( (i >> j) & 1 ){
//                    deBug(j);
                    ans += cost[j];
                    for ( int k = 1 ;k < sub_cnt[j];++k ){

                        if ( _find(sub[j][k-1]) == _find(sub[j][k]) ) continue;
                        mkEdge( sub[j][k-1], sub[j][k] ,INT_MAX);
                        _unite( sub[j][k-1], sub[j][k] );
                        c++;
                    }
                }
            }
            if ( c < (n-1) )
                ans += Kruskal_2(n,c);
            ret = min(ret,ans);
        }
        printf("%d\n",ret);
        if(t)puts("");
    }

    return 0;
}
