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
double const eps = 1E-6;
double const PI = acos(-1);
inline int dcmp(double x){if(x > eps) return 1;return x < -eps ? -1 : 0;}

struct point_t{
    int_t x,y;
    point_t( int_t xx=0,int_t yy=0 ): x(xx),y(yy){};
    point_t( point_t const&a ): x(a.x),y(a.y) {};
    point_t operator-(  point_t const&a )const {return point_t( x-a.x,y-a.y);}
    point_t operator+(  point_t const&a )const {return point_t( x+a.x,y+a.y);}
    bool operator == (  point_t const&a )const {return dcmp(a.x-x) == 0 && dcmp(a.y-y) == 0;}
    bool operator <  (  point_t const&a )const {return a.x != x ?  x < a.x : y < a.y;}
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

/**< ��� oa * ob */
inline int_t cross(point_t const &O,point_t const &A,point_t const &B){
    return (A.x - O.x) * (B.y - O.y) - (B.x - O.x) * (A.y - O.y);
}
inline int_t Point2Point(point_t const &a, point_t const &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline point_t SegmentMid(point_t const &a, point_t const &b) {
    return point_t ( (a.x+b.x)/2.0 , (a.y+b.y)/2.0 );
}
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
vector_t vector_rotate( vector_t const&a, double rad ){
    return vector_t( a.x*cos(rad)-a.y*sin(rad) , a.x*sin(rad)+a.y*cos(rad) );
}

/**< �����ε���� */
double TriangleArea( point_t const&a,point_t const&b, point_t const&c){return 0.5 * cross(a,b,c);}

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
bool PointOnSegment( point_t const&a,point_t const&b, point_t const&po ){

    return dcmp( cross(po,a,b) ) == 0 && dcmp( vector_dot(a-po,b-po) ) < 0 ;
    return po.x >= min( a.x , b.x ) &&
           po.x <= max( a.x , b.x ) &&
           po.y >= min( a.y , b.y ) &&
           po.y <= max( a.y , b.y ) &&
           /**< �˴�ע��double Ҫ�ж� eps  */
           dcmp(( po.x - a.x ) * ( b.y - a.y ) - ( po.y - a.y ) * ( b.x - a.x )) == 0 ;
}

/**< ��po�Ƿ��ڼ򵥶����(͹)��  ,��p��Ҫ��graham ���� */
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

/**< �㵽�򵥶���εľ��� */
double Point2Simple( point_t * p ,int n , point_t const&po ){
    if ( PointInSimple( p,n,po ) ) return 0;
    double ans = Point2Segment( p[0],p[1] ,po);
    p[n] = p[0];
    for (int i = 1;i < n ;++i)
        ans = min( ans, Point2Segment( p[i] , p[i+1] ,po) );
    return ans;
}


/**< ����������� ,��p��Ҫ��graham ����*/
int_t PolygonArea(point_t p[], int n)
{
    double area = 0;
    for (int i = 0 ;i < n-1;++i )
        area += cross(p[0] , p[i] , p[i+1] );
    return area / 2.0;
//    if(n < 3) return 0.0;
//    int_t s = p[0].y * (p[n - 1].x - p[1].x);
//    p[n] = p[0];
//    for(int i = 1; i < n; ++ i)
//        s += p[i].y * (p[i - 1].x - p[i + 1].x);
//    return s * 0.5;
}

int_t PolygonSideLength(point_t p[], int n){
    double length = 0;
    for (int i = 0 ;i < n-1;++i ) length += Point2Point(p[i],p[i+1]);
    return length + Point2Point(p[n-1],p[0]);
}
/**< �߶��ཻ */
bool SegmentOnSegment(segment_t const &u,segment_t const &v){
    return max(u.s.x,u.e.x) >= min(v.s.x,v.e.x)
        && max(v.s.x,v.e.x) >= min(u.s.x,u.e.x)
        && max(u.s.y,u.e.y) >= min(v.s.y,v.e.y)
        && max(v.s.y,v.e.y) >= min(u.s.y,u.e.y)
        /**< ���ǽ����Ƕ˵� */
        && cross(v.s,u.e,v.e) * cross(v.s,v.e,u.s) > 0
        && cross(u.s,v.e,u.e) * cross(u.s,u.e,v.s) > 0;
}

/**< A�����B�����¸����󷵻��� */
inline bool isLowLeft(point_t const&A,point_t const&B){
    return A.y < B.y || ( A.y == B.y && A.x < B.x );
}


/**< ���ն���pO�ļ������򣬼�����ȵľ���Զ������ǰ�棬��Ϊ����Ҫ��һ��unique */
point_t* pO;
bool comp4Graham(point_t const&A,point_t const&B){
    int_t t = cross(*pO,A,B);
    if ( t ) return t > 0LL;

    int_t a1 = A.x > pO->x ? A.x - pO->x : pO->x - A.x;
    int_t a2 = B.x > pO->x ? B.x - pO->x : pO->x - B.x;
//    if ( a1 != a2 ) return a1 > a2;
    if ( a1 != a2 ) return a1 < a2; //�������ɽ��ķ�ǰ�� ( ���ϸ�͹�� )
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
//    p = unique(P+1,P+n,isEqPolar);
//    n = p - P;

    //������Grahamѭ��
    int top = 2;
    for(int i=2;i<n;++i){
        /**< ���ϸ� ���<= Ҫ�ĳ� <  */
        while( top > 1 && cross(P[top-2],P[top-1],P[i]) < 0LL )
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

/**< ֱ����ֱ�ߵĽ��� */
point_t lineCrossline(point_t a,vector_t v,point_t c,vector_t w)
{
    point_t  p0(0,0);
    vector_t u = a-c;
    int_t t = cross( p0,w,u ) / cross( p0,v,w );
    return point_t( a.x + v.x*t, a.y + v.y*t );
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
                tmp[tn++] = lineCrossline(a[i], a[i + 1], p[j], p[j + 1]); ///�󽻵�
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

/// - - - - - - - - - - - - - - - - - - Code line - - - - - - - - - - - - - - - - - - - - - - - ///

int n;

const int SIZE = 500;
point_t p[SIZE];
point_t pd[SIZE];
segment_t sg[SIZE];
int main(){
	int kase = 1;
	while( scanf("%d",&n) != EOF ){
        for (int i=0;i<n;++i ){
            scanf("%lf%lf%lf%lf",&sg[i].s.x,
                                 &sg[i].s.y,
                                 &sg[i].e.x,
                                 &sg[i].e.y);
        }
        int cnt = 0;
        for(int i=0;i<n;++i){
            p[cnt].x = sg[i].s.x;
            p[cnt++].y = sg[i].s.y;
            p[cnt].x = sg[i].e.x;
            p[cnt++].y = sg[i].e.y;
        }
        point_t target;
        scanf("%lf%lf",&target.x,&target.y);
        for (int i=0;i<n;++i ){
            if ( PointOnSegment(sg[i].s,sg[i].e,target) ) while(1);
        }
//        p[n++] = point_t(0,0);
//        p[n++] = point_t(0,100);
//        p[n++] = point_t(100,0);
//        p[n++] = point_t(100,100);
//        int tmp = Graham(p,cnt);
//        assert(tmp == cnt);

//        p[cnt] = p[0];
        int ans = INT_MAX;
        for (int i = 0 ; i < cnt ;++i ){
//            point_t mid = SegmentMid( p[i],p[i+1] );
            if ( p[i] == point_t(0,0)||
                 p[i] == point_t(0,100)||
                 p[i] == point_t(100,0)||
                 p[i] ==  point_t(100,100)
                ) continue;
            int c = 0;
            for (int j = 0 ;j < n;++j )
                if( SegmentOnSegment( segment_t(p[i],target),sg[j] ) ) c++;
            ans = min(ans,c);
        }
        if ( n == 0 ) ans = 0;
        printf("Number of doors = %d\n",ans+1);
	}
	return 0;
}
/*
    ios.sync_with_stdio(false);  /// ��ôcin, �Ͳ��ܸ�C�� scanf��sscanf, getchar, fgets֮���һ��ʹ���ˡ�
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/


