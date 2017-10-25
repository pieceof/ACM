#include "../../headers.h"


const int SIZE_V = 100100;
const int SIZE_E = SIZE_V;

struct edge_t{
    int node , next;
    int w;
    edge_t( int no=0,int ne=0,int ww=0):node(no),next(ne),w(ww){};
}Edge[SIZE_E];

int Ecnt ; // = 1
int Ver[SIZE_V];

const int LAYER = 15;
int up[SIZE_V][LAYER];
int fa[SIZE_V];
int depth[SIZE_V];
int dis[SIZE_V];

void mkEdge( int a,int b ,int w){
    Edge[Ecnt] = edge_t( b,Ver[a],w );
    Ver[a] = Ecnt++;

    Edge[Ecnt] = edge_t( a,Ver[b],w );
    Ver[b] = Ecnt++;
}


void dfs1( int p,int u, int d ,int w){
    fa[u] = p;
    depth[u] = d;
    if( u != 1 ) dis[u] = w + dis[p];
    for (int next = Ver[u];next;next=Edge[next].next){
        int v = Edge[next].node;
        int w = Edge[next].w;
        if ( p != v ) dfs1( u, v, d+1 ,w);
    }
}

void init_LCA( int n ){
    for (int i = 1;i <= n;++i )
        up[i][0] = fa[i];
    for (int j = 1;j < LAYER;++j)
        for (int i = 1;i <= n;++i )
            up[i][j] = up[ up[i][j-1] ][j-1];
}

int get_LCA(int a,int b){
    if ( depth[a] < depth[b] ) swap(a,b);
    int x = depth[a]-depth[b];
    for ( int i = 0;i < LAYER;++i )
        if ( x & (1<<i) )
            a = up[a][i];
    if ( a == b ) return b;

    for ( int i = LAYER-1;i >= 0;--i )
        if ( up[a][i] != up[b][i] )
            a = up[a][i] , b = up[b][i];
    return up[a][0];
}

void init( ){
    Ecnt = 1;
    dis[1] = 0;
    CLEAR(Ver);
}

int main(){
//    readfile("in.txt");
    int t;scanf("%d",&t);
    int n,m;
    while ( t-- ){
        scanf("%d%d",&n,&m);
        init();
        int x,y,c;
        for ( int i = 1;i < n;++i ){
            scanf("%d%d%d",&x,&y,&c);
            mkEdge(x,y,c);
        }
        dfs1(-1,1,1,0);
        init_LCA(n);
        while ( m-- ){
            scanf("%d%d",&x,&y);
            int p = get_LCA( x, y);
//            deBug(p);
            int ans = dis[x] + dis[y] - 2*dis[p];
//            deBug( ans);
            Ans(ans);
        }
//        printf("\n");
    }
    return 0;
}
