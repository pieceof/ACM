#include "../../headers.h"

#define lson(x) ((x)<<1)
#define rson(x) (lson(x)|1)
#define ls lson(t)
#define rs rson(t)

const int SIZE = 500000+500;

map<int,int> YearID;
int Years[SIZE];
int YearCnt ;
void init( ){
    YearID.clear();
    YearCnt = 1;
}
int Insert( int year ){
    if ( YearID.count(year) ) return YearID[year];
    Years[ YearCnt ] = year;
    return YearID[year] = YearCnt++;
}
int rain[SIZE];


struct stNode_t{
//    int sum;
    int max;
}ST[SIZE<<2];


inline void _pushUp( int t ){
//    ST[t].sum = ST[ls].sum + ST[rs].sum;
    ST[t].max = max(ST[ls].max, ST[rs].max);
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
        ST[t].max = rain[s];
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

int nn;
int query( int t,int s,int e,int a,int b ){

    if ( a <= s && e <= b ){
//        return ST[t].sum;
        return ST[t].max;
    }
//    _pushDown(t);
    int ret = 0;
    int m = (s + e)>>1;
    if (a <= m) ret = max(ret,query(ls,s,m,a,b));
    if (m < b)  ret = max(ret,query(rs,m+1,e,a,b));
    return ret;
}

void yes( ){
    printf("true\n");
}
void no(){
    printf("false\n");
}
void maybe(){
    printf("maybe\n");
}

int main(){

    int n,m;
    while (scanf("%d",&n ) != EOF ){
        nn = n;
        init();
        int yi,ri;
        for ( int i = 1;i <= n;++i ){
            scanf("%d%d",&yi,&ri);
            Insert( yi );
            rain[i] = ri;
        }
        build(1,1,n);
        scanf("%d",&m);
        int x,y;
        //以下m行每行包含两个数Y和X，即询问“X年是自Y年以来降雨量最多的。
        while ( m -- ){
            scanf("%d%d",&y,&x);
            if ( x < y )while(1);
            if ( x == y ){
                yes();
                continue;
            }
            int fx = YearID.count(x);
            int fy = YearID.count(y);
//            deBug( y );
//            deBug( x );
            int xid,yid;
            if ( fx ) xid = YearID[x];
            else      xid = lower_bound(Years+1,Years+n+1,x) - Years;
            if ( fy ) yid = YearID[y];
            else      yid = lower_bound(Years+1,Years+n+1,y) - Years;

            int mrain;
////            deBug( xid );deBug( fx );
////            deBug( yid );deBug( fy );
//            2.  (y+1 ~ x) < x <= y
            if ( 0 == fx && 0 == fy ) {
                maybe();

            }else if( fx && fy ){

                if ( rain[xid] > rain[yid] ){
                    no();
                    continue;
                }
                // yid >= xid ;
                if ( yid + 1 == xid ){
                    if ( y + 1 == x ) yes();
                    else              maybe();
                    continue;
                }
                mrain = query( 1,1,n,yid+1,xid-1);
                if ( mrain < rain[xid] ){
                    if (xid-yid == x - y ) yes();
                    else maybe();
                }else no();

            }else if ( fx && 0 == fy ){
                if ( yid == xid ){
                    maybe();
                    continue;
                }
                mrain = query( 1,1,n, yid , xid-1 );
                if ( mrain < rain[xid] ) maybe();
                else             no();
            }else if ( fy && 0 == fx ){
                if ( yid + 1 == xid ){
                    maybe();
                    continue;
                }
                mrain = query( 1,1,n, yid+1,xid-1 );
                if ( mrain < rain[yid] ) maybe();
                else no();
            }else while(1);

        }


    }

    return 0;
}
