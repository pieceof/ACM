#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#define clear(a) memset((a),0,sizeof(a) )
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
    clear(Ver);
}
void mkEdge( int a,int b,int k = 0){
    Edge[toUsed] = (edge_t){a,Ver[b]};
    Ver[b] = Edge + toUsed++;

    Edge[toUsed] = (edge_t){b,Ver[a]};
    Ver[a] = Edge + toUsed++;
}
llt toall[SIZE_V];
llt tosub[SIZE_V];
int sz[SIZE_V];
int dep[SIZE_V];
const int LOG = int(log2(SIZE_V)) + 2 ;
int fa[SIZE_V][20]; //(log2_SIZE_V)

int n,m;


void dfs2sub( int father,int u,int depth ){
    sz[u] = 1;
    dep[u] = depth;
    tosub[u] = 0;
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
        dfs2sub(u , v , depth+1);
        sz[u] += sz[v];
        tosub[u] += sz[v] + tosub[v];
    }
    toall[u] = tosub[u];
}
void dfs2all(int father,int u){
    for (edge_t*p = Ver[u]; p ; p = p->next ){
        int v = p->node;
        if ( v == father ) continue;
        toall[v] += ( toall[u] - tosub[v] - sz[v]  ) + ( n-sz[v] );
        dfs2all(u,v);
    }
}
int up(int u,int d){
    for (int i = 0;i < LOG;++i ){
        if ( d&(1<<i) ){
            u = fa[u][i];
        }
    }
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

    while( scanf("%d%d",&n,&m ) != EOF ){
        init();
        int x,y;
        for (int i = 0 ;i < n-1 ; ++i ){
            scanf("%d%d",&x,&y);
            mkEdge(x,y);
        }
        clear(toall);
        clear(tosub);
        dfs2sub(-1,1,1);
        dfs2all(-1,1);

        for (int i = 0 ; i < m ; ++ i ){
            scanf("%d%d",&x,&y);
            if ( dep[x] < dep[y] ) swap(x,y);
            llt cntdis = 0;
            llt cntWay = 0;
            if ( LCA(x,y) != y ){
                cntWay = (llt)sz[x] * sz[y];
                cntdis = sz[x] * tosub[y] + sz[y] * tosub[x] + cntWay*dis(x,y) + cntWay;

            }else {
                int k = up( x , dep[x]-dep[y] - 1 );
                cntWay = (llt)sz[x] * ( n - sz[k] );
                cntdis = tosub[x] * (n-sz[k]) + (toall[y]-tosub[k]-sz[k])*sz[x] + cntWay*dis(x,y) + cntWay;
            }
//            cout << "cntway : " << cntWay << " cntall :" << cntdis << endl;
            printf("%f\n", (cntdis*1.0 / cntWay) );
        }
    }

    return 0;
}
