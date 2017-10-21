#include "../../headers.h"

#define lson(x) ((x)<<1)
#define rson(x) (lson(x)|1)
#define ls lson(t)
#define rs rson(t)

const int SIZE = 500000+500;

struct _t{
    int p,d;
    friend bool operator < ( const _t&a ,const _t&b) {
        if ( a.p == b.p )return a.d < b.d;
        return a.p < b.p;
    }
}hotel[SIZE];


struct stNode_t{
//    int sum;
    int min;
}ST[SIZE<<2];


inline void _pushUp( int t ){
//    ST[t].sum = ST[ls].sum + ST[rs].sum;
    ST[t].min = min(ST[ls].min, ST[rs].min);
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
//        ST[t].sum = 0;
        ST[t].min = hotel[s].d;
        return;
    }
    int m = (s+e)>>1;
    build( ls , s, m);
    build( rs , m+1,e);
    _pushUp(t);

}
//
//void modify( int t,int s,int e,int a,int b,int delta){
//    if (a <= s && e <= b ){
//        ST[t].sum += delta;
//        return;
//    }
////    _pushDown(t);
//
//    int m = (s + e)>>1;
//    if ( a <= m ) modify(ls,s,m,a,b,delta);
//    if ( m < b ) modify( rs,m+1,e,a,b,delta);
//    _pushUp(t);
//}

int query( int t,int s,int e,int a,int b ){

    if ( a <= s && e <= b ){
//        return ST[t].sum;
        return ST[t].min;
    }
//    _pushDown(t);
    int ret = INT_MAX;
    int m = (s + e)>>1;
    if (a <= m) ret = min(ret,query(ls,s,m,a,b));
    if (m < b)  ret = min(ret,query(rs,m+1,e,a,b));
    return ret;
}

int ansp[SIZE] ,ansd[SIZE];

int main(){
//    readfile("in.txt");
    int n;
    while ( scanf( "%d" ,&n) != EOF ){

        for ( int i = 1 ;i <= n;++i ){
            scanf("%d%d",&hotel[i].p,&hotel[i].d);
        }
        sort( hotel + 1,hotel + n + 1);

        build( 1, 1, n);
        int ans = 0;
        int last = 1;
        int i = 1;
        for ( ; hotel[i].p == hotel[last].p && i <= n ;++i )
            ansp[ans] = hotel[i].p ,
            ansd[ans++]  = hotel[i].d;
//            printf("%d %d\n",hotel[i].p,hotel[i].d);
//        deBug( i );
        for (  ;i <= n;++i ){
            if ( hotel[last].p != hotel[i].p )last = i;
            int r = query( 1, 1, n, 1, last-1 );
            if ( hotel[i].d <= r )
                ansp[ans] = hotel[i].p ,
                ansd[ans++]  = hotel[i].d;
        }
        Ans(ans);
        for (int i = 0;i < ans;++i ){
            printf("%d %d\n",ansp[i],ansd[i]);
        }

    }
    return 0;
}
