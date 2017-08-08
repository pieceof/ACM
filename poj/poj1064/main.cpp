#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;

const int SIZE = 11000;
double cable[SIZE];
int check ( double len ,int n ,int k){
    int cnt = 0;
    for (int i = 0;i < n;++i ){
        cnt += floor(cable[i] / len);
    }
    if ( cnt < k ) return -1;
    if ( cnt == k ) return 0;
    return 1;
}

int main(){
    int n,k;
    while ( scanf("%d%d",&n,&k) != EOF ){
        double l=0,r=0;
        for( int i = 0 ;i < n;++i ){
            scanf("%lf",cable+i);
            r = max(r,cable[i]);
        }
        double const eps = 0.00001;
        while ( (r - l) > eps ){
            double mid = (r+l)/2.0;
            if ( check(mid,n,k) >= 0 ) l = mid;
            else r = mid;
        }
//        deBug(r);
        if((int)(r*1000)%10 >=5) r-=0.005;//因为要用浮点数输出 所以 如果是 0.005 的话会输出0.01！！！！！！一定要注意
//        deBug(r);
        printf("%.2f\n",(double)r);
    }
    return 0;
}
/*
4 3
8.02
7.43
4.57
5.39

>5.39

4 2540
8.02
7.43
4.57
5.39

>0.01

4 2542
8.02
7.43
4.57
5.39

>0.00


4 1
8.02
7.43
4.57
5.39

>8.02


1 1 1

>1
*/
