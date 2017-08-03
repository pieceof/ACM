/**
 * LCA 倍增算法
 * 下标从 1 开始
 * 初始化 & depth = 1;
 * \return
 *
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#define  clear(a) memset((a),0,sizeof(a) )

#define  debug(x) cout << "=-=-> " << #x << " : " << (x) << endl
using namespace std;
typedef long long llt;

const int SIZE_V = 400000;
const int SIZE_E = 400000;
struct edge_t{
    int node;
    edge_t* next;
    int k;
    edge_t(int nn=0,edge_t* ne=0,int kk=0):node(nn),k(kk),next(ne) {}
}Edge[SIZE_E];

edge_t* Ver[SIZE_V];
int toUsed ;
void init( ){
    toUsed = 0;
    clear(Ver);
}
void mkEdge( int a,int b,int k = 0){
    Edge[toUsed] = edge_t(a,Ver[b],k);
    Ver[b] = Edge + toUsed++;

    Edge[toUsed] = edge_t(b,Ver[a],k);
    Ver[a] = Edge + toUsed++;
}

int dep[SIZE_V];
const int LOG = int(log2(SIZE_V)) + 2 ;
int fa[SIZE_V][20]; //(log e _SIZE_V)

int n,m;
llt len[SIZE_V];

void dfs( int father,int u,int depth ,llt length){
    dep[u] = depth;
    len[u] = length;
    if ( 1 == u )
        for ( int i = 0 ; i < LOG;++i )
            fa[u][i] = u ;
    else{
        fa[u][0] = father;
        for ( int i = 1 ; i < LOG;++i )
            fa[u][i] = fa[fa[u][i-1]][i-1];
    }
    for ( edge_t*p = Ver[u]; p ; p = p->next ){
        int v = p->node;
        if ( v == father )continue;
        dfs(u , v , depth+1 ,length + p->k);
    }
}
llt maxlen;
int maxnode;
void dfs2( int father,int u ,llt l){
    if ( maxlen < l ) maxlen = l , maxnode = u;
    for (edge_t*p = Ver[u] ; p ; p = p->next) {
        int v = p->node;
        if ( father == v ) continue;
        dfs2( u,v , l + p->k );
    }
}
void init2(){
    maxlen = 0, maxnode = -1;
}

int up(int u,int d){
    for (int i = 0;i < LOG;++i )
        if ( d&(1<<i) ) u = fa[u][i];
    return u;
}

int LCA( int u,int v ){
    if ( dep[u] < dep[v] ) swap( u , v );
    u = up(u,dep[u]-dep[v] );
    if ( u == v ) return u;
    for (int i = LOG-1;i >= 0;--i ){
        if ( fa[u][i] == fa[v][i] )continue;
        u = fa[u][i];
        v = fa[v][i];
    }
    return fa[u][0];
}
llt dis(int x,int y ){
    return (llt)len[x]+len[y]-2*len[LCA(x,y)];
}

void solve( int n ){
    //init();
    dfs(-1,1,1,0);

    init2();
    dfs2(-1,1,0);
    int node1 = maxnode ;
    init2();
    dfs2(-1,node1,0);
    int node2 = maxnode ;
//    debug(node1);
//    debug(node2);
//
    debug( LCA(2,4) );
//    debug(dep[2]);
//    debug(dep[4]);
//    debug(dep[1]);

    llt ans = 0;
    for (int i = 1 ;i <= n; ++i ){
        llt d1 = dis(i,node1);
        llt d2 = dis(i,node2);
//        cout << "  " << endl;
//        debug(i);
//        debug(d1);
//        debug(d2);
        ans += max(d1,d2);
    }
    ans -= dis(node1,node2);
//    debug(dis(node1,node2));
    printf("%I64d\n",ans);
}
int main(){

    int n;
    while ( scanf("%d",&n) != EOF ){
        int x,y,k;
        init();
        for (int i = 1 ;i < n;++i){
            scanf("%d%d%d",&x,&y,&k);
            mkEdge(x,y,k);
        }
        solve(n);
    }

}
