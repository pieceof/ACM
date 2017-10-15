#include "../../headers.h"

const int SIZE = 200000;

struct edge_t{
    int to;
    int next;
}Edge[SIZE<<1];

int Ver[SIZE];
int Ecnt;
int Weight[SIZE];

inline void mkEdge(int a,int b){
    Edge[Ecnt].to = b;
    Edge[Ecnt].next = Ver[a];
    Ver[a] = Ecnt++;

    Edge[Ecnt].to = a;
    Edge[Ecnt].next = Ver[b];
    Ver[b] = Ecnt++;
}
int InIdx[SIZE],OutIdx[SIZE]; /**< 第一/二次访问该节点的时间戳 */
int InOut[SIZE<<1];     /**< 该次访问的节点是进入还是离开 */
int NewIdx[SIZE<<1];    /**< 访问序列 */
int Ncnt;               /**< 时间戳 */

void dfs(int node,int parent){
    NewIdx[Ncnt] = node;
    InOut[Ncnt] = 1;
    InIdx[node] = Ncnt++;
    for (int next = Ver[node];next;next = Edge[next].next){
        int son = Edge[next].to;
        if (son != parent ) dfs(son,node);
    }
    NewIdx[Ncnt] = node;
    InOut[Ncnt] = -1;
    OutIdx[node] = Ncnt++;
}

struct stNode_t{
//    int sum;  /*!< 区间和 */
    int lazy; /*!< lazy -1 为清除 1为标记 */
    int sum; /*!< 区间内标记的个数 */
//    int dela
}ST[SIZE<<3];

#define lson(x) ((x)<<1)
#define rson(x) (lson(x)|1)
#define ls lson(t)
#define rs rson(t)

inline void _pushUp( int t ,int s,int e){
    if(ST[t].lazy)
        ST[t].sum = e-s+1;
    else
        ST[t].sum = ST[ls].sum + ST[rs].sum;
}

void build( int t,int s,int e ){
    ST[t].lazy = 0;
    ST[t].sum = 0;
    if ( s == e ){
        ST[t].sum = 0;
        return;
    }
    int m = (s+e)>>1;
    build( lson(t) , s, m);
    build( rson(t) , m+1,e);
    _pushUp(t,s,e);

}

void modify( int t,int s,int e,int a,int b,int flag){
    if (a <= s && e <= b ){
        ST[t].lazy += flag ;
        _pushUp(t,s,e);
        return ;
    }
//    _pushDown(t,s,e);
    int m = (s + e)>>1;
    if ( a <= m ) modify(ls,s,m,a,b,flag);
    if ( m < b ) modify( rs,m+1,e,a,b,flag);
    _pushUp(t,s,e);
}


vector <int> que[SIZE];

inline void initTree(int n){
    Ecnt = Ncnt = 1;
    CLEAR(Ver);
    for (int i = 0;i <= n;++i){
        que[i].clear();
    }
    CLEAR(ST);
}

int n,m;
int ans[SIZE];
void dfs2(int fa,int u ){
    for (int i = 0;i < que[u].size();++i ){
        int v = que[u][i];
        modify(1,1,n<<1, InIdx[v],OutIdx[v],1);
    }
//    _pushUp(1);
    ans[u] = ST[1].sum/2;
    if (ans[u]) ans[u]--;
    for ( int next = Ver[u];next;next = Edge[next].next){
        int v = Edge[next].to;
        if ( fa == v ) continue;
        dfs2(u,v);
    }
    for (int i = 0;i < que[u].size();++i ){
        int v = que[u][i];
        modify(1,1,n<<1, InIdx[v],OutIdx[v],-1);
    }
}

int main(){
    int root=1;
    while ( scanf("%d%d",&n,&m) != EOF ){
        initTree(n);
        int a,b;
        for ( int i = 1;i < n ;++i ){
            scanf("%d%d",&a,&b);
            mkEdge(a,b);
        }
        dfs(root,0);
        build(1,1,n<<1);

//        scanf("%d",&m);
        int x,y;
        while ( m-- ){
            scanf("%d%d",&x,&y);
            que[x].push_back(x);
            que[x].push_back(y);
            que[y].push_back(x);
            que[y].push_back(y);
        }
        CLEAR(ans);
        dfs2(-1,1);

//        printf("\n");
        for (int i = 1;i < n;++i ){
            printf("%d ",ans[i]);
        }
        printf("%d\n",ans[n]);

    }


    return 0;
}
