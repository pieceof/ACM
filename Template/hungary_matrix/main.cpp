#include "../../headers.h"

typedef int weight_t;
/**
 *二分图匹配（匈牙利算法的DFS实现）
 *Graph[][]两边定点划分的情况
 *CALL:ret=hungary();输出最大匹配数
 *优点：适于稠密图，DFS找增广路快，实现简洁易于理解
 *时间复杂度:O(VE);
 *gn gm 为两个集合的大小，从0 ～ n-1 编号
 *********
  初始化Graph 为0；
 *********
 */
const int SIZE = 510;
// 存储二分图 左边的集合跟右边集合边的信息
// 如果有边为 1 , 没边为 0
weight_t Graph[SIZE][SIZE];

int Link[SIZE]; //对于右边集合的 i, link[i]即对应左边集合的 node
bool vis[SIZE];
int gn,gm;

//对于左边的集合的node节点 求增广路径
bool DFS( int node){
    //对右边集合的每个结点便利一次
    for (int i = 0;i < gm;++i){

        //如果已经找过 或者没有这个边
        if ( vis[i] || Graph[node][i] == 1)continue;

        vis[i] = true;
        //如果这个点上未盖点 或者该点还能找到增广路径
        if ( Link[i] == -1 || DFS( Link[i] ) ){
            Link[i] = node;
            return true;
        }

    }
    return false;
}
int hungary(){
    int ret = 0;

    memset(Link , -1 ,sizeof(Link));
    //对左边集合的每个点求增广路径
    for (int u = 0;u < gn;++u){
        memset(vis,0,sizeof(vis));
        if (DFS(u)) ret++;
    }
    return ret;
}

int n,m,k;
int kase = 1;
int main(){
    while ( scanf("%d%d%d",&gn,&gm,&k) != EOF ){
        if ( (gn||gm||k) == 0 )break;
        int x,y;
        CLEAR(Graph);
        while ( k-- ){
            scanf("%d%d",&x,&y);
            Graph[x-1][y-1] = 1;
        }
        int ans = hungary();
//        deBug( gn+gm-ans );
        printf("Case %d: ",kase++);
        Ans(gn+gm-ans);
    }
    return 0;
}
