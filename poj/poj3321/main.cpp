#include "../../headers.h"

const int SIZE = 1000010;

struct edge_t{
    int to;
    int next;
}Edge[SIZE<<1];

int Ver[SIZE];
int Ecnt;

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
    int sum;  /**< 区间和 */
}ST[SIZE<<3];

inline int lson( int t ) {return t<<1;}
inline int rson( int t ) {return (t<<1)|1;}

inline void _pushUp( int t ){
    ST[t].sum = ST[lson(t)].sum + ST[rson(t)].sum;
}

void build( int t,int s,int e ){
    if ( s == e ){
        ST[t].sum = 1;
        return;
    }
    int m = (s+e)>>1;
    build( lson(t) , s, m);
    build( rson(t) , m+1,e);
    _pushUp(t);

}

void modify( int t,int s,int e,int a,int b){
    if (a <= s && e <= b ){
        ST[t].sum ^= 1;
        return;
    }
    int m = (s + e)>>1;
    if ( a <= m ) modify(lson(t),s,m,a,b);
    if ( m < b ) modify( rson(t),m+1,e,a,b);
    _pushUp(t);
}

int query( int t,int s,int e,int a,int b ){
    if ( a <= s && e <= b ){
        return ST[t].sum;
    }
    int ret = 0;
    int m = (s + e)>>1;
    if (a <= m) ret += query(lson(t),s,m,a,b);
    if (m < b)  ret += query(rson(t),m+1,e,a,b);
    return ret;
}

inline void initTree(int n){
    Ecnt = Ncnt = 1;
    CLEAR(Ver);
}

int main(){

    int n,m;
    int root=1;
    while ( scanf("%d",&n) != EOF ){
        initTree(n);

        int a,b;
        for ( int i = 1;i < n ;++i ){
            scanf("%d%d",&a,&b);
            mkEdge(a,b);
        }
        dfs(root,0);
        build(1,1,n<<1);
//    1
//2       3
//
//1 3 3 2 2 1
//1 1 1 1 1 1
//Q 1
//C 2
//Q 1


        scanf("%d",&m);
        char cmd[2];
        int x;
        while ( m-- ){
            scanf("%s%d",cmd,&x);
            if (*cmd == 'Q'){
//                cout << InIdx[x] << " " << OutIdx[x] << endl;
                int ans = query(1,1,n<<1,InIdx[x],OutIdx[x]);
                printf("%d\n",ans/2);
            }else {
//                cout << InIdx[x] << " " << OutIdx[x] << endl;
                modify(1,1,n<<1,InIdx[x],InIdx[x]);
                modify(1,1,n<<1,OutIdx[x],OutIdx[x]);
            }
        }
//        printf("\n");


    }


    return 0;
}
