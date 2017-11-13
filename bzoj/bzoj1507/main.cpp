#include "../../headers.h"


const int SIZE_Q = 256;

struct node_t {
    int next;
    int cnt;
    char arr[SIZE_Q];
//    void print( ){ ArrayDisp(arr,cnt); }
    void print( ){
        for ( int i = 0; i < cnt ;++i ){
            printf("%c",arr[i]);
        }
    }
};
node_t Bulk[400000];
int Head;
int toUsed;
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
void _fillNode( int p ,char const nub[],int n,int s = 0){
    Bulk[p].cnt += n;
    for ( int i = 0;i < n;++i )
        Bulk[p].arr[i+s] = nub[i];
}

inline void _linkNode( int p, int v ){
    Bulk[v].next = Bulk[p].next;
    Bulk[p].next = v;
}
void _cutNode( int p,int idx ){
    if ( idx == Bulk[p].cnt ) return ;
    int v = _newNode();
    _fillNode(v, Bulk[p].arr+idx, Bulk[p].cnt-idx );
    Bulk[p].cnt = idx;
    _linkNode(p,v);

}
void _mergeNode( int p ){
    while ( Bulk[p].next != -1 ){
        int v = Bulk[p].next;
        if ( Bulk[p].cnt + Bulk[v].cnt <= SIZE_Q ){
            _fillNode( p,Bulk[v].arr,Bulk[v].cnt,Bulk[p].cnt );
            Bulk[p].next = Bulk[v].next;
        }else break;
    }
}
void _dispNode( int p ,int n){
//    if ( n > Bulk[p].cnt ) {}
    for (int i = 0;i < n ;++i ){
        printf("%c",Bulk[p].arr[i]) ;
    }
}
//template<class T>
void Insert( int idx, char const nub[],int n ){
    int p = Head;
    int ns = 0;

    while ( idx > Bulk[p].cnt )
        idx -= Bulk[p].cnt,p = Bulk[p].next;

    _cutNode( p,idx );
    int leave = SIZE_Q - Bulk[p].cnt;
    _fillNode( p, nub, min(n,leave), Bulk[p].cnt );
    ns = min(n,leave);

    while ( ns < n ){
        int v = _newNode();
        _fillNode(v,nub+ns, min( SIZE_Q ,n-ns) );
        ns += min( SIZE_Q ,n-ns);
        _linkNode(p,v);
        p = v;
    }
    _mergeNode(p);
}

void Delete( int idx,int n ){
    int p = Head;
    while ( idx > Bulk[p].cnt )
        idx -= Bulk[p].cnt,p = Bulk[p].next;
    _cutNode( p,idx );
    int ns = 0;
    while ( ns < n ){
        int v = Bulk[p].next;
        _cutNode( v , min(Bulk[v].cnt,n-ns) );
        ns += min(Bulk[v].cnt,n-ns);
        Bulk[p].next = Bulk[v].next;
    }
    _mergeNode(p);
}

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
//    readfile("editor0.in");
//    writefile("editor.out");
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
