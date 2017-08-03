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

const int SIZE = 1000000;
int nub[SIZE];


int main()
{
    int n;
    int t = 1;

    while(scanf("%d",&n) &&n ){

        for (int i = 1;i <= n;++i )
            scanf("%d",nub+i);

        int m = INT_MAX;
        int sum = 0;
        int b;
        for (int i = 1;i <= n;++i ){
            scanf("%d",&b);
            nub[i] -= b;
            sum += nub[i];
            m = min(m,sum);
        }
        printf("Case %d:",t++);

        int ans = m;
        for (int i = 1;i <= n;++i){
            if ( ans >= 0 )printf(" %d",i);
            ans -= nub[i];
        }


        puts("");

    }
}
