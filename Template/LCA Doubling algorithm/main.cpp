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
#define CLEAR(a) memset((a),0,sizeof(a) )
using namespace std;
typedef long long llt;

const int SIZE_V = 200000;
const int SIZE_E = 200000;
struct edge_t{
    int node;
    edge_t* next;
}Edge[SIZE_E];

edge_t* Ver[SIZE_V];
int toUsed ;
void init( ){
    toUsed = 0;
    CLEAR(Ver);
}
void mkEdge( int a,int b,int k = 0){
    Edge[toUsed] = (edge_t){a,Ver[b]};
    Ver[b] = Edge + toUsed++;

    Edge[toUsed] = (edge_t){b,Ver[a]};
    Ver[a] = Edge + toUsed++;
}

int dep[SIZE_V];
const int LOG = int(log2(SIZE_V)) + 2 ;
int fa[SIZE_V][20]; //(log e _SIZE_V)

int n,m;


void dfs( int father,int u,int depth ){
    dep[u] = depth;
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
        dfs(u , v , depth+1);
    }
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
int dis(int x,int y ){
    return dep[x]+dep[y]-2*dep[LCA(x,y)];
}

int main()
{
    init();
    return 0;
}
