#include "../../headers.h"


const int SIZE = 1000100;

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
//    int sum;  /**< 区间和 */
    int lazy;
    llt color; /*!< 二进制记录颜色 */
}ST[SIZE<<3];

inline int lson( int t ) {return t<<1;}
inline int rson( int t ) {return (t<<1)|1;}

#define ls lson(t)
#define rs rson(t)

inline void _pushUp( int t ){
    ST[t].color = ST[ls].color | ST[rs].color;
}
inline void _pushDown( int t ){
    if (ST[t].lazy == 0 )return ;

    ST[ls].lazy = ST[rs].lazy = ST[t].lazy;
    ST[ls].color = ST[rs].color = 1LL << ST[t].lazy;
    ST[t].lazy = 0;
}


void build( int t,int s,int e ){
    ST[t].lazy = 0;
    if ( s == e ){
        ST[t].color = 1LL << Weight[ NewIdx[s]] ;
        return;
    }
    int m = (s+e)>>1;
    build( lson(t) , s, m);
    build( rson(t) , m+1,e);
    _pushUp(t);

}

void modify( int t,int s,int e,int a,int b,int color){
    if (a <= s && e <= b ){
        ST[t].color = (1LL<<color);
        ST[t].lazy = color;
        return ;
    }
    _pushDown(t);
    int m = (s + e)>>1;
    if ( a <= m ) modify(lson(t),s,m,a,b,color);
    if ( m < b ) modify( rson(t),m+1,e,a,b,color);
    _pushUp(t);
}

llt query( int t,int s,int e,int a,int b ){
    if ( a <= s && e <= b ){
        return ST[t].color;
    }
    _pushDown(t);
    llt ret = 0;
    int m = (s + e)>>1;
    if (a <= m) ret |= query(lson(t),s,m,a,b);
    if (m < b)  ret |= query(rson(t),m+1,e,a,b);
    return ret;
}


inline void initTree(int n){
    Ecnt = Ncnt = 1;
    CLEAR(Ver);
}

int CountColor(llt x){
    int ret = 0;
    while (x){
        ret += (x&1);
        x >>= 1LL;
    }
    return ret;
}

int main(){

    int n,m;
    int root=1;
    while ( scanf("%d%d",&n,&m) != EOF ){
        initTree(n);
        for (int i = 1;i <= n;++i )
            scanf("%d",Weight+i);
        int a,b;
        for ( int i = 1;i < n ;++i ){
            scanf("%d%d",&a,&b);
            mkEdge(a,b);
        }
        dfs(root,0);
        build(1,1,n<<1);

//        scanf("%d",&m);
        int cmd;
        int v,k;
        while ( m-- ){
            scanf("%d%d",&cmd,&v);
            if ( cmd == 1 ){
                scanf("%d",&k);
                modify(1,1,n<<1,InIdx[v],OutIdx[v],k);
            }else if (cmd == 2){
                llt ans = query(1,1,n<<1,InIdx[v],OutIdx[v]);
//                deBug( ans ) ;
                printf("%d\n",CountColor(ans));
            }
        }
//        printf("\n");


    }


    return 0;
}
