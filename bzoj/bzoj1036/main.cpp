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
/**�����ʷ�,���ر��ʷ�HLDD
 * ��Ȩ
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
    int depth;  /**< ��Ϊ0 */
    int size;
    int top;    /**< ����������������˽ڵ� */
    int nid;    /**< �µı�� ( ���߶����еı�� ) */
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
        // �ж��ر�
        if ( Node[u].size > Node[Node[t].heavy_son].size)
            Node[t].heavy_son = u;
    }

}

void dfsHeavyPath( int t,int top ){
    Node[t].top = top;
    Node[t].nid = TIdx; /**< TIdx ��dfs���ʵ�ʱ��� */
    NewIdx[TIdx++] = t; /**< ʱ�������,��¼���ʱ����ʵĽڵ��,���潨�߶������� */
    /**< ��������ڵ��,�洢��Ȩ,��ʵҲ���������¼��Ȩ */

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
//    int delay;
}ST[ SIZE << 2 ],ST2[SIZE << 2];

inline int lson( int t ) {return t<<1;}
inline int rson( int t ) {return (t<<1)|1;}

void _pushUp( int t ){
    ST[t].peak = ST[lson(t)].peak +  ST[rson(t)].peak;
    ST2[t].peak = max(ST2[lson(t)].peak , ST2[rson(t)].peak);
}
/*
void _pushDown( int t ){
//    if ( 0 == ST[t].delay ) return;
    if ( 0 != ST[t].delay ){
        int &k = ST[t].delay;
        ST[lson(t)].delay += k;
        ST[lson(t)].peak += k;
        ST[rson(t)].delay += k;
        ST[rson(t)].peak += k;
        ST[t].delay = 0;
    }
}*/

void buildTree( int t,int s,int e ){
//    ST[t].delay = 0;
//    ST2[t].delay = 0;
    if ( s == e ){
        ST[t].peak = Node[NewIdx[s]].data;
        ST2[t].peak = Node[NewIdx[s]].data;
        return;
    }
    int mid = (s+e) >> 1;
    buildTree(lson(t),s,mid);
    buildTree(rson(t),mid+1,e);
    _pushUp(t);
}

void modify( int t,int s,int e, int a,int b,int delta ){
    if ( a <= s && e <= b ){
//        ST[t].delay += delta;
        ST[t].peak = delta;
        ST2[t].peak = delta;
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
int query_max(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ){ return ST2[t].peak; }
//    _pushDown(t);
    int mid = (s+e)>>1;
    int ret = INT_MIN;
    if ( a <= mid )  ret = max( ret, query_max(lson(t),s,mid,a,b));
    if ( mid < b )   ret = max( ret, query_max(rson(t),mid+1,e,a,b));
    return ret;
}

/**< x - y ·���ϵĵ�  val */
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
/**< ��ѯ u->v �ߵ� sum */
int find( int t,int s,int e ,int u ,int v ){
    int tmp = 0 ;
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
    /**< ��֤u������Ľڵ� */
//    if ( u == v ) return tmp;
    if ( Node[u].depth > Node[v].depth ) swap(u,v);
//    tmp = max( tmp, query( t,s,e, Node[u].nid,Node[v].nid) );
    return tmp + query( t,s,e, Node[u].nid,Node[v].nid);
}
/**< ��ѯ u->v �ߵ� ���ֵ */
int find_max( int t,int s,int e ,int u ,int v ){
    int tmp = INT_MIN;
    while ( Node[u].top != Node[v].top ){
        if ( Node[ Node[u].top ].depth < Node[ Node[v].top ].depth )
            swap( v,u );
//        tmp += query(t,s,e,
//            Node[Node[u].top].nid,Node[u].nid);
        tmp = max( tmp , query_max(t,s,e,
            Node[Node[u].top].nid,Node[u].nid) );
        u = Node[u].top;
        u = Node[u].parent;
    }
    /**< ��֤u������Ľڵ� */
//    if ( u == v ) return tmp;
    if ( Node[u].depth > Node[v].depth ) swap(u,v);
    /**< ��Ȩ���ʷ� �˴� +1  */
    tmp = max( tmp, query_max( t,s,e, Node[u].nid,Node[v].nid) );
    return tmp ;
}

inline void init(int n ){
    Ecnt = TIdx = 1;
    fill(Ver,Ver+n+1,0);
    for(int i=0;i<=n;++i)Node[i].heavy_son = 0;
}

char Cmd[5];
int n,m,p;
int main(){
    while( EOF != scanf("%d",&n) ){

        init(n);
        for(int i=0;i < n-1;++i){
            int a,b;
            scanf("%d%d",&a,&b);
            mkEdge(a,b);
        }
        for(int i=1;i<=n;++i)scanf("%d",&Node[i].data);

        //�Ե�1���ڵ�Ϊ������
        dfsHeavyEdge(1,0,0);
        //�Ӹ��ڵ㿪ʼ�ݹ齨����
        dfsHeavyPath(1,1);
        //��ST[1]Ϊ���ڵ�����[1,N]���߶���
        buildTree(1,1,n);
        int u,v;
        int q;scanf("%d",&q);
        for (int i = 0;i < q;++i ){
            scanf("%s%d%d",Cmd,&u,&v);
//            deBug( u );
//            deBug( v );
            if ( 'Q' == *Cmd ){
                if ( Cmd[1] == 'S' )
                    printf("%d\n",find(1,1,n,u,v));
                else
                    printf("%d\n",find_max(1,1,n,u,v));

            }else{
                change(1,1,n,u,u,v);
            }
        }
    }
    return 0;
}

