#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef double int_t;
double const eps = 1E-6;
double const PI = acos(-1);
inline int dcmp(double x){if(x > eps) return 1;return x < -eps ? -1 : 0;}

struct point_t{
    int_t x,y;
    point_t( int_t xx=0,int_t yy=0 ): x(xx),y(yy){};
    point_t( point_t const&a ): x(a.x),y(a.y) {};
    point_t operator-(  point_t const&a )const {return point_t( x-a.x,y-a.y);}
    point_t operator+(  point_t const&a )const {return point_t( x+a.x,y+a.y);}
    bool operator == (  point_t const&a ){return dcmp(a.x-x) == 0 && dcmp(a.y-y) == 0;}
    bool operator <  (  point_t const&a ){return a.x != x ?  x < a.x : y < a.y;}
};

typedef point_t vector_t;

struct segment_t{
    point_t s,e;
    segment_t ( point_t aa = point_t(0,0),point_t bb = point_t(0,0) ):s(aa),e(bb) {};
};

struct round_t {
    int_t x, y, r;
    round_t( int_t xx=0,int_t yy=0,int_t rr=0): x(xx),y(yy),r(rr) {};
};

/**< 叉积 oa * ob */
int_t cross(point_t const &O,point_t const &A,point_t const &B){
    return (A.x - O.x) * (B.y - O.y) - (B.x - O.x) * (A.y - O.y);
}
int_t Point2Point(point_t a, point_t b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

/**< 向量的点积 */
double vector_dot ( vector_t const&a,vector_t const&b ){return a.x*b.x + a.y*b.y;}
/**< 向量的长度 */
double vector_length( vector_t const&a ){return sqrt(vector_dot(a,a));}
/**< 向量的夹角 */
double vector_angle( vector_t const&a,vector_t const&b ){return acos(vector_dot(a,b)/vector_length(a)/vector_length(b));}

/**< 向量的法线 输入要保证不是零向量 */
vector_t vector_normal( vector_t const&a ){
    double L = vector_length(a);
    return vector_t( -a.y/L , a.x/L );
}
/**< 向量旋转 向量a逆时针旋转rad  */
vector_t vector_rotate( vector_t const&a, double rad ){
    return vector_t( a.x*cos(rad)-a.y*sin(rad) , a.x*sin(rad)+a.y*cos(rad) );
}

/**< 点p到线段a,b的距离 */
int_t Point2Segment( point_t const&a,point_t const&b,point_t const&p){
    int_t ap_ab = (b.x - a.x)*(p.x - a.x)+(b.y - a.y)*(p.y - a.y);//cross( a , p , b );
    if ( ap_ab <= 0 )
        return sqrt( (p.x-a.x)*(p.x-a.x) + (p.y-a.y)*(p.y-a.y) );

    int_t d2 = ( b.x - a.x ) * ( b.x - a.x ) + ( b.y-a.y ) * ( b.y-a.y ) ;
    if ( ap_ab >= d2 ) return sqrt( (p.x - b.x )*( p.x - b.x ) + ( p.y - b.y )*( p.y - b.y ) ) ;

    int_t r = ap_ab / d2;
    int_t px = a.x + ( b.x - a.x ) *r;
    int_t py = a.y + ( b.y - a.y ) *r;
    return sqrt( (p.x - px)*(p.x - px) + (p.y - py)*(p.y - py) );
}

int_t Point2Line( point_t const&p,point_t const&a,point_t const&b){
    vector_t v1 = b-a,v2 = p-a;
    return fabs(cross(point_t(0,0),v1,v2)) / vector_length(v1) ;
}

/**<  点po是否在线段ab上 */
bool PointOnSegment( point_t const&a,point_t const&b, point_t const&po ){

    return dcmp( cross(po,a,b) ) == 0 && dcmp( vector_dot(a-po,b-po) ) < 0 ;
    return po.x >= min( a.x , b.x ) &&
           po.x <= max( a.x , b.x ) &&
           po.y >= min( a.y , b.y ) &&
           po.y <= max( a.y , b.y ) &&
           /**< 此处注意double 要判断 eps  */
           dcmp(( po.x - a.x ) * ( b.y - a.y ) - ( po.y - a.y ) * ( b.x - a.x )) == 0 ;
}

/**< 点po是否在简单多边形(凸)中  ,点p需要先graham 排序 */
bool PointInSimple( point_t * p ,int n , point_t const&po ){

    p[n] = p[0];
    bool flag = 0;
    int tmp;
    for ( int i = 0; i < n;++i ){
        if ( PointOnSegment( p[i] , p[i+1] , po ) ) return true;
        if ( p[i].y == p[i+1].y ) continue;
        p[i].y < p[i+1].y ? tmp = i+1 : tmp = i ;
        if ( po.y == p[tmp].y && po.x < p[tmp].x ) flag ^= 1;
        p[i].y > p[i+1].y ? tmp = i+1 : tmp = i ;
        if ( po.y == p[tmp].y && po.x < p[tmp].x ) continue ;

        if ( po.x < max( p[i].x , p[i+1].x ) &&
             po.y > min( p[i].y , p[i+1].y ) &&
             po.y < max( p[i].y , p[i+1].y ) ) flag ^= 1;
    }
    return flag;
}

int_t Point2Simple( point_t * p ,int n , point_t const&po ){
    return 0;
}


/**< 计算多边形面积 ,点p需要先graham 排序*/
int_t PolygonArea(point_t p[], int n)
{
    if(n < 3) return 0.0;
    int_t s = p[0].y * (p[n - 1].x - p[1].x);
    p[n] = p[0];
    for(int i = 1; i < n; ++ i)
        s += p[i].y * (p[i - 1].x - p[i + 1].x);
    return s * 0.5;
}

/**< 线段相交 */
bool SegmentOnSegment(segment_t const &u,segment_t const &v){
    return max(u.s.x,u.e.x) >= min(v.s.x,v.e.x)
        && max(v.s.x,v.e.x) >= min(u.s.x,u.e.x)
        && max(u.s.y,u.e.y) >= min(v.s.y,v.e.y)
        && max(v.s.y,v.e.y) >= min(u.s.y,u.e.y)
        /**< 考虑交点是端点 */
        && cross(v.s,u.e,v.e) * cross(v.s,v.e,u.s) >= 0
        && cross(u.s,v.e,u.e) * cross(u.s,u.e,v.s) >= 0;
}

/**< A如果比B更靠下更靠左返回真 */
inline bool isLowLeft(point_t const&A,point_t const&B){
    return A.y < B.y || ( A.y == B.y && A.x < B.x );
}


/**< 按照对于pO的极角排序，极角相等的距离远的排在前面，因为后面要做一个unique */
point_t* pO;
bool comp4Graham(point_t const&A,point_t const&B){
    int_t t = cross(*pO,A,B);
    if ( t ) return t > 0LL;

    int_t a1 = A.x > pO->x ? A.x - pO->x : pO->x - A.x;
    int_t a2 = B.x > pO->x ? B.x - pO->x : pO->x - B.x;
    if ( a1 != a2 ) return a1 > a2;

    a1 = A.y > pO->y ? A.y - pO->y : pO->y - A.y;
    a2 = B.y > pO->y ? B.y - pO->y : pO->y - B.y;
    return a1 > a2;
}

/**< 相对于pO是否极角相等 */
inline bool isEqPolar(point_t const&A,point_t const&B){
    return 0LL == cross(*pO,A,B);
}

/**<  Graham求凸包，结果当中没有共线点，起点总是最下最左点 */
int Graham(point_t P[],int n){
    if ( 1 == n ) return 1;

    //寻找最下最左点
    point_t *p = min_element(P,P+n,isLowLeft);

    //交换
    swap(*p,P[0]);

    if ( 2 == n ) return 2;

    //按极角排序，极角相等，距离近的排在前面
    pO = P;
    sort(P+1,P+n,comp4Graham);

    //将相对于pO的共线点均剔除，只保留最后一个
    p = unique(P+1,P+n,isEqPolar);
    n = p - P;

    //真正的Graham循环
    int top = 2;
    for(int i=2;i<n;++i){
        while( top > 1 && cross(P[top-2],P[top-1],P[i]) <= 0LL )
            --top;
        P[top++] = P[i];
    }
    return top;
}

/**< RoundIntersectArea   */
int_t RIA(round_t a, round_t b) {
    int_t d = Point2Point( point_t(a.x,a.y),point_t(b.x,b.y) );
    if (d >= a.r + b.r)
        return 0;
    if (d <= fabs(a.r - b.r)) {
        int_t r = a.r < b.r ? a.r : b.r;
        return PI * r * r;
    }
    int_t ang1 = acos((a.r * a.r + d * d - b.r * b.r) / 2. / a.r / d);
    int_t ang2 = acos((b.r * b.r + d * d - a.r * a.r) / 2. / b.r / d);
    int_t ret = ang1 * a.r * a.r + ang2 * b.r * b.r - d * a.r * sin(ang1);
    return ret;
}

/**< 直线与直线的交点 */
point_t lineCrossline(point_t a,vector_t v,point_t c,vector_t w)
{
    point_t  p0(0,0);
    vector_t u = a-c;
    int_t t = cross( p0,w,u ) / cross( p0,v,w );
    return point_t( a.x + v.x*t, a.y + v.y*t );
}

/**< 有向面积交,有正负 */
/**< ConvexPolygonIntersectArea */
int_t CPIA(point_t a[], point_t b[], int na, int nb)
{
    point_t p[20], tmp[20];
    int tn, sflag, eflag;
    a[na] = a[0], b[nb] = b[0];
    memcpy(p,b,sizeof(point_t)*(nb + 1));
    for(int i = 0; i < na && nb > 2; i++)
    {
        sflag = dcmp(cross(a[i],a[i + 1], p[0]));
        for(int j = tn = 0; j < nb; j++, sflag = eflag)
        {
            if(sflag>=0) tmp[tn++] = p[j];
            eflag = dcmp(cross(a[i],a[i + 1], p[j + 1]));
            if((sflag ^ eflag) == -2)
                tmp[tn++] = lineCrossline(a[i], a[i + 1], p[j], p[j + 1]); ///求交点
        }
        memcpy(p, tmp, sizeof(point_t) * tn);
        nb = tn, p[nb] = p[0];
    }
    if(nb < 3) return 0.0;
    return PolygonArea(p, nb);
}

/**< 有向面积交,有正负 */
/**< SimplePolygonIntersectArea 调用此函数 */
int_t SPIA(point_t a[], point_t b[], int na, int nb)
{
    int i, j;
    point_t t1[4], t2[4];
    int_t res = 0, num1, num2;
    a[na] = t1[0] = a[0], b[nb] = t2[0] = b[0];
    for(i = 2; i < na; i++)
    {
        t1[1] = a[i-1], t1[2] = a[i];
        num1 = dcmp(cross(t1[0],t1[1], t1[2]));
        if(num1 < 0) swap(t1[1], t1[2]);
        for(j = 2; j < nb; j++)
        {
            t2[1] = b[j - 1], t2[2] = b[j];
            num2 = dcmp(cross(t2[0],t2[1], t2[2]));
            if(num2 < 0) swap(t2[1], t2[2]);
            res += CPIA(t1, t2, 3, 3) * num1 * num2;
        }
    }
    return res;
}

/// - - - - - - - - - - - - - - - - - - Code line - - - - - - - - - - - - - - - - - - - - - - - ///
const int SIZE = 550;

point_t p[SIZE];
point_t v[SIZE*SIZE];

#include <iostream>

int main()
{
    int n ;
    int kase=1;
    while ( scanf("%d" ,&n ) && n ){
        for ( int i = 0;i < n;++i ){
            scanf("%lf%lf",&p[i].x,&p[i].y);
            v[i] = p[i];
        }
        int c = n-1;
        int ans = 1;

        for ( int i = 3;i < n ;++i ){
            for (int j = 0;j < i-1 ; ++j ){
                if ( SegmentOnSegment(segment_t(p[i],p[i-1]),segment_t(p[j],p[j+1])) ){
                    /// ----------------两个线段如果有同一个交点,可能是平行的没交点 ------------------///
                    if ( p[j] == p[i] || p[j] == p[i-1] || p[j+1] == p[i-1] || p[j+1] == p[i] )continue;
                    v[c++] = lineCrossline(p[i],p[i]-p[i-1] ,p[j], p[j]-p[j+1] );
                }
            }
        }
        sort(v,v+c);
        c = unique(v,v+c)-v;
//        printf("c : %d \n" ,c);
        int e = n-1;
        for (int i = 0 ;i < c;++i ){
            for (int j = 0 ; j < n-1;++j ){
                if ( PointOnSegment(p[j],p[j+1],v[i]) )e++;
            }
        }
//        printf("e : %d\n",e);
//        if(e+2-c == 1) printf("Case %d: There is %d piece.\n",kase++,e+2-c);
        printf("Case %d: There are %d pieces.\n",kase++,e+2-c);


//        printf("%d\n",ans);

    }
    return 0;
}

/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/

