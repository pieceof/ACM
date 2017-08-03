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
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <bitset>

//define
#define MOD  1000000007
#define INF 1<<30
#define EPS 1e-13
#define S(r) r*r*PI
#define PI acos(-1.0)
#define UP(i,x,y) for(llt i=x;i<=y;i++)
#define MEM(a,x) memset(a,x,sizeof(a))

using namespace std;
typedef map<int,int>::iterator mii_iter;
typedef map<int,string>::iterator mis_iter;
typedef map<string,string>::iterator mss_iter;
typedef map<int,vector<int> >::iterator mivi_iter;
typedef vector<int>::iterator vi_iter;
typedef vector<string>::iterator vs_iter;
typedef string::iterator s_iter;
typedef long long llt ;
/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/
const int SIZE = 1050;


int dp[SIZE][SIZE] ;
int num[SIZE];
int dfs( int l,int r ){

    if ( l > r ) return 0;
    int best = INT_MIN;

    int val = num[l];
    val -= dfs(l+1,r);
    best = max(best,val);

    val = num[r];
    val -= dfs(l,r-1);
    best = max(best,val);
    return best;
}

int main(){
    int t;
    scanf("%d",&t);
    while( t-- ){
        int n;
        scanf("%d",&n);
        int sum = 0;
        for (int i = 1;i <= n;++i ){
            scanf("%d",num+i);
            sum += num[i];
        }
        int ans = dfs( 1,n );
        printf("%d\n",(ans+sum)/2);
    }

    return 0;
}

