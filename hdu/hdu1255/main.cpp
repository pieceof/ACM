#include "../../headers.h"


const int SIZE = 20000;
struct segment_t{
    double l,r,h;
    int pos;
    segment_t( double ll = 0, double rr = 0,double hh = 0,int pp = 0):l(ll),r(rr),h(hh),pos(pp) {};
    friend bool operator < ( const segment_t& a,const segment_t&b){
        return a.h < b.h;
    }
}sg[SIZE];
double x[SIZE];

#define lson(x) ((x)<<1)
#define rson(x) (lson(x)|1)
#define ls lson(t)
#define rs rson(t)
struct stNode_t{
//    double len;
//    int sum;        /*!< 该点对应的区间覆盖的数量 */
    int lazy;           /*!< 该点对应的区间完全覆盖的次数 */
    double cover_one;
    double cover_two;
}ST[SIZE<<2];


inline void _pushUp( int t ,int s, int e ){
    if ( ST[t].lazy>1 ){    /*!< 如果此处被覆盖两次,直接计算长度 */
        ST[t].cover_two = ST[t].cover_one = x[e+1] - x[s];
    }else if ( ST[t].lazy == 1){
        /*!< 如果整段区间被覆盖一次,子区间未知 */

        ST[t].cover_one = x[e+1] - x[s]; /*!< 覆盖一次的先计算 */
        if ( s == e ){      /*!< 叶子节点不存在子区间,所以覆盖两次不存在 */
            ST[t].cover_two = 0;
        }else {
            /*!< 覆盖两次的是 左右节点各覆盖一次+的和 */
            ST[t].cover_two = ST[ls].cover_one + ST[rs].cover_one;
        }
    }else{
        /*!< 整段区间没有被覆盖过,但是子区间是否覆盖两次并不知道 */
        if ( s == e ){
            ST[t].cover_two = ST[t].cover_one = 0;
        }else {
            /*!< 直接用左右儿子节点更新该 节点 */
            ST[t].cover_two = ST[ls].cover_two + ST[rs].cover_two;
            ST[t].cover_one = ST[ls].cover_one + ST[rs].cover_one;
        }
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
    int t;scanf("%d",&t);while(t--){
        int n;scanf("%d",&n);
        int sgCnt = 0;
        int xCnt = 1;
        double x1,y1,x2,y2;
        for ( int i = 0;i < n;++i ){
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
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
        double ans = 0;
        for ( int i = 0;i < sgCnt-1;++i ){
            double h = sg[i].h;
            double h1 = sg[i+1].h;
            int l = lower_bound(x+1,x+1+xCnt ,sg[i].l )-(x);
            int r = lower_bound(x+1,x+1+xCnt ,sg[i].r )-(x)-1;
            modify(1,1,xCnt,l,r,sg[i].pos);
            ans += (h1-h) * ST[1].cover_two;
        }
        printf("%.2f\n",ans);
    }

    return 0;
}





