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

llt dfs( llt nub ,llt w, int isfirst){
    if ( nub == 0 & w == 0 )
        return 1;
    if ( nub < 0 || nub >= w*20)
        return 0;
    if  ( w == 1 )
        return (nub&1) == 0 ;
    llt left = nub%10;
    llt ret = 0;

    ret += (1-isfirst+left)*( dfs( (nub-w*left-left)/10 , w/100,0));

    left += 10;
    ret += ( 19-left )*(dfs( (nub-w*left-left)/10 , w/100,0));
    return ret;
}

llt solve( llt n ){
    llt ans = 0;
    for (llt w = 1; w <= n+1; w*=10 ){
        ans += dfs(n,w,1);
    }
    return ans;
}

int main(){
//freopen("Holodeck.in", "r", stdin);
//freopen("cout.txt", "w", stdout);
    int t;
    scanf("%d",&t);
    while( t-- ){
        llt n ;
        scanf("%lld",&n);
        if (n < 0 )
            continue;
        printf("%lld\n",solve(n));

    }


    return 0;
}
