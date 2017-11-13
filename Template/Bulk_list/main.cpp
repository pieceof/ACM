#include "../../headers.h"

const int BLOCK_SIZE = 256;

struct node_t {
    int next;                /*!< 下个节点的指针 */
    int cnt;                 /*!< 该节点数组的大小 */
    char arr[BLOCK_SIZE];    /*!< 该节点数组 */
    void print( ){for ( int i = 0; i < cnt ;++i ) printf("%c",arr[i]);}
}Bulk[400000];      /*!< 预留内存池 */

int Head;                   /*!< 链表头指针 */
int toUsed;                 /*!< 计数 */
inline int _newNode(){
    Bulk[toUsed].next = -1;
    Bulk[toUsed].cnt = 0;
    return toUsed++;
}

inline void init(){
    toUsed = 1;
    Head = _newNode();
}
//template<class T>
/*!< 用nub给节点p的数组赋值,s是起点 */
void _fillNode( int p ,char const nub[],int n,int s = 0){
    Bulk[p].cnt += n;
    for ( int i = 0;i < n;++i ) Bulk[p].arr[i+s] = nub[i];
}
/*!< 将节点v链在p后面 */
inline void _linkNode( int p, int v ){
    Bulk[v].next = Bulk[p].next;
    Bulk[p].next = v;
}
/*!< 将节点p从idx这个位置切开,分成两个节点 */
void _cutNode( int p,int idx ){
    if ( idx == Bulk[p].cnt ) return ;
    int v = _newNode();
    _fillNode(v, Bulk[p].arr+idx, Bulk[p].cnt-idx );
    Bulk[p].cnt = idx;
    _linkNode(p,v);
}
/*!< 合并p节点与后面的若干节点  */
void _mergeNode( int p ){
    while ( Bulk[p].next != -1 ){
        int v = Bulk[p].next;
        if ( Bulk[p].cnt + Bulk[v].cnt <= BLOCK_SIZE ){
            _fillNode( p,Bulk[v].arr,Bulk[v].cnt,Bulk[p].cnt );
            Bulk[p].next = Bulk[v].next;
        }else break;
    }
}
void _dispNode( int p ,int n){
    for (int i = 0;i < n ;++i )printf("%c",Bulk[p].arr[i]) ;
}
//template<class T>
/*!< 在idx位置插入n个数 */
void Insert( int idx, char const nub[],int n ){
    int p = Head;
    int ns = 0;

    /*!< 先定位idx所在的节点 */
    while ( idx > Bulk[p].cnt )
        idx -= Bulk[p].cnt,p = Bulk[p].next;

    /*!< 切割该节点 */
    _cutNode( p,idx );

    /*!< 先把该节点先填满,尽可能不退化成链表 */
    int leave = BLOCK_SIZE - Bulk[p].cnt;
    _fillNode( p, nub, min(n,leave), Bulk[p].cnt );
    ns = min(n,leave);

    /*!< 用nub填充新节点,每填满一个就链在里面 */
    while ( ns < n ){
        int v = _newNode();
        _fillNode(v,nub+ns, min( BLOCK_SIZE ,n-ns) );
        ns += min( BLOCK_SIZE ,n-ns);
        _linkNode(p,v);
        p = v;
    }
    _mergeNode(p);
}

/*!< 删除idx为起点的n个数 */
void Delete( int idx,int n ){
    int p = Head;
    /*!< 定位idx位置并cut */
    while ( idx > Bulk[p].cnt )
        idx -= Bulk[p].cnt,p = Bulk[p].next;
    _cutNode( p,idx );

    /*!< 删除后面的节点 */
    int ns = 0;
    while ( ns < n ){
        int v = Bulk[p].next;
        _cutNode( v , min(Bulk[v].cnt,n-ns) );
        ns += min(Bulk[v].cnt,n-ns);
        Bulk[p].next = Bulk[v].next;
    }
    _mergeNode(p);
}
/*!< 从idx开始输入n个数 */
void Out( int idx ,int n ){
    int p = Head;
    while ( idx > Bulk[p].cnt )
        idx -= Bulk[p].cnt,p = Bulk[p].next;
    _cutNode( p,idx );
    int ns = 0;
    int v = Bulk[p].next;
    while ( ns < n && v != -1 ){
        _dispNode(v, min(n-ns,Bulk[v].cnt) );
        ns += min( Bulk[v].cnt ,n-ns);
        v = Bulk[v].next;
    }
    _mergeNode(p);
    printf("\n");
}
/*!< 输出整个区间 */
void print( ){
    int cnt = 0;
    for ( int p = Head ;p != -1 ;p = Bulk[p].next){
        deBug( cnt );
        Bulk[p].print();
        cnt ++;
    }
}

const int SIZE = 4100000;
char op[1000];
char str[SIZE];
char nub[SIZE];
int main(){
    int t;scanf("%d",&t);
    int cur = 0 , k;
    init();
    while (t-- ){
        scanf("%s",op);
        if (  *op == 'M' ) scanf("%d",&cur);
        else if ( *op == 'I' && scanf("%d",&k) != EOF ){
            for ( int i = 0; i < k ; ){
                gets( str );
                int len = strlen( str );
                for ( int j = 0;j < len;++j )nub[j+i] = str[j];
                i += len;
            }
            Insert(cur,nub,k);
        }
        else if ( *op == 'D' && scanf("%d",&k) != EOF ) Delete(cur,k);
        else if ( *op == 'G' && scanf("%d",&k) != EOF ) Out(cur,k);
        else if ( *op == 'P' ) cur--;
        else if ( *op == 'N' )  cur++;
    }
    return 0;
}
