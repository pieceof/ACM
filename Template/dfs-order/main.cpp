#include "../../headers.h"

const int SIZE = 1001000;

struct edge_t{
    int to;
    int next;
}Edge[SIZE<<1];

int Ver[SIZE];
int Ecnt;
llt W[SIZE];

inline void mkEdge(int a,int b){
    Edge[Ecnt].to = b;
    Edge[Ecnt].next = Ver[a];
    Ver[a] = Ecnt++;

    Edge[Ecnt].to = a;
    Edge[Ecnt].next = Ver[b];
    Ver[b] = Ecnt++;
}
int InIdx[SIZE],OutIdx[SIZE]; /**< 第一/二次访问该节点的时间戳 */
int InOut[SIZE<<1];     /**< 该次访问的节点是第几次访问 */
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
    int flag; /*!< 区间内正数个数-负数个数 */
    llt sum;  /**< 区间和 */
    llt delay;
}ST[SIZE<<3];

#define lson(x) ((x)<<1)
#define rson(x) (lson(x)|1)
#define ls lson(t)
#define rs rson(t)

inline void _pushUp( int t ){
    ST[t].sum = ST[ls].sum + ST[rs].sum;
    ST[t].flag = ST[ls].flag + ST[rs].flag;
}

inline void _pushDown( int t ){
    if ( 0 == ST[t].delay ) return;
    llt &x = ST[t].delay;

    ST[ls].sum += ST[ls].flag * x;
    ST[ls].delay += x;

    ST[rs].sum += ST[rs].flag * x;
    ST[rs].delay += x;

    x = 0;
}

void build( int t,int s,int e ){
    ST[t].delay = 0;
    if ( s == e ){
        ST[t].sum = InOut[s] * W[ NewIdx[s] ];
        ST[t].flag = InOut[s];
        return;
    }
    int m = (s+e)>>1;
    build( ls , s, m);
    build( rs , m+1,e);
    _pushUp(t);

}

void modify( int t,int s,int e,int a,int b,llt delta){
    if (a <= s && e <= b ){
        ST[t].sum += ST[t].flag * delta;
        ST[t].delay += delta;
        return;
    }
    _pushDown(t);

    int m = (s + e)>>1;
    if ( a <= m ) modify(ls,s,m,a,b,delta);
    if ( m < b ) modify( rs,m+1,e,a,b,delta);
    _pushUp(t);
}

llt query( int t,int s,int e,int a,int b ){
    if ( a <= s && e <= b ){
        return ST[t].sum;
    }
    _pushDown(t);
    llt ret = 0;
    int m = (s + e)>>1;
    if (a <= m) ret += query(ls,s,m,a,b);
    if (m < b)  ret += query(rs,m+1,e,a,b);
    return ret;
}

inline llt query(int n,int x){
    return query(1,1,n<<1,1,InIdx[x]);
}
inline void modify(int n,int x,llt delta){
    modify(1,1,n<<1,InIdx[x],InIdx[x],delta);
    modify(1,1,n<<1,OutIdx[x],OutIdx[x],delta);
}

inline void modifySubtree(int n,int x,llt delta){
    modify(1,1,n<<1,InIdx[x],OutIdx[x],delta);
}

inline void initTree(int n){
    Ecnt = Ncnt = 1;
    CLEAR(Ver);
}

int main(){

    int n,m;
    while ( scanf("%d%d",&n,&m) != EOF ){
        initTree(n);
        for (int i = 1;i <= n;++i ) scanf("%lld",W+i);

        int a,b;
        for ( int i = 1;i < n ;++i ){
            scanf("%d%d",&a,&b);
            mkEdge(a,b);
        }
        dfs(1,0);
        build(1,1,n<<1);

        int cmd , x;
        llt c;

        while (m--){
            scanf("%d%d",&cmd,&x);
            switch(cmd){
                case 1: scanf("%lld",&c);modify(n,x,c);break;
                case 2: scanf("%lld",&c);modifySubtree(n,x,c);break;
                case 3: printf("%lld\n",query(n,x));break;
            }
        }


    }


    return 0;
}
