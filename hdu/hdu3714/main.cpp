#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
const double eps = 1e-9;
inline double ln(double const&x ){ return log(x)/log(exp(1));}
//inline double f( double const&x ){return x/ln(x);}



int t,n;
double l,r;
const int SIZE = 11000;
double a[SIZE],b[SIZE],c[SIZE];
inline double f( double const & x ,int i){
    return a[i] * x * x + b[i] * x + c[i];
}
double S( double const &x ){
//    double ret = -1e99;
    double ret = f(x,0);
    for ( int i = 1;i < n;++i ) ret = max(ret,f(x,i));
    return ret;
}

bool read( ){
    if ( t-- == 0 ) return 0;
    scanf("%d",&n);
    for (int i = 0;i < n;++i )
        scanf("%lf%lf%lf",a+i,b+i,c+i);
    return 1;
}

int main(){
    scanf("%d",&t);
//    test_fx();
    while ( read() ){
        l = 0, r = 1000;
        while ( r-l > eps ){
            double m1 = l + (r-l)/3;
            double m2 = r - (r-l)/3;
            if ( S(m1) < S(m2) ) r = m2;
            else l = m1;
        }
        printf("%.4f\n",S(l));
    }
    return 0;
}
