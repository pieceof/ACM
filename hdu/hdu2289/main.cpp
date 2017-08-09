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
const double PI = acos(-1);
inline double ln(double const&x ){ return log(x)/log(exp(1));}
inline double Vfrustum( double const&r1,double const&r2,double const&h ){
    return PI * h * ( r1*r1 + r2*r2 + r1*r2 )/3;
}




int t,n;

double top_r,bot_r,H,V;
double l,r;
const int SIZE = 11000;

inline double Get_Volume( double const&h ){
//    double z = H/(top_r-bot_r);
//    double r0 = bot_r / z * (h+z) ;
    double r0 = h/H*(top_r-bot_r) + bot_r;/*中部小圆台上底半径,根据比例可以求*/
    return Vfrustum(r0,bot_r,h);
}

bool read( ){
    if ( t-- == 0 ) return false;
    scanf("%lf%lf%lf%lf",&bot_r,&top_r,&H,&V);
    return true;
}

int main(){
//    printf("%.9f\n",acos(-1));
//    deBug(acos(-1));
    scanf("%d",&t);

//    test_fx();
    while ( read() ){
        l = 0, r = H;
        while ( r-l > eps ){
            double mid = (l+r)/2;
            if ( Get_Volume(mid) > V ) r = mid;
            else l = mid;
        }
//        printf("%.6f\n",l);
        printf("%.6f\n",r);
    }
    return 0;
}
