#include "../../headers.h"

const int SIZE = 400000;

#define lson(x) ((x)<<1)
#define rson(x) (lson(x)|1)
#define ls lson(t)
#define rs rson(t)
struct stNode_t{
    int sum;        /*!< 该点对应的区间覆盖的数量 */
    int lazy;       /*!< 该区间要被完全覆盖 */
}ST[SIZE<<2];

inline void _pushUp( int t ,int s, int e ){
    if ( ST[t].lazy ){
        ST[t].sum = e-s+1;
    }
    else{
        ST[t].sum = ST[ls].sum + ST[rs].sum ;
    }
}
void _pushDown( int t ,int s,int e){
    if ( ST[t].lazy ){
        ST[rs].lazy = ST[ls].lazy = ST[t].lazy;
        int m = (s+e)>>1;
        _pushUp(ls,s,m);
        _pushUp(rs,m+1,e);
    }
}

void build( int t,int s,int e ){
    CLEAR(ST);
}

void modify( int t,int s,int e,int a,int b,int delta){
    if (a <= s && e <= b ){
        ST[t].lazy += delta;
        ST[t].sum = e-s+1;
        return;
    }
    _pushDown(t,s,e);
    int m = (s + e)>>1;
    if ( a <= m ) modify(ls,s,m,a,b,delta);
    if ( m < b ) modify( rs,m+1,e,a,b,delta);
    _pushUp(t,s,e);
}

int query( int t,int s,int e,int a,int b ){
    if ( a <= s && e <= b ){
        return ST[t].sum;
    }
    _pushDown(t,s,e);
    int ans = 0;
    int m = (s+e)>>1;
    if ( a <= m ) ans += query(ls,s,m,a,b);
    if ( m < b ) ans += query(rs,m+1,e,a,b);
    return ans;
}

struct Seq_t{
    int l,r;
}sq[SIZE];
int x[SIZE<<1];

int main(){
    int kase = 1;
    int l;
    int n;while (scanf("%d%d",&n,&l) != EOF ){

        int xCnt = 0;
        for ( int i = 0;i < n;++i ){
            scanf("%d%d",&sq[i].l,&sq[i].r);
            x[xCnt++] = sq[i].l;
            x[xCnt++] = sq[i].r;
        }
        sort( x+1, x+xCnt );
        xCnt = unique( x+1, x+xCnt ) - x - 1;
        build( 1,1,xCnt );
        int ans = n;
        for ( int i = n-1;i >= 0;--i ){
            int l = lower_bound(x+1,x+1+xCnt ,sq[i].l )-(x);
            int r = lower_bound(x+1,x+1+xCnt ,sq[i].r )-(x)-1;
            int tmp = query(1,1,xCnt,l,r);
            if ( tmp + l > r ) ans--;
            modify(1,1,xCnt,l,r,1);
        }
        printf("%d\n",ans);
    }

    return 0;
}
