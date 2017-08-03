//#include <bits/stdc++.h>
#include <cstdio>
#include <climits>
#include <iostream>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
#define TEST(x) while(!(x))
typedef long long llt;
using namespace std;
/**树链剖分,轻重边剖分HLDD
 * 边权
 * heavy light decomposition
 */

/// ------------------------------------- 临接表  ------------------------- //
typedef int data_t;
const int SIZE = 150100;

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
    llt peak;
//    int delay;
}ST[ SIZE << 2 ];

inline int lson( int t ) {return t<<1;}
inline int rson( int t ) {return (t<<1)|1;}

void _pushUp( int t ){
    ST[t].peak = ST[lson(t)].peak +  ST[rson(t)].peak;
//    ST[t].peak = max( ST[lson(t)].peak , ST[rson(t)].peak );
}
//void _pushDown( int t ){
//    if ( 0 == ST[t].delay ) return;
//    int &k = ST[t].delay;
//    ST[lson(t)].delay += k;
//    ST[lson(t)].peak += k;
//    ST[rson(t)].delay += k;
//    ST[rson(t)].peak += k;
//    ST[t].delay = 0;
//}

void buildTree( int t,int s,int e ){
//    ST[t].delay = 0;
    if ( s == e ){
        ST[t].peak = 0;
        return;
    }
    int mid = (s+e) >> 1;
    buildTree(lson(t),s,mid);
    buildTree(rson(t),mid+1,e);
    _pushUp(t);
}
/**< 区间更新 */
void modify( int t,int s,int e, int a,int b,int delta ){
    if ( a <= s && e <= b ){
//        ST[t].delay += delta;
//        ST[t].peak += delta;
        ST[t].peak = delta;
        return;
    }
//    _pushDown(t);
    int mid = (s+e) >> 1;
    if ( a <= mid ) modify( lson(t),s,mid,a,b,delta);
    if ( mid < b )  modify( rson(t) ,mid+1,e,a,b,delta);
    _pushUp(t);
}

int query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){ return ST[t].peak; }
//    _pushDown(t);
    int mid = (s+e)>>1;
    int ret = 0;
    if ( a <= mid )  ret += query(lson(t),s,mid,a,b);
    if ( mid < b )   ret += query(rson(t),mid+1,e,a,b);
    return ret;
}
/**< 查询 u->v 边的最大值 */
llt find( int t,int s,int e ,int u ,int v ){
    int tmp = 0;
    while ( Node[u].top != Node[v].top ){
        if ( Node[ Node[u].top ].depth < Node[ Node[v].top ].depth )
            swap( v,u );
        tmp += query(t,s,e,
            Node[Node[u].top].nid,Node[u].nid);
//        tmp = max( tmp , query(t,s,e,
//            Node[Node[u].top].nid,Node[u].nid) );
        u = Node[u].top;
        u = Node[u].parent;
    }
    /**< 保证u是下面的节点 */
    if ( u == v ) return tmp;
    if ( Node[u].depth > Node[v].depth ) swap(u,v);
    /**< 边权的剖分 此处 +1  */
//    tmp = max( tmp, query( t,s,e, Node[u].nid+1,Node[v].nid) );
    return tmp + query( t,s,e, Node[u].nid+1,Node[v].nid);
}

inline void init( int n ){
    Ecnt = TIdx = 1;
    fill(Ver,Ver+n+1,0);
    for(int i = 0;i <= n;++i)Node[i].heavy_son = 0;
}

int t,n,m;
int e[SIZE][3];
int q,s;
int main(){
//    writefile("out.txt");
//    scanf("%d",&t);while ( t-- ){
    while ( scanf("%d%d%d",&n,&q,&s) != EOF ) {
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
            modify(1,1,n,Node[e[i][1]].nid,Node[e[i][1]].nid,e[i][2]);
        }
        char op[20];
        int u,v;
        while ( q-- ){
            scanf("%s",op);
            if ( *op == '1' ){
                scanf("%d%d",&u,&v);
                modify(1,1,n,Node[e[u-1][1]].nid,Node[e[u-1][1]].nid,v);
            }else {
                int to;scanf("%d",&to);
                printf("%lld\n",find(1,1,n,s,to));
                s = to;
            }
        }
    }

    return 0;
}

