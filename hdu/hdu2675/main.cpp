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
const double eps = 1e-8;


double l,r;
double y;
bool read( ){
    if ( EOF == scanf("%lf",&y) ) return 0;
    return 1;
}
inline double ln(double const&x ){
    return log(x)/log(exp(1));
}
inline double f( double const&x ){
    return x/ln(x);
}

void test_fx( ){
    for (double i = 1.1;i < exp(1); i += 0.01 ){
        deBug( f(i) );
    }
}
int main(){

//    test_fx();
    while ( read() ){

        if ( fabs(y-1) < eps ) {
            printf("%.5f\n",exp(1));
            continue;
        }
        double ans2 = exp(1)*y;
        l = 1+eps , r = exp(1);
        y = f(exp(1)*y);
        while ( r-l > eps ){
            double mid = (r+l)/2;
            if ( f(mid) < y ) r = mid;
            else l = mid;
        }
        printf("%.5f %.5f\n",l,ans2);
    }
    return 0;
}
