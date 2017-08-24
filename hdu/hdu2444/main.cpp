#include "../../headers.h"

typedef int weight_t;
/** \二分图最大匹配（匈牙利算法的DFS实现）
 * 临界表 无向边(ans/2)
 * CALL:ret=hungary();输出最大匹配数
 * 时间复杂度:O(VE);
 *********
 */
const int SIZE_V = 2000+500;
const int SIZE_E = 30000+500;
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
    /**< 对左边集合的每个点求增广路径 */
    for (int u = 1;u <= n;++u){
        memset(vis,0,sizeof(vis));
        if (DFS(u)) ret++;
    }
    return ret;
}
//int Graph[SIZE][SIZE];
int color[SIZE_V];
bool BFS( int s,int n ){
    queue<int> que;
    que.push(s);
    color[s] = 1;
    while( !que.empty() ){
        int u = que.front(); que.pop();
        for (int next = Ver[u];next;next=Edge[next].next){
            int v = Edge[next].node;
            if( color[v] == -1 ){
                color[v] = !color[u];
                que.push(v);
            }
            if ( color[v] == color[u] )
                return false;
        }
    }
    return true;
}
bool just_Bipartite_Graph( int n ){
    for ( int i = 1;i <= n;++i )
        if ( color[i] == -1 && BFS(i,n) == 0 )
            return false;
    return true;
}
void init(){
    memset(color,-1,sizeof(color));
}
int main(){
    int n,m;
//    int t;scanf("%d",&t);while( t-- ){
    while ( scanf("%d%d",&n,&m) != EOF){
        int x,y;
        init_Graph();
        init();
        while ( m-- ){
            scanf("%d%d",&x,&y);
            mkEdge(x,y);
        }
        if ( just_Bipartite_Graph(n) == 0 ) printf("No\n");
        else
            printf("%d\n",hungary(n)/2);
    }
    return 0;
}
