#include <cstdio>
#include <cmath>
#include <climits>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <cstring>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
using namespace std;

typedef double int_t;
double const eps = 1e-8;
double const PI = acos(-1.0);
inline int dcmp(double x){if(x > eps) return 1;return x < -eps ? -1 : 0;}
inline double toRad( double angle ){ return (angle/180*PI);}
struct point_t{
    int_t x,y;
    point_t( int_t xx=0,int_t yy=0 ): x(xx),y(yy){};
//    point_t( point_t const&a ): x(a.x),y(a.y) {};

    bool operator == (  point_t const&a )const {return dcmp(a.x-x) == 0 && dcmp(a.y-y) == 0;}
    bool operator != (  point_t const&a )const {return ! (*this == a ); }
    bool operator <  (  point_t const&a )const {return a.x != x ?  x < a.x : y < a.y;}
    friend ostream &operator<<(ostream &os,const point_t &p){os << "(" << p.x << ","<< p.y << ")" << endl;return os;}
};
typedef point_t vector_t;

vector_t operator-(  vector_t a,vector_t b ) {return point_t( a.x-b.x,a.y-b.y);}
vector_t operator*(  vector_t a,double t ) { return point_t( a.x*t,a.y*t);}
vector_t operator+(  vector_t a,vector_t b ) {return point_t( a.x+b.x,a.y+b.y);}

struct segment_t{
    point_t s,e;
    segment_t ( point_t aa = point_t(0,0),point_t bb = point_t(0,0) ):s(aa),e(bb) {};
    bool operator < ( segment_t const&sg )const{
        return s != sg.s ? s < sg.s : e < sg.e;
    }
};

struct line_t{
    point_t a,b;
    double angle;
    void cal(){angle = atan2(b.y-a.y, b.x-a.x);}
    line_t  ( point_t aa = point_t(0,0),point_t bb = point_t(0,0) ):a(aa),b(bb) {angle = atan2(b.y-a.y, b.x-a.x);}
    bool operator < ( line_t const&c ) const { return angle < c.angle ;};
};

struct circle_t {
    point_t p;
    int_t r;
    circle_t( point_t pp= point_t(0,0),int_t rr=0): p(pp),r(rr) {};
//    circle_t( int_t xx=0,int_t yy=0,int_t rr=0): x(xx),y(yy),r(rr) {};
};



/**< 叉积 oa * ob */
inline int_t cross(point_t const &O,point_t const &A,point_t const &B){return (A.x - O.x) * (B.y - O.y) - (B.x - O.x) * (A.y - O.y);}
/**< 点到点的距离 */
inline int_t Point2Point(point_t const &a, point_t const &b) {return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));}
/**< 线段的中点 */
inline point_t SegmentMid(point_t const &a, point_t const &b) {return point_t ( (a.x+b.x)/2.0 , (a.y+b.y)/2.0 );}
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
vector_t vector_rotate( vector_t const&a, double rad ){return vector_t( a.x*cos(rad)-a.y*sin(rad) , a.x*sin(rad)+a.y*cos(rad) );}


/**< 点p到线段a,b的距离 */
int_t Point2Segment( point_t const&a,point_t const&b,point_t const&p){
    if( a == b ) return Point2Point(a,p);
    vector_t v1  = b-a , v2 = p-a, v3 = p-b;
    if ( dcmp( vector_dot(v1,v2) ) < 0 ) return vector_length(v2);
    else if ( dcmp( vector_dot(v1,v3)) > 0 ) return vector_length(v3);
    return fabs( cross( a, b, p ) ) / vector_length(v1);
}


/**< 点到直线的距离 */
int_t Point2Line( point_t const&p,point_t const&a,point_t const&b){
    vector_t v1 = b-a,v2 = p-a;
    return fabs(cross(point_t(0,0),v1,v2)) / vector_length(v1) ;
}

/**<  点po是否在线段ab上 */
bool PointOnSegment( point_t const&a,point_t const&b, point_t const&po ){return dcmp( cross(po,a,b) ) == 0 && dcmp( vector_dot(a-po,b-po) ) < 0 ;}

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

/**< 点到简单多边形的距离 */
double Point2Simple( point_t * p ,int n , point_t const&po ){
    if ( PointInSimple( p,n,po ) ) return 0;
    double ans = Point2Segment( p[0],p[1] ,po);
    p[n] = p[0];
    for (int i = 1;i < n ;++i)
        ans = min( ans, Point2Segment( p[i] , p[i+1] ,po) );
    return ans;
}
/**< 线段相交 */
inline bool SegmentOnSegment(segment_t const&u,segment_t const&v){
    return max(u.s.x,u.e.x) >= min(v.s.x,v.e.x)
        && max(v.s.x,v.e.x) >= min(u.s.x,u.e.x)
        && max(u.s.y,u.e.y) >= min(v.s.y,v.e.y)
        && max(v.s.y,v.e.y) >= min(u.s.y,u.e.y)
        /**< 考虑交点是端点 */
        && cross(v.s,u.e,v.e) * cross(v.s,v.e,u.s) >= 0
        && cross(u.s,v.e,u.e) * cross(u.s,u.e,v.s) >= 0;
}
inline double Segment2Segment(segment_t const&u,segment_t const&v){
    return min(min(Point2Segment(u.s,u.e,v.s),Point2Segment(u.s,u.e,v.e)),
               min(Point2Segment(v.s,v.e,u.s),Point2Segment(v.s,v.e,u.e)));
}
/**< 直线是否与线段相交 */
/**< 注意向量要大于0 */
inline bool LineOnSegment( point_t const&p,vector_t const&v,segment_t const &s ){
    return cross(p,p+v,s.s)*cross(p,s.e,p+v) >= 0;
}
/**< 直线与直线的交点 */
point_t lineCrossline( line_t const&l1,line_t const&l2)
{
    point_t  p0(0,0);
    vector_t v = l1.b - l1.a;
    vector_t w = l2.b - l2.a;
    double t = cross( l2.a , l2.b , l1.a )/cross( p0,v,w );
    return l1.a + v * t;
}

/**< 三角形的面积 */
double TriangleArea( point_t const&a,point_t const&b, point_t const&c){return 0.5 * cross(a,b,c);}

/**< 计算多边形面积 ,点p需要先graham 排序*/
int_t PolygonArea(point_t p[], int n)
{
    double area = 0;
    for (int i = 0 ;i < n-1;++i )
        area += cross(p[0] , p[i] , p[i+1] );
    return area / 2.0;
}
/**< 多边形的周长 */
int_t PolygonSideLength(point_t p[], int n){
    double length = 0;
    for (int i = 0 ;i < n-1;++i ) length += Point2Point(p[i],p[i+1]);
    return length + Point2Point(p[n-1],p[0]);
}


/**< A如果比B更靠下更靠左返回真 */
inline bool isLowLeft(point_t const&A,point_t const&B){return A.y < B.y || ( A.y == B.y && A.x < B.x );}

/**< 按照对于pO的极角排序，极角相等的距离远的排在前面，因为后面要做一个unique */
point_t* pO;
inline bool comp4Graham(point_t const&A,point_t const&B){
    int_t t = cross(*pO,A,B);
    if ( t ) return t > 0LL;

    int_t a1 = A.x > pO->x ? A.x - pO->x : pO->x - A.x;
    int_t a2 = B.x > pO->x ? B.x - pO->x : pO->x - B.x;
    if ( a1 != a2 ) return a1 > a2;
//    if ( a1 != a2 ) return a1 < a2; //把这个变成近的放前面 ( 不严格凸包 )
    a1 = A.y > pO->y ? A.y - pO->y : pO->y - A.y;
    a2 = B.y > pO->y ? B.y - pO->y : pO->y - B.y;
    return a1 > a2;
}

/**< 相对于pO是否极角相等 */
inline bool isEqPolar(point_t const&A,point_t const&B){return 0LL == cross(*pO,A,B);}

/** \brief
 * 默认是严格凸包多边形的排序
 * 严格凸包是在极角排序的时候提前做了处理，所以我们只要把处理取反即可，
 * 代码上只要把极角相等的时候改成近的放前面，去掉unique函数 <= 改成 < 。
 */
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

    //将相对于pO的共线点均剔除，只保留最后一个 ( 严格凸包 )
    p = unique(P+1,P+n,isEqPolar);
    n = p - P;

    //真正的Graham循环
    int top = 2;
    for(int i=2;i<n;++i){
        /**< 不严格 这个<= 要改成 <  */
        while( top > 1 && cross(P[top-2],P[top-1],P[i]) <= 0LL )
            --top;
        P[top++] = P[i];
    }
    return top;
}
/**<  圆与直线的切线 ,返回向量的数量  */
int LineTangentCircle(point_t const&p , circle_t const&c, vector_t *v){
    vector_t u = c.p - p;
    double dist = vector_length(u);
    if ( dist < c.r )return 0;
    else if ( dcmp(dist-c.r) == 0 ){
        v[0] = vector_rotate(u,PI/2);
        return 1;
    }else {
        double ang = asin(c.r/dist);
        v[0] = vector_rotate(u,-ang);
        v[1] = vector_rotate(u,+ang);
        return 2;
    }
}

/**< CircleIntersectArea  两个圆的面积并 */
double CIA(circle_t const&a, circle_t const&b) {
    double d = Point2Point( a.p,b.p );
    if (d >= a.r + b.r)
        return 0;
    if (d <= fabs(a.r - b.r)) {
        int_t r = a.r < b.r ? a.r : b.r;
        return PI * r * r;
    }
    double ang1 = acos((a.r * a.r + d * d - b.r * b.r) / 2. / a.r / d);
    double ang2 = acos((b.r * b.r + d * d - a.r * a.r) / 2. / b.r / d);
    return ang1 * a.r * a.r + ang2 * b.r * b.r - d * a.r * sin(ang1);
}


/**< 有向面积交,有正负 */
/**< ConvexPolygonIntersectArea */
int_t CPIA(point_t a[], point_t b[], int na, int nb)
{
    point_t p[20], tmp[20];
    int tn, sflag, eflag;
    a[na] = a[0], b[nb] = b[0];
    memcpy(p,b,sizeof(point_t)*(nb + 1));
    for(int i = 0; i < na && nb > 2; i++){
        sflag = dcmp(cross(a[i],a[i + 1], p[0]));
        for(int j = tn = 0; j < nb; j++, sflag = eflag){
            if(sflag>=0) tmp[tn++] = p[j];
            eflag = dcmp(cross(a[i],a[i + 1], p[j + 1]));
            if((sflag ^ eflag) == -2)
                tmp[tn++] = lineCrossline( line_t( a[i], a[i + 1]),line_t(p[j], p[j + 1]) ); ///求交点
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


/**< 旋转卡壳法求凸包的最长点对 即凸包的直径*/
double Rotating_calipers( point_t *p ,int n ){
    int q = 1;
    double ans = 0;
    p[n] = p[0];
    point_t p1,p2;
    for (int i = 0 ;i < n;++i ){
        while ( fabs(TriangleArea(p[i],p[i+1],p[q+1])) > fabs(TriangleArea(p[i],p[i+1],p[q] )) )
            q = (q+1) % n;
//            deBug(p[i]);deBug(p[q]);
//            deBug(p[i+1]);deBug(p[q+1]);
            ans = max( ans ,max( Point2Point(p[i],p[q]), Point2Point(p[i+1],p[q+1]) ) );
    }
    return ans;
}

/**< 旋转卡壳法求凸包中最大三角形 注意网上很多都是错的,这个虽然慢了点,但是跟暴力得到的答案起码是一样的  */
double  max_TriangleArea( point_t *p,int n ){
    double ans = 0;
    p[n] = p[0];
    for (int i = 0; i < n; i ++) {
        int k = 2;
        for (int j = i + 1; j <= n; j ++) {
            while(TriangleArea(p[i], p[j], p[k]) < TriangleArea(p[i], p[j], p[(k + 1) % n]))
                k = (k + 1) % n;
            ans = max(ans,TriangleArea(p[i], p[j], p[k]));
        }
    }
    return ans;
}

/**< 两个凸包的最近距离 */
void _getTOP_DOWN( point_t *p1 ,int n1,int &l, point_t *p2,int n2,int &r ){
    l=r=0;
    for( int i=0;i<n1;i++ )
        if((dcmp(p1[i].y-p1[l].y))<0) l = i;
    for( int i=0;i<n2;i++ )
        if((dcmp(p2[i].y-p2[r].y))>0) r = i;
}
double _docp( point_t *p1 ,int n1,int l, point_t *p2,int n2,int r ){
    double ans = 1e90;
    int tmp;
    p1[n1] = p1[0];
    p2[n2] = p2[0];
//    auto f = [](const double&x)->int{ return dcmp(x); };
    for ( int i = 0;i < n1;++i ){
        if ( dcmp(ans) == 0 ) return 0;
//        while ( tmp = dcmp( fabs( TriangleArea(p1[l],p1[l+1],p2[r+1]) ) - fabs( TriangleArea(p1[l],p1[l+1],p2[r]) ) ) < 0 )
//            r = (r+1) % n2;

        while ( 1 ){
            double s1 = TriangleArea(p1[l],p1[l+1],p2[r+1]);
            double s2 = TriangleArea(p1[l],p1[l+1],p2[r]) ;
//            if ( f(s1) * f(s2) < 0 ) ans = 0;
            if ( SegmentOnSegment( segment_t(p1[l],p1[l+1]),segment_t(p2[r],p2[r+1]) ) )  ans = 0;
            s1 = fabs(s1);
            s2 = fabs(s2);
            tmp = dcmp( s1-s2);
            if ( tmp < 0 ) r = (r+1)%n2;
            else break;
        }

        if ( tmp == 0 )
            ans = min( ans ,Segment2Segment( segment_t( p1[l],p1[l+1] ) , segment_t(p2[r],p2[r+1]) ) );
        else
            ans = min( ans ,Point2Segment( p1[l],p1[l+1],p2[r]));
        l = (l+1)%n1;
    }
    return ans;
}

/**< distence of  Convex polygon*/
/**< 旋转卡壳法 计算 两个凸包的最近距离 ,这里判断了四次, 注意包含的情况,此处包含不算0  */
double DOCP( point_t *p1 ,int n1, point_t *p2,int n2 ){
    int l,r;
    _getTOP_DOWN( p1,n1,l,p2,n2,r );
    double ans = INT_MAX;
    ans = min( ans , _docp(p1,n1,l,p2,n2,r));
//    deBug(ans);
    ans = min(ans , _docp(p2,n2,r,p1,n1,l)) ;
//    deBug(ans);
    _getTOP_DOWN( p2,n2,r,p1,n1,l );
    ans = min( ans , _docp(p2,n2,r,p1,n1,l)) ;
//    deBug(ans);
    ans = min( ans , _docp(p1,n1,l,p2,n2,r));
//    deBug(ans);
    return ans;
}

/**< 两点计算 直线一般式方程 */
void LineEquation(point_t const&a,point_t const&b ,int_t&A,int_t&B,int_t&C ){
    assert( !(a==b) ); // assert( !(a.x==b.x));
    A = b.y - a.y;
    B = a.x - b.x;
    C = b.x*a.y - a.x*b.y;
}

const int _SIZE = 30000;
point_t _p[_SIZE];
line_t _q[_SIZE];
//auto OnLeft = [](line_t const&L,point_t const&p )->bool{ return cross( L.a, L.b, p ) > 0; };
inline bool OnLeft(line_t const&L,point_t const&p ){ return cross( L.a, L.b, p ) > 0; };
/**< 半平面交, 注意line要初始化angle, _size的大小*4 */
/**< l的方向 直线a->b 的左边为半平面区域 输出逆序,graham序 */
int HalfplaneIntersection( line_t * l , int n ,point_t *poly ){
    sort( l,l+n );

    int first = 0,last = 0;
    _q[first] = l[0];
    for ( int i = 1;i < n;++i ){
        while ( first < last && !OnLeft(l[i],_p[last-1])) last--;
        while ( first < last && !OnLeft(l[i],_p[first] )) first++;
        _q[++last] = l[i];
        if ( fabs(cross( point_t(0,0) ,(_q[last].b-_q[last].a) ,(_q[last-1].b-_q[last-1].a) )) < eps ){
            last--;
            if ( OnLeft( _q[last],l[i].a ) ) _q[last] = l[i];
        }
        if ( first < last ) _p[last-1] = lineCrossline( _q[last-1] , _q[last] );
    }
    while ( first < last && !OnLeft( _q[first] , _p[last-1]) ) last--;

    if ( last-first <= 1 ) return 0;
    _p[last] = lineCrossline(_q[last],_q[first]);

    int m = 0;
    for (int i = first ;i <= last ;++i ) poly[m++] = _p[i];
    return m;
}



/// - - - - - - - - - - - - - - - - - - Code line - - - - - - - - - - - - - - - - - - - - - - - ///


//int father[SIZE];
//void init( int n ){for (int i = 0 ;i <= n;++i) father[i] = i;}
//int find( int x ){return father[x] == x ? x : father[x] = find( father[x] );}
//void unite( int x,int y){father[ find(x) ] = find(y);}
//

const int N = 105;
int X[N], Y[N], Z[N];
point_t poly[N];
line_t L[N];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++)
            scanf("%d%d%d", &X[i], &Y[i], &Z[i]);
        double temp = 10000;
        for (int i = 0; i < n; i++) {
            int cnt = 0, flag = 1;
            for (int j = 0; j < n; j++)
                if (i != j) {
                    if (X[i] <= X[j] && Y[i] <= Y[j] && Z[i] <= Z[j]) {
                        flag = 0;
                        break;
                    }
                    if (X[i] >= X[j] && Y[i] >= Y[j] && Z[i] >= Z[j])
                        continue;
                    double A = (temp / Y[j] - temp / Z[j]) - (temp / Y[i] - temp / Z[i]);
                    double B = (temp / X[j] - temp / Z[j]) - (temp / X[i] - temp / Z[i]);
                    double C = temp / Z[j] - temp / Z[i];
                    L[cnt++] = line_t(point_t(0, -C / B), point_t(B, -A-C/B));
                }
            if (flag) {
                //x > 0 y > 0 -x-y+1 > 0
                L[cnt++] = line_t(point_t(0, 0), point_t(0, -1));
                L[cnt++] = line_t(point_t(0, 0), point_t(1, 0));
                L[cnt++] = line_t(point_t(0, 1), point_t(-1, 2));
                if (!HalfplaneIntersection(L, cnt, poly))
                    flag = 0;
            }
            if (flag)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}
/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
*/



