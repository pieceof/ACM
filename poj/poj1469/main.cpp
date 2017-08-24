#include "../../headers.h"

typedef int weight_t;
/** \二分图最大匹配（匈牙利算法的DFS实现）
 * 临界表 无向边(ans/2)
 * CALL:ret=hungary();输出最大匹配数
 * 时间复杂度:O(VE);
 *********
 */
const int SIZE_V = 8000+500;
const int SIZE_E = 80000+500;
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

//    Edge[Ecnt].node = a;
//    Edge[Ecnt].next = Ver[b];
//    Ver[b] = Ecnt++;
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

int main(){
    int n,m;
    int t;scanf("%d",&t);while( t-- ){
        scanf("%d%d",&n,&m);
        int x,y;
        init_Graph();
        for (int i = 1;i <= n;++i ){
            int k;scanf("%d",&k);
            while( k-- ){
                scanf("%d",&x);
                mkEdge(i,x);
//                deBugPair(i,x);
            }
        }
        if ( hungary(n) == n ) printf("YES\n");
        else printf("NO\n");
//        printf("%d\n",hungary(n));
    }
    return 0;
}
