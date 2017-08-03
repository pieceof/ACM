#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
#include <stdlib.h>
//stl
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <bitset>
//unused
#include <complex>
#include <functional>
#include <fstream>
#include <ctime>
#include <stdexcept>
//define
#define MOD  1000000007
#define INF 1<<30
#define EPS 1e-13
#define S(r) r*r*PI
#define PI acos(-1.0)
#define UP(i,x,y) for(int i=x;i<=y;i++)
#define MEM(a,x) memset(a,x,sizeof(a))

int gcd(int a,int b){  return b==0?a:gcd(b,a%b); }
typedef long long llt ;



//cout.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
//freopen("cin.txt", "r", stdin);
//freopen("cout.txt", "w", stdout);
using namespace std;
typedef long long llt;

//int ST[4000010];

struct point_t{
    int x,y;
    point_t( int xx= 0,int yy=0):x(xx),y(yy){}
};

double incross( point_t const&a,point_t const&b){
    //cout <<a.x*b.x-a.y*b.y<<endl;
    return (double)(a.x*b.x+a.y*b.y)/(sqrt(a.x*a.x+a.y*a.y)*sqrt(b.x*b.x+b.y*b.y));
}
int outcross(point_t const &O,point_t const &A,point_t const &B){
    int xOA = A.x - O.x;
    int yOA = A.y - O.y;
    int xOB = B.x - O.x;
    int yOB = B.y - O.y;
    return xOA * yOB - xOB * yOA;
}


int main(){
    int r,n;
    scanf("%d",&n);
    while( n-- ){
        int a,b,c,d,e,f;
        scanf("%d%d%d%d%d%d%d",&r,&a,&b,&c,&d,&e,&f);
        point_t p0(0,0),pa(a,b),pb(c,d),pc(e,f);
        if ( a*a+b*b == 0 || c*c+d*d == 0 || e*e+f*f == 0){
            puts("No");
            //while(1);
            continue;
        }
        double t1 = incross( pa,pb );
        double t2 = incross( pa,pc );
        double t3 = incross( pb,pc );
        double tt1 = outcross(p0,pa,pb);
        double tt2 = outcross(p0,pa,pc);
        bool flag = 0;
        if ( outcross(p0,pa,pb) > 0 ){
            if ( incross(pa,pb) >= -0.5 )
                if ( incross(pa,pc) < -0.5 )
                    flag = 1;
        }
        if ( outcross(p0,pa,pc) > 0 ){
            if ( incross(pa,pc) >= -0.5 )
                if ( incross(pa,pb) < -0.5 )
                    flag = 1;
        }
        if ( outcross(p0,pb,pa) > 0 ){
            if ( incross(pb,pa) >= -0.5 )
                if ( incross(pb,pc) < -0.5 )
                    flag = 1;
        }
        if ( outcross(p0,pb,pc) > 0 ){
            if ( incross(pb,pc) >= -0.5 )
                if ( incross(pb,pa) < -0.5 )
                    flag = 1;
        }
        if ( outcross(p0,pc,pb) > 0 ){
            if ( incross(pc,pb) >= -0.5 )
                if ( incross(pc,pa) < -0.5 )
                    flag = 1;
        }
        if ( outcross(p0,pc,pa) > 0 ){
            if ( incross(pc,pa) >= -0.5 )
                if ( incross(pc,pb) < -0.5 )
                    flag = 1;
        }
        if (flag)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
