#include <cstdio>
#include <cmath>
#include <climits>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <map>
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
    int id;
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



/**< ��� oa * ob */
inline int_t cross(point_t const &O,point_t const &A,point_t const &B){return (A.x - O.x) * (B.y - O.y) - (B.x - O.x) * (A.y - O.y);}
/**< �㵽��ľ��� */
inline int_t Point2Point(point_t const &a, point_t const &b) {return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));}
/**< �߶ε��е� */
inline point_t SegmentMid(point_t const &a, point_t const &b) {return point_t ( (a.x+b.x)/2.0 , (a.y+b.y)/2.0 );}
/**< �����ĵ�� */
double vector_dot ( vector_t const&a,vector_t const&b ){return a.x*b.x + a.y*b.y;}
/**< �����ĳ��� */
double vector_length( vector_t const&a ){return sqrt(vector_dot(a,a));}
/**< �����ļн� */
double vector_angle( vector_t const&a,vector_t const&b ){return acos(vector_dot(a,b)/vector_length(a)/vector_length(b));}

/**< �����ķ��� ����Ҫ��֤���������� */
vector_t vector_normal( vector_t const&a ){
    double L = vector_length(a);
    return vector_t( -a.y/L , a.x/L );
}
/**< ������ת ����a��ʱ����תrad  */
vector_t vector_rotate( vector_t const&a, double rad ){return vector_t( a.x*cos(rad)-a.y*sin(rad) , a.x*sin(rad)+a.y*cos(rad) );}


/**< ��p���߶�a,b�ľ��� */
int_t Point2Segment( point_t const&a,point_t const&b,point_t const&p){
    if( a == b ) return Point2Point(a,p);
    vector_t v1  = b-a , v2 = p-a, v3 = p-b;
    if ( dcmp( vector_dot(v1,v2) ) < 0 ) return vector_length(v2);
    else if ( dcmp( vector_dot(v1,v3)) > 0 ) return vector_length(v3);
    return fabs( cross( a, b, p ) ) / vector_length(v1);
}


/**< �㵽ֱ�ߵľ��� */
int_t Point2Line( point_t const&p,point_t const&a,point_t const&b){
    vector_t v1 = b-a,v2 = p-a;
    return fabs(cross(point_t(0,0),v1,v2)) / vector_length(v1) ;
}

/**<  ��po�Ƿ����߶�ab�� */
bool PointOnSegment( point_t const&a,point_t const&b, point_t const&po ){return dcmp( cross(po,a,b) ) == 0 && dcmp( vector_dot(a-po,b-po) ) <= 0 ;}
//��bug
/**< ��po�Ƿ��ڼ򵥶����  ,��p��Ҫ��graham ���� */
//bool PointInSimple( point_t * p ,int n , point_t const&po ){
//
//    p[n] = p[0];
//    bool flag = 0;
//    int tmp;
//    for ( int i = 0; i < n;++i ){
//        if ( PointOnSegment( p[i] , p[i+1] , po ) ) return true;
//        if ( p[i].y == p[i+1].y ) continue;
//        p[i].y < p[i+1].y ? tmp = i+1 : tmp = i ;
//        if ( po.y == p[tmp].y && po.x < p[tmp].x ) flag ^= 1;
//        p[i].y > p[i+1].y ? tmp = i+1 : tmp = i ;
//        if ( po.y == p[tmp].y && po.x < p[tmp].x ) continue ;
//
//        if ( po.x < max( p[i].x , p[i+1].x ) &&
//             po.y > min( p[i].y , p[i+1].y ) &&
//             po.y < max( p[i].y , p[i+1].y ) ) flag ^= 1;
//    }
//    return flag;
//}
/**< ��po�Ƿ��ڼ򵥶������, ���� */
bool PointInSimple( point_t * p ,int n , point_t const&po ){
    int wn = 0;
    p[n] = p[0];
    for (int i = 0;i < n;++i ){
        if ( PointOnSegment(p[i],p[i+1],po)) return 1;
        int k = dcmp( cross(p[i],p[i+1],po) );
        int d1 = dcmp(p[i].y-po.y);
        int d2 = dcmp(p[i+1].y-po.y);
        if ( k > 0 && d1 <= 0 && d2 > 0 ) wn++;
        if ( k < 0 && d2 <= 0 && d1 > 0 ) wn--;
    }
    if ( wn != 0 ) return 1;
    return 0;
}



/**< �㵽�򵥶���εľ��� */
/**< �����Ż�,��Ϊ�Ǹ����庯�� n/2 ���Խ�� */
double Point2Simple( point_t * p ,int n , point_t const&po ){
//    if ( PointInSimple( p,n,po ) ) return 0;
    double ans = Point2Segment( p[0],p[1] ,po);
    p[n] = p[0];
    for (int i = 1;i < n ;++i)
        ans = min( ans, Point2Segment( p[i] , p[i+1] ,po) );
    return ans;
}
/**< �߶��ཻ */
inline bool SegmentOnSegment(segment_t const&u,segment_t const&v){
    return max(u.s.x,u.e.x) >= min(v.s.x,v.e.x)
        && max(v.s.x,v.e.x) >= min(u.s.x,u.e.x)
        && max(u.s.y,u.e.y) >= min(v.s.y,v.e.y)
        && max(v.s.y,v.e.y) >= min(u.s.y,u.e.y)
        /**< ���ǽ����Ƕ˵� */
        && cross(v.s,u.e,v.e) * cross(v.s,v.e,u.s) >= 0
        && cross(u.s,v.e,u.e) * cross(u.s,u.e,v.s) >= 0;
}
inline double Segment2Segment(segment_t const&u,segment_t const&v){
    return min(min(Point2Segment(u.s,u.e,v.s),Point2Segment(u.s,u.e,v.e)),
               min(Point2Segment(v.s,v.e,u.s),Point2Segment(v.s,v.e,u.e)));
}
/**< ֱ���Ƿ����߶��ཻ */
/**< ע������Ҫ����0 */
//inline bool LineOnSegment( point_t const&p,vector_t const&v,segment_t const &s ){
//    return cross(p,p+v,s.s)*cross(p,s.e,p+v) >= 0;
//}
inline bool LineOnSegment( line_t const&l,segment_t const &s ){
    return cross(l.a,l.b,s.s)*cross(l.a,s.e,l.b) >= 0;
}
/**< ֱ����ֱ�ߵĽ��� */
point_t lineCrossline( line_t const&l1,line_t const&l2)
{
    point_t  p0(0,0);
    vector_t v = l1.b - l1.a;
    vector_t w = l2.b - l2.a;
    double t = cross( l2.a , l2.b , l1.a )/cross( p0,v,w );
    return l1.a + v * t;
}

/**< �����ε����  ������� */
double TriangleArea( point_t const&a,point_t const&b, point_t const&c){return 0.5 * cross(a,b,c);}

/**< ����������� ,��p��Ҫ��graham ����*/
double  PolygonArea(point_t p[], int n)
{
    double area = 0;
    for (int i = 0 ;i < n-1;++i )
        area += cross(p[0] , p[i] , p[i+1] );
    return area / 2.0;
}
/**< ����ε��ܳ� */
int_t PolygonSideLength(point_t p[], int n){
    double length = 0;
    for (int i = 0 ;i < n-1;++i ) length += Point2Point(p[i],p[i+1]);
    return length + Point2Point(p[n-1],p[0]);
}


/**< A�����B�����¸����󷵻��� */
inline bool isLowLeft(point_t const&A,point_t const&B){return A.y < B.y || ( A.y == B.y && A.x < B.x );}

/**< ���ն���pO�ļ������򣬼�����ȵľ���Զ������ǰ�棬��Ϊ����Ҫ��һ��unique */
point_t* pO;
inline bool comp4Graham(point_t const&A,point_t const&B){
    int_t t = cross(*pO,A,B);
    if ( t ) return t > 0LL;

    int_t a1 = A.x > pO->x ? A.x - pO->x : pO->x - A.x;
    int_t a2 = B.x > pO->x ? B.x - pO->x : pO->x - B.x;
    if ( a1 != a2 ) return a1 > a2;
//    if ( a1 != a2 ) return a1 < a2; //�������ɽ��ķ�ǰ�� ( ���ϸ�͹�� )
    a1 = A.y > pO->y ? A.y - pO->y : pO->y - A.y;
    a2 = B.y > pO->y ? B.y - pO->y : pO->y - B.y;
    return a1 > a2;
}

/**< �����pO�Ƿ񼫽���� */
inline bool isEqPolar(point_t const&A,point_t const&B){return 0LL == cross(*pO,A,B);}

/** \brief
 * Ĭ�����ϸ�͹������ε�����
 * �ϸ�͹�����ڼ��������ʱ����ǰ���˴�����������ֻҪ�Ѵ���ȡ�����ɣ�
 * ������ֻҪ�Ѽ�����ȵ�ʱ��ĳɽ��ķ�ǰ�棬ȥ��unique���� <= �ĳ� < ��
 */
/**<  Graham��͹�����������û�й��ߵ㣬���������������� */
int Graham(point_t P[],int n){
    if ( 1 == n ) return 1;

    //Ѱ�����������
    point_t *p = min_element(P,P+n,isLowLeft);

    //����
    swap(*p,P[0]);

    if ( 2 == n ) return 2;

    //���������򣬼�����ȣ������������ǰ��
    pO = P;
    sort(P+1,P+n,comp4Graham);

    //�������pO�Ĺ��ߵ���޳���ֻ�������һ�� ( �ϸ�͹�� )
    p = unique(P+1,P+n,isEqPolar);
    n = p - P;

    //������Grahamѭ��
    int top = 2;
    for(int i=2;i<n;++i){
        /**< ���ϸ� ���<= Ҫ�ĳ� <  */
        while( top > 1 && cross(P[top-2],P[top-1],P[i]) <= 0LL )
            --top;
        P[top++] = P[i];
    }
    return top;
}
/**<  Բ��ֱ�ߵ����� ,��������������  */
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

/**< CircleIntersectArea  ����Բ������� */
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


/**< ���������,������ */
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
                tmp[tn++] = lineCrossline( line_t( a[i], a[i + 1]),line_t(p[j], p[j + 1]) ); ///�󽻵�
        }
        memcpy(p, tmp, sizeof(point_t) * tn);
        nb = tn, p[nb] = p[0];
    }
    if(nb < 3) return 0.0;
    return PolygonArea(p, nb);
}

/**< ���������,������ */
/**< SimplePolygonIntersectArea ���ô˺��� */
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


/**< ��ת���Ƿ���͹�������� ��͹����ֱ��*/
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

/**< ��ת���Ƿ���͹������������� ע�����Ϻܶ඼�Ǵ��,�����Ȼ���˵�,���Ǹ������õ��Ĵ�������һ����  */
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

/**< ����͹����������� */
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
/**< ��ת���Ƿ� ���� ����͹����������� ,�����ж����Ĵ�, ע����������,�˴���������0  */
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

/**< ������� ֱ��һ��ʽ���� */
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
/**< ��ƽ�潻, ע��lineҪ��ʼ��angle, _size�Ĵ�С*4 */
/**< l�ķ��� ֱ��a->b �����Ϊ��ƽ������ �������,graham�� */
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
/**< ���������Բ  */
circle_t CircumscribedCircle(point_t p1, point_t p2, point_t p3) {
    double Bx = p2.x - p1.x, By = p2.y - p1.y;
    double Cx = p3.x - p1.x, Cy = p3.y - p1.y;
    double D = 2 * (Bx*Cy - By*Cx);
    double cx = (Cy*(Bx*Bx + By*By) - By*(Cx*Cx + Cy*Cy)) / D + p1.x;
    double cy = (Bx*(Cx*Cx + Cy*Cy) - Cx*(Bx*Bx + By*By)) / D + p1.y;
    point_t _p = point_t(cx, cy);
    return circle_t(_p, Point2Point(p1,_p));
}    //���������Բ

/** �߶��ϵ�������
 *  �����˵������ľ���ֵ�� gcd + 1
 */
/**  pick ��ʽ
 *  ��� = �߽���� �� 2 �� �ڲ����� �� 1
 */
/** ������ABCD,��֪�Զ���A(X1,Y1),C(X3,Y3) (���öԽ��߿ɵ���������)
 *  x2:=(x1+x3+y3-y1)/2; y2:=(y1+y3+x1-x3)/2;
 *  x4:=(x1+x3-y3+y1)/2; y4:=(y1+y3-x1+x3)/2;
 */

bool isConvexPolygon( point_t*p,int n,int &shunxu ){
    p[n] = p[0];
    p[n+1] = p[1];
    int dir=0;
    for(int i = 0 ;i < n;i++){
        int temp=dcmp( cross(p[i],p[i+1],p[i+2]) ) ;
        if( dir == 0 ) //��һ�β�Ϊ0����ֵ
            dir = temp;
        if ( temp != 0 )shunxu = temp;
        if( dir * temp < 0 ) //���͵�һ�εķ���ͬ��˵������͹��
            return false;
    }
    return true; //Ϊ͹��
}
/// - - - - - - - - - - - - - - - - - - Code line - - - - - - - - - - - - - - - - - - - - - - - ///

point_t p[120];
int main(){
    int n;
    while(cin>>n && n){
        point_t po;
        cin>>po.x>>po.y;
        for (int i = 0;i < n;++i)
            cin>>p[i].x>>p[i].y;
        if ( PointInSimple(p,n,po)){
            puts("Y");
        }else {
            puts("N");
        }
//        if ( isInSimple( p , n , po ) ) {
//            puts("Y");
//            continue;
//        }else {
//            puts("N");
//            continue;
//        }
//        double ans = PointTOline( p[0],p[1],po );
//        p[n] = p[0];
//        for (int i = 1;i < n ;++i)
//            ans = min( ans, PointTOline(p[i] , p[i+1] , po) );
//        if ( ans <= 0 ){
//            puts("Y");
//        }else {
//            puts("N");
//        }
        //printf("%.2lf\n",ans);
    }
    return 0;
}
/*
    ios.sync_with_stdio(false);  /// ��ôcin, �Ͳ��ܸ�C�� scanf��sscanf, getchar, fgets֮���һ��ʹ���ˡ�
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/



