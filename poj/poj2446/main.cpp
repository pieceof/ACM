#include "../../headers.h"

typedef int weight_t;
/** \二分图最大匹配（匈牙利算法的DFS实现）
 * 临界表 无向边(ans/2)
 * CALL:ret=hungary();输出最大匹配数
 * 时间复杂度:O(VE);
 *********
 */
const int SIZE_V = 2000+500;
const int SIZE_E = 10000+500;
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


int n,m,k;
const int SIZE = 40;
bool mat[SIZE][SIZE];
inline bool isIn(int r,int c){
    return r >= 0 && r < n && c >= 0 && c < m;
}
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};

inline int encode( int r,int c ){
    return r*m+c+1;
}

int main(){
    while ( scanf("%d%d%d",&n,&m,&k) != EOF ){
        CLEAR(mat);
        int x,y;
        for (int i = 0;i < k;++i ){
            scanf("%d%d",&x,&y);
            mat[y-1][x-1] = 1;
        }
        for (int i = 0;i < n;++i ){
            for (int j = 0;j < m;++j ){
                if ( mat[i][j] == 0 && isIn(i,j) ){
                    int tx,ty;
                    for (int f = 0;f < 4;++f ){
                        tx = dx[f] + i;
                        ty = dy[f] + j;
                        if ( mat[tx][ty] == 0 && isIn(tx,ty) )
//                            deBugPair( encode(i,j) , encode(tx,ty) );
                            mkEdge( encode(i,j) , encode(tx,ty) );
                    }
                }
            }
        }

        int ans = hungary( n*m );
//        deBug( ans );
//        deBug(ans*2 == n-k );
        if ( ans == n*m-k )printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
