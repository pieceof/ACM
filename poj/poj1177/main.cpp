#include "../../headers.h"


const int SIZE = 10050;
struct segment_t{
    int l,r,h;
    int pos;
    segment_t( int ll = 0, int rr = 0,int hh = 0,int pp = 0):l(ll),r(rr),h(hh),pos(pp) {};
    friend bool operator < ( const segment_t& a,const segment_t&b){
        if ( a.h == b.h ) return a.pos > b.pos;
        return a.h < b.h;
    }
}sg[SIZE];
int x[SIZE];

#define lson(x) ((x)<<1)
#define rson(x) (lson(x)|1)
#define ls lson(t)
#define rs rson(t)
struct stNode_t{
    int len;
//    int sum;        /*!< 覆盖的数量 */
    int lazy;       /*!< 完全覆盖的次数 */
    int cnt;        /*!< 覆盖的块数 */
    bool lc,rc;     /*!< 左右端点覆盖情况 */
}ST[SIZE<<2];



inline void _pushUp( int t ,int s, int e ){
    if ( ST[t].lazy ){
//        ST[t].sum = e-s+1,
        ST[t].len = x[e+1] - x[s];
        ST[t].cnt = 1;
        ST[t].lc = ST[t].rc = 1;

    }else if ( s == e ){

        //        ST[t].sum = 1,
        ST[t].len = 0;
        ST[t].cnt = 0;
        ST[t].lc = ST[t].rc = 0;

    }else{
        ST[t].lc = ST[ls].lc,ST[t].rc = ST[rs].rc;
//        ST[t].sum = ST[ls].sum + ST[rs].sum,
        ST[t].len = ST[ls].len + ST[rs].len;
        ST[t].cnt = ST[ls].cnt + ST[rs].cnt - (ST[ls].rc&&ST[rs].lc );
    }

}

void build( int t,int s,int e ){
    CLEAR(ST);
}

void modify( int t,int s,int e,int a,int b,int delta){
    if (a <= s && e <= b ){
        ST[t].lazy += delta;
        _pushUp(t,s,e);
        return;
    }
    int m = (s + e)>>1;
    if ( a <= m ) modify(ls,s,m,a,b,delta);
    if ( m < b ) modify( rs,m+1,e,a,b,delta);
    _pushUp(t,s,e);
}


int main(){
    int kase = 1;
    int n;while (scanf("%d",&n) != EOF ){
        int sgCnt = 0;
        int xCnt = 1;
        int x1,y1,x2,y2;
        for ( int i = 0;i < n;++i ){
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            if ( y2 > y1 )swap (y2 ,y1 );
            sg[sgCnt++] = segment_t(x1,x2,y2,1);
            sg[sgCnt++] = segment_t(x1,x2,y1,-1);
            x[xCnt++] = x1;
            x[xCnt++] = x2;
        }
        sort( x+1, x+xCnt );
        xCnt = unique( x+1, x+xCnt ) - x - 1;
        build( 1,1,xCnt );
        x[xCnt+1] = x[xCnt];
        sort( sg,sg+sgCnt );
        int ans = 0;
        int lastve = 0;
        for ( int i = 0;i < sgCnt;++i ){
            int h = sg[i].h;
            int h1 = (sgCnt==i+1)? h: sg[i+1].h;
            int l = lower_bound(x+1,x+1+xCnt ,sg[i].l )-(x);
            int r = lower_bound(x+1,x+1+xCnt ,sg[i].r )-(x)-1;
//            deBug( l );
//            deBug( r );
            modify(1,1,xCnt,l,r,sg[i].pos);
//            deBug(ST[1].cnt);
            int tmpup = ST[1].cnt * 2 * (h1-h);
            int tmpve = ST[1].len - lastve;
//            deBug( tmpup );
//            deBug( tmpve );
            lastve = ST[1].len;
            ans += tmpup + abs(tmpve);
        }

        Ans(ans);
    }
    return 0;
}





