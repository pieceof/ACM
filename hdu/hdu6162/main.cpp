#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
typedef long long llt;
using namespace std;
/**树链剖分,轻重边剖分HLDD
 * 点权
 * heavy light decomposition
 */
typedef int data_t;
const int SIZE = 190100;

struct edge_t{
    int node;
    int next;
}Edge[SIZE<<1];
int Ecnt ; // = 0
int Ver[SIZE];
void mkEdge( int a,int b ){
    Edge[Ecnt].node = b;
    Edge[Ecnt].next = Ver[a];
    Ver[a] = Ecnt++;

    Edge[Ecnt].node = a;
    Edge[Ecnt].next = Ver[b];
    Ver[b] = Ecnt++;
}

struct node_t{
    int parent;
    int heavy_son;
    int depth;  /**< 根为0 */
    int size;
    int top;    /**< 本点所在重链的最顶端节点 */
    int nid;    /**< 新的编号 ( 在线段树中的编号 ) */
    data_t data;
}Node[SIZE];
int TIdx ; // = 0
int NewIdx[SIZE];


void dfsHeavyEdge( int t,int parent ,int depth ){
    Node[t].depth = depth;
    Node[t].parent = parent;
    Node[t].size = 1;

    for (int next = Ver[t]; next ; next = Edge[next].next ){
        int u = Edge[next].node;
        if ( u == parent ) continue;

        dfsHeavyEdge(u,t,depth+1);
        Node[t].size += Node[u].size;
        // 判断重边
        if ( Node[u].size > Node[Node[t].heavy_son].size)
            Node[t].heavy_son = u;
    }

}

void dfsHeavyPath( int t,int top ){
    Node[t].top = top;
    Node[t].nid = TIdx; /**< TIdx 可dfs访问的时间戳 */
    NewIdx[TIdx++] = t; /**< 时间戳数组,记录这个时间访问的节点号,后面建线段树就是 */
    /**< 根据这个节点号,存储点权,其实也可以在这记录点权 */

    if ( 0 == Node[t].heavy_son ) return;
    dfsHeavyPath(Node[t].heavy_son,top);
    for ( int next = Ver[t] ; next ; next = Edge[next].next){
        int u = Edge[next].node;
        if ( u == Node[t].parent || u == Node[t].heavy_son )
            continue;
        dfsHeavyPath(u,u);
    }
}

struct stNode_t{
    llt sum;
    int ma;
    int mi;
//    int delay;
}ST[ SIZE << 2 ];

inline int lson( int t ) {return t<<1;}
inline int rson( int t ) {return (t<<1)|1;}

void _pushUp( int t ){
    ST[t].ma = max( ST[lson(t)].ma, ST[rson(t)].ma );
    ST[t].mi = min( ST[lson(t)].mi, ST[rson(t)].mi );
    ST[t].sum = ST[lson(t)].sum + ST[rson(t)].sum ;
}

void buildTree( int t,int s,int e ){
//    ST[t].delay = 0;
//    ST2[t].delay = 0;
    if ( s == e ){
        ST[t].mi = Node[NewIdx[s]].data;
        ST[t].ma = Node[NewIdx[s]].data;
        ST[t].sum = Node[NewIdx[s]].data;
        return;
    }
    int mid = (s+e) >> 1;
    buildTree(lson(t),s,mid);
    buildTree(rson(t),mid+1,e);
    _pushUp(t);
}

llt query(int t,int s,int e,int a,int b,int low,int up){

    if ( low > ST[t].ma || up < ST[t].mi ) return 0;

    if ( a <= s && e <= b ){
        if ( ST[t].ma <= up && ST[t].mi >= low ) return ST[t].sum;
//        if ( ST[t].ma <= up && ST[t].mi >= low ) return ST[t].sum;
//        if ( ST[t].ma <= up && ST[t].mi >= low ) return ST[t].sum;
//        if ( ST[t].ma <= up && ST[t].mi >= low ) return ST[t].sum;
        if ( s == e ) return 0;
    }

    int mid = (s+e)>>1;
    llt ret = 0;

    if ( a <= mid )  ret += query(lson(t),s,mid,a,b , low, up );
    if ( mid < b )   ret += query(rson(t),mid+1,e,a,b, low, up );
    return ret;
}



/**< 查询 u->v 边的 最大值 */
llt find( int t,int s,int e ,int u ,int v ,int low,int up){
    llt tmp = 0;
    while ( Node[u].top != Node[v].top ){
        if ( Node[ Node[u].top ].depth < Node[ Node[v].top ].depth )
            swap( v,u );
//        tmp += query(t,s,e,
//            Node[Node[u].top].nid,Node[u].nid);
        tmp += query(t,s,e,
            Node[Node[u].top].nid,Node[u].nid ,low,up) ;
        u = Node[u].top;
        u = Node[u].parent;
    }
    /**< 保证u是下面的节点 */
//    if ( u == v ) return tmp;
    if ( Node[u].depth > Node[v].depth ) swap(u,v);
    /**< 边权的剖分 此处 +1  */
    tmp += query( t,s,e, Node[u].nid,Node[v].nid ,low,up ) ;
    return tmp ;
}

inline void init(int n ){
    Ecnt = TIdx = 1;
    fill(Ver,Ver+n+1,0);
    for(int i=0;i<=n;++i)Node[i].heavy_son = 0;
}

int n,m;
llt ans[SIZE];
int anscnt = 0;
int main(){
    int q;
    while( EOF != scanf("%d%d",&n,&q) ){

        init(n);
        for(int i=1;i<=n;++i)scanf("%d",&Node[i].data);
        for(int i=0;i < n-1;++i){
            int a,b;
            scanf("%d%d",&a,&b);
            mkEdge(a,b);
        }
        //以第1个节点为根建树
        dfsHeavyEdge(1,0,0);
        //从根节点开始递归建重链
        dfsHeavyPath(1,1);
        //以ST[1]为根节点区间[1,N]建线段树
        buildTree(1,1,n);
        int u,v;
        int up,low;
////        int q;scanf("%d",&q);
        anscnt = 0;
        for (int i = 0;i < q;++i ){
            scanf("%d%d%d%d",&u,&v,&low,&up);
//            deBug( u );
//            deBug( v );
            ans[anscnt++] = find(1,1,n,u,v,low,up);
        }
        for (int i = 0 ;i < anscnt-1;++i )
            printf("%lld ",ans[i]);
        printf("%lld\n",ans[anscnt-1]);
    }
    return 0;
}
