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

const int SEC_SIZE = 100000+500;
int secL[SEC_SIZE];
int secR[SEC_SIZE];


int Link[SEC_SIZE]; //对于右边集合的 i, link[i]即对应左边集合的 node
int match[SEC_SIZE];

bool vis[SEC_SIZE];
/**< 对于左边的集合的node节点 求增广路径 */
bool DFS( int u){
    /**< 对右边集合的每个结点遍历一次 */
    for( int v = secL[u];v <= secR[u];++v ){
        /**< 如果已经找过 */
        if ( vis[v] )continue; vis[v] = true;
        /**< 如果这个点上未盖点 或者该点还能找到增广路径 */
        if ( Link[v] == -1 || DFS( Link[v] ) ){
            Link[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int hungary(int n ){
    int ret = 0;
    FLAG(Link);
    FLAG(match);
    /**< 对左边集合的每个点求增广路径 */
    for (int u = n;u > 0;--u){
        memset(vis,0,sizeof(vis));
        if (DFS(u)) ret++;
    }
    return ret;
}


int main(){
    int n;
    int t;scanf("%d",&t);while( t-- ){
//    while ( scanf("%d",&n) != EOF){
//        scanf("%d",&n);
        fastIo::scan_d(n);
//        init_Graph();
        for (int i = 1;i <= n;++i )
            fastIo::scan_d(secL[i]),fastIo::scan_d(secR[i]);
        int ans;
        fastIo::println( ans=hungary(n) );
        for (int i = 1;i <= n;++i ){
            if ( match[i] != -1 ){
                ans--;
//                printf("%d",i);
                fastIo::print(i);
                if ( ans )printf(" ");
                else printf("\n");
            }
        }

//        printf("%d\n",);
    }
    return 0;
}
