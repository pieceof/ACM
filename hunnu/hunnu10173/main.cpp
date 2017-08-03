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

using namespace std;
const int SIZE = 100;
int c[SIZE];
int like[SIZE];
int m;
double cost(int n ,double nowCost , double nowgai,int arri){

    double ret = 0;

    for (int i = 0;i < n;++i){

        double tmp = ( nowCost+c[i] )  * ((1.0/n)*nowgai);
        if ( tmp < 0.00001 ) continue;
        if ( like[i] == 1 ){
            if ( arri+1 == m){
                ret += tmp;
                // cout <<"tmp:" << tmp<<endl;
                continue;
            }
            like[i] = 2;
            ret += cost(n,nowCost+c[i] , nowgai*(1.0/n),arri+1);
            like[i] = 1;
            continue;
        }
        ret += cost(n,nowCost+c[i] , nowgai*(1.0/n),arri);


    }
    return ret;
}

int main()
{
//freopen("cin.txt", "r", stdin);
//freopen("cout.txt", "w", stdout);
    int n;
    while( scanf("%d",&n) &&n ){
        for ( int i = 0;i < n;++ i){
            scanf("%d",c+i);
        }
        int r;
        scanf("%d",&r);
        while ( r-- ){
            double ans = 0;
            int b;
            scanf("%d",&m);
            memset(like,0,sizeof(like));
            for (int i = 0;i < m;++i ){
                scanf("%d",&b);
                like[b-1] = 1 ;
            }
            ans = cost(n,0,1,0);
            printf("%.2lf\n",ans);
        }

    }

    return 0;
}
