#include <set>
#include <cmath>
#include <cstdio>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d:\n",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
const double eps = 1e-9;
const double PI = acos(-1);
inline double ln(double const&x ){ return log(x)/log(exp(1));}
inline double Vfrustum( double const&r1,double const&r2,double const&h ){
    return PI * h * ( r1*r1 + r2*r2 + r1*r2 )/3;
}
void ArrayCin( int *a ,int n ,int pos = 0){
    for (int i = pos;i < n;++i ) scanf("%d",a+i);
}



int t,n,m,k,kase = 1;
const int SIZE = 6000;

int a[SIZE],b[SIZE],c[SIZE];

set<int> sum;
void TestAndSet( int const&x ){
    if ( sum.count(x) == 0 ) sum.insert(x);
}

bool read( ){
//    if ( t-- == 0 ) return false;
    if ( EOF == scanf("%d%d%d",&n,&m,&k) ) return false;

    ArrayCin(a,n);
    ArrayCin(b,m);
    ArrayCin(c,k);
    sum.clear();
    for (int i = 0;i < n;++i )for (int j = 0;j < m;++j )
        TestAndSet(a[i]+b[j]);
    return true;
}


int main(){
//    scanf("%d",&t);

    while ( read() ){
        Case;
        int s,x;
        scanf("%d",&s);
        while ( s -- ){
            scanf("%d",&x);
            bool isok = 0;
            for (int i = 0;i < k;++i ){
                if ( isok ) break;
                if ( sum.count( x - c[i] ) ) isok = 1;
            }
            if( isok ) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
