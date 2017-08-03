#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )

using namespace std;
/**树链剖分,轻重边剖分HLDD
 * 点权
 * heavy light decomposition
 */
typedef int data_t;
const int SIZE = 50100;

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
    int peak;
    int delay;
}ST[ SIZE << 2 ];

inline int Lson( int t ) {return t<<1;}
inline int Rson( int t ) {return (t<<1)|1;}

void _pushUp( int t ){
    ST[t].peak = ST[Lson(t)].peak +  ST[Rson(t)].peak;
}
void _pushDown( int t ){
    if ( 0 == ST[t].delay ) return;
    int &k = ST[t].delay;
    ST[Lson(t)].delay += k;
    ST[Lson(t)].peak += k;
    ST[Rson(t)].delay += k;
    ST[Rson(t)].peak += k;
    ST[t].delay = 0;
}

void buildTree( int t,int s,int e ){
    ST[t].delay = 0;
    if ( s == e ){
        ST[t].peak = Node[NewIdx[s]].data;
        return;
    }
    int mid = (s+e) >> 1;

    buildTree(Lson(t),s,mid);
    buildTree(Rson(t),mid+1,e);
    _pushUp(t);
}

void modify( int t,int s,int e, int a,int b,int delta ){
    if ( a <= s && e <= b ){
        ST[t].delay += delta;
        ST[t].peak += delta;
        return;
    }
    _pushDown(t);
    int mid = (s+e) >> 1;
    if ( a <= mid ) modify( Lson(t),s,mid,a,b,delta);
    if ( mid < b )  modify( Rson(t) ,mid+1,e,a,b,delta);
    _pushUp(t);
}

/**< 点查询 */
int query( int t,int s,int e,int idx ){
    if ( s == e ) return ST[t].peak;
    _pushDown(t);
    int mid = (s+e) >> 1;
    int ret = ( idx <= mid ) ? query( Lson(t),s,mid,idx) : query( Rson(t),mid+1,e,idx);
    return ret;
}
/**< x - y 路径上的点 + val */
void change( int t,int s,int e,int x,int y ,int val){
    while ( Node[x].top != Node[y].top ){
        if ( Node[Node[x].top].depth < Node[Node[y].top].depth )
            swap(x,y);
        modify(t,s,e,Node[Node[x].top].nid,Node[x].nid,val);

        x = Node[x].top;
        x = Node[x].parent;
    }
    if ( Node[x].depth > Node[y].depth ) swap(x,y);

    modify(t,s,e,Node[x].nid,Node[y].nid,val);
}

inline void init(int n ){
    Ecnt = TIdx = 1;
    fill(Ver,Ver+n+1,0);
    for(int i=0;i<=n;++i)Node[i].heavy_son = 0;
}

char Cmd[5];
int n,m,p;
int main(){
    while( EOF != scanf("%d%d%d",&n,&m,&p) ){

        init(n);
        for(int i=1;i<=n;++i)scanf("%d",&Node[i].data);
        for(int i=0;i<m;++i){
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




        while(p--){
            scanf("%s",Cmd);
            if ( 'Q' == *Cmd ){
                int x;
                scanf("%d",&x);
                printf("%d\n",query(1,1,n,Node[x].nid));
            }else{
                int x,y,v;
                scanf("%d%d%d",&x,&y,&v);
                if ( 'D' == *Cmd ) v = -v;
                change(1,1,n,x,y,v);
            }
        }
    }
    return 0;
}

