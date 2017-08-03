#include <iostream>
#include <cstdio>
#include <climits>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
#define TEST(x) while(!(x))
using namespace std;
/**树链剖分,轻重边剖分HLDD
 * 边权
 * heavy light decomposition
 */

/// ------------------------------------- 临接表  ------------------------- //
typedef int data_t;
const int SIZE = 500100;

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

///---------------------------------------  树链剖分 ------------------------//

struct node_t{
    int parent;
    int heavy_son;
    int depth;  /**< 根为0 */
    int size;
    int top;    /**< 本点所在重链的最顶端节点 */
    int nid;    /**< 新的编号 */
//    data_t data;
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
    Node[t].nid = TIdx;
    NewIdx[TIdx++] = t;
    if ( 0 == Node[t].heavy_son ) return;
    dfsHeavyPath(Node[t].heavy_son,top);
    for ( int next = Ver[t] ; next ; next = Edge[next].next){
        int u = Edge[next].node;
        if ( u == Node[t].parent || u == Node[t].heavy_son ) continue;
        dfsHeavyPath(u,u);
    }
}

///  -0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0- -- 线段树 -- -0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0 ///
/**
 * 边权的跟点权的不一样,边的表示为点上面的那条边
 * 1 ~ n
 */
struct stNode_t{
    int Min;
    int Max;
    int delay;
}ST[SIZE<<2];

inline int lson( int t ) {return t<<1;}
inline int rson( int t ) {return (t<<1)|1;}

void _pushUp( int t ){
//    ST[t].peak = ST[lson(t)].peak +  ST[rson(t)].peak;
    ST[t].Min = min( ST[lson(t)].Min ,ST[rson(t)].Min );
    ST[t].Max = max( ST[lson(t)].Max ,ST[rson(t)].Max );
}

void _swapMin2Max( int t ){
    swap(ST[t].Min,ST[t].Max);
    ST[t].Min *= -1;
    ST[t].Max *= -1;
}

void _pushDown( int t ){
    if ( 0 == ST[t].delay ) return;
//    int &k = ST[t].delay;
    ST[t].delay ^= 1;
    ST[lson(t)].delay ^= 1;
    ST[rson(t)].delay ^= 1;

//    ST[lson(t)].Min += k;
//    ST[rson(t)].Max += k;
    _swapMin2Max(lson(t));
    _swapMin2Max(rson(t));
}

void buildTree( int t,int s,int e ){
    ST[t].delay = 0;
    if ( s == e ){
        ST[t].Max = ST[t].Min = 0;
        return;
    }
    int mid = (s+e) >> 1;
    buildTree(lson(t),s,mid);
    buildTree(rson(t),mid+1,e);
    _pushUp(t);
}
/**< 单点更新 */
void modify( int t,int s,int e, int k,int var ){
    if ( s == e ){
        ST[t].Max = ST[t].Min = var;
        return;
    }
    _pushDown(t);
    int mid = (s+e) >> 1;
    if ( k <= mid ) modify( lson(t),s,mid,k,var);
    else modify( rson(t) ,mid+1,e,k,var);
    _pushUp(t);
}


/**< 区间更新 */
/*
void modify( int t,int s,int e, int a,int b,int delta ){
    if ( a <= s && e <= b ){
        ST[t].delay += delta;
        ST[t].peak += delta;
//        ST[t].peak = delta;
        return;
    }
    _pushDown(t);
    int mid = (s+e) >> 1;
    if ( a <= mid ) modify( lson(t),s,mid,a,b,delta);
    if ( mid < b )  modify( rson(t) ,mid+1,e,a,b,delta);
    _pushUp(t);
}*/
void _Negate(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){
        ST[t].delay ^= 1;
        _swapMin2Max(t);
        return;
    }
    _pushDown(t);
    int mid = (s+e) >> 1;
    if ( a <= mid ) _Negate( lson(t),s,mid,a,b);
    if ( mid < b )  _Negate( rson(t) ,mid+1,e,a,b);
    _pushUp(t);
}
void Negate(int t,int s,int e,int x,int y){
    while ( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth )
            swap(x,y);
        _Negate(t,s,e,Node[Node[x].top].nid,Node[x].nid);

        x = Node[x].top;
        x = Node[x].parent;
    }
    if( x == y )return;
    if ( Node[x].depth > Node[y].depth ) swap(x,y);

    _Negate(t,s,e,Node[x].nid+1,Node[y].nid);
}
int query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){ return ST[t].Max; }
    _pushDown(t);
    int mid = (s+e)>>1;
    int ret = INT_MIN;
    if ( a <= mid )  ret = max(ret, query(lson(t),s,mid,a,b));
    if ( mid < b )   ret = max(ret, query(rson(t),mid+1,e,a,b));
    return ret;
}
/**< 查询 u->v 边的最大值 */
int find( int t,int s,int e ,int u ,int v ){
    int tmp = INT_MIN;
    while ( Node[u].top != Node[v].top ){
        if ( Node[ Node[u].top ].depth < Node[ Node[v].top ].depth )
            swap( v,u );
        tmp = max( tmp , query(t,s,e,
            Node[Node[u].top].nid,Node[u].nid) );
        u = Node[u].top;
        u = Node[u].parent;
    }
    /**< 保证u是下面的节点 */
    if ( u == v ) return tmp;
    if ( Node[u].depth > Node[v].depth ) swap(u,v);
    /**< 边权的剖分 此处 +1  */
    tmp = max( tmp, query( t,s,e, Node[u].nid+1,Node[v].nid) );
    return tmp;
}

/**< x - y 路径上的点  val */
/*
void change( int t,int s,int e,int x,int y ,int delta){
    while ( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth )
            swap(x,y);
        modify(t,s,e,Node[Node[x].top].nid,Node[x].nid,delta);

        x = Node[x].top;
        x = Node[x].parent;
    }
    if( x == y )return;
    if ( Node[x].depth > Node[y].depth ) swap(x,y);

    modify(t,s,e,Node[x].nid+1,Node[y].nid,delta);
}*/

inline void init( int n ){
    Ecnt = TIdx = 1;
    fill(Ver,Ver+n+1,0);
    for(int i = 0;i <= n;++i)Node[i].heavy_son = 0;
}

int t,n;
int e[SIZE][3];
int main(){
//    writefile("out.txt");
    scanf("%d",&t);while ( t-- ){
        scanf("%d",&n);
        init(n);
        for(int i = 0;i < n-1;++i ){
            scanf("%d%d%d",&e[i][0],&e[i][1],&e[i][2]);
            mkEdge( e[i][0],e[i][1] );
        }
        //以第1个节点为根建树
        dfsHeavyEdge(1,0,0);
        //从根节点开始递归建重链
        dfsHeavyPath(1,1);
        //以ST[1]为根节点区间[1,N]建线段树
        buildTree(1,1,n);

        for (int i = 0;i < n-1;++i ){
            if ( Node[e[i][0]].depth > Node[e[i][1]].depth )
                swap(e[i][0],e[i][1]);
            modify(1,1,n,Node[e[i][1]].nid,e[i][2]);
        }
        char op[20];
        int u,v;
        while ( scanf("%s",op) != EOF ){
            if ( *op == 'D' ) break;
            scanf("%d%d",&u,&v);
            if ( *op == 'Q' )
                printf("%d\n",find(1,1,n,u,v));
            else if ( *op == 'C')
                modify(1,1,n,Node[e[u-1][1]].nid,v);
            else
                Negate(1,1,n,u,v);
        }
    }

    return 0;
}
