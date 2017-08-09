#include <cstdio>
#include <set>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <climits>
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
void ArrayDisp(int *a,int n ){
    cout << varName(a) << "  : ";
    for (int i = 0;i < n;++i )printf("%4d ",a[i]);printf("\n");
}

/// ------------------------------ code line ------------------------------//


const int SIZE = 60000;
int rock[SIZE];
int t,n,m,L,kase = 1;
int l,r;

bool check( int length ,int cnt ){
    for (int i = 0;i < n-1;){
        int j = i+1;
        while( j < n && rock[j] - rock[i] <= length )j++;
        cnt -= j-i-1;
        if ( j == n ) cnt--;
        if ( cnt < 0 )return 0;
        i = j;
    }
    return true;
}
int biniSearh(){
    l = 0 ,r = L;
    while ( l < r ){
        int mid = l + ( r - l) / 2 ;
        if ( check(mid,m) ) l = mid+1;
        else r = mid;
    }
//    deBug(l);deBug(r);
    return l;
}


bool read( ){
//    if ( t-- == 0 ) return false;
    if ( EOF == scanf("%d%d%d",&L,&n,&m) ) return false;
    ArrayCin(rock,n+1,1); n++;
    rock[0] = 0 , rock[n++] = L;
    return true;
}
int main(){
//    scanf("%d",&t);

    while ( read() ){
        sort( rock,rock + n );
        Ans(biniSearh());
    }
    return 0;
}
