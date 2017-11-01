#include "../../headers.h"

const int SIZE_V = 100040;
const int SIZE_E = SIZE_V;

struct edge_t{
    int node ,next;
    int w;
    edge_t( int no=0,int ne=0,int ww=0):node(no),next(ne),w(ww){};
}Edge[SIZE_E];

int Ecnt ; // = 1
int Ver[SIZE_V];

const int LAYER = 20;
int up[SIZE_V][LAYER];
int fa[SIZE_V];
int depth[SIZE_V];
int dis[SIZE_V];
bool isVis[SIZE_V];
void init_Edge( ){
    Ecnt = 1;
    CLEAR(dis);
    CLEAR(Ver);
}
void mkEdge( int a,int b ,int w){
    Edge[Ecnt] = edge_t( b,Ver[a],w );
    Ver[a] = Ecnt++;
    Edge[Ecnt] = edge_t( a,Ver[b],w );
    Ver[b] = Ecnt++;
}


void dfs1( int p,int u, int d ,int w){
    fa[u] = p;
    depth[u] = d;
    isVis[u] = 1;
    if ( p != -1 )dis[u] = w + dis[p];
    else dis[u] = 0;
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


void init2( int n ){
    CLEAR(isVis);
    for ( int i = 1;i <= n;++i )if (isVis[i] == 0)
        dfs1(-1,i,1,0);
}


int father[SIZE_V];
int find( int x ){
    return x == father[x] ? x : father[x] = find( father[x] ) ;
}
void unite(int x ,int y ){
    father[ find(x) ] = find(y);
}
void init_set(int n){
    for ( int i = 0;i <= n;++i ) father[i] = i;
}



int main(){
//    readfile("in.txt");
//    int t;scanf("%d",&t);
    int n,m,q;
    int x,y,c;
//    while (t--) {

    while (scanf("%d%d%d",&n,&m,&q)!= EOF){

        init_Edge();
        init_set(n);
        for ( int i = 1;i <= m;++i ){
            scanf("%d%d%d",&x,&y,&c);
            unite(x,y);
            mkEdge(x,y,c);
        }
        init2(n);
//        dfs1(-1,1,1,0);
        init_LCA(n);
        while ( q-- ){
            scanf("%d%d",&x,&y);
            if ( find(x) != find(y) ) {
                printf("Not connected\n");
                continue;
            }
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
