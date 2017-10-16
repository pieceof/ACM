#include "../../headers.h"

const int SIZE = 100000+500;
struct _t{
    int idx,l,r,h;
    friend bool operator < (const _t &a,const _t&b){
        return a.h < b.h;
    }
}que[SIZE];

#define lson(x) ((x)<<1)
#define rson(x) (lson(x)|1)
#define ls lson(t)
#define rs rson(t)
struct stNode_t{
    int sum;
}ST[SIZE<<2];


inline void _pushUp( int t ){
    ST[t].sum = ST[ls].sum + ST[rs].sum;
}

//inline void _pushDown( int t ){
//    if ( 0 == ST[t].delay ) return;
//    llt &x = ST[t].delay;
//
//    ST[ls].sum += ST[ls].flag * x;
//    ST[ls].delay += x;
//
//    ST[rs].sum += ST[rs].flag * x;
//    ST[rs].delay += x;
//
//    x = 0;
//}

void build( int t,int s,int e ){
//    ST[t].delay = 0;
    if ( s == e ){
        ST[t].sum = 0;
        return;
    }
    int m = (s+e)>>1;
    build( ls , s, m);
    build( rs , m+1,e);
    _pushUp(t);

}

void modify( int t,int s,int e,int a,int b,int delta){
    if (a <= s && e <= b ){
        ST[t].sum += delta;
        return;
    }
//    _pushDown(t);

    int m = (s + e)>>1;
    if ( a <= m ) modify(ls,s,m,a,b,delta);
    if ( m < b ) modify( rs,m+1,e,a,b,delta);
    _pushUp(t);
}

int query( int t,int s,int e,int a,int b ){
    if ( a <= s && e <= b ){
        return ST[t].sum;
    }
//    _pushDown(t);
    int ret = 0;
    int m = (s + e)>>1;
    if (a <= m) ret += query(ls,s,m,a,b);
    if (m < b)  ret += query(rs,m+1,e,a,b);
    return ret;
}

struct _brick{
    int idx;
    int h;
    friend bool operator < (const _brick & a,const _brick & b){
        return a.h < b.h ;
    }
}brick[SIZE];

int ans[SIZE];
int main(){
    int kase = 1;
    int t;scanf( "%d",&t);while(t-- ){
        int n,m;
        scanf("%d%d",&n,&m);

        for (int i = 1 ;i <= n;++i ) {
            scanf("%d",&brick[i].h);
            brick[i].idx = i;
        }
        for ( int i = 0;i < m;++i ){
            scanf("%d%d%d",&que[i].l,&que[i].r,&que[i].h);

            que[i].l++;
            que[i].r++;
            que[i].idx = i;

        }
        sort ( brick+1,brick+n+1);
        sort ( que,que+m);
        int bi = 1;
        build( 1,1,n );
//        CLEAR(ST);
        for (int i = 0;i < m;++i ){
            while ( bi <= n && brick[bi].h <= que[i].h ){
                modify( 1,1,n, brick[bi].idx ,brick[bi].idx,1);
                bi++;
            }
            ans[ que[i].idx ] = query(1,1,n,que[i].l,que[i].r);
        }
        printf("Case %d:\n",kase++);
        for ( int i = 0;i < m;++i ){
            printf("%d\n",ans[i]);
        }
    }


    return 0;
}
