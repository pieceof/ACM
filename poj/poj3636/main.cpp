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
const int SIZE = 105000;
/*最长不上升子序列 POJ 1887*/

/*预处理*/

const int INF = 0x3f3f3f3f;

int n;
int A[SIZE], S[SIZE];
int d[SIZE];

int BSearch(int x, int y, int v)
{
    while(x <= y)
    {
        int mid = x+(y-x)/2;
        if(S[mid] >= v) x = mid+1; //注意看二分的变化
        else y = mid-1;
    }
    return x;
}

void dp( int n )
{
    for(int i = 1; i <= n; i++) S[i] = -INF; //注意初始值
    memset(d, 0, sizeof(d));
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        int x = 1, y = i;
        int pos = BSearch(x, y, A[i]);
        d[i] = pos;
        S[d[i]] = max(S[d[i]], A[i]); //max
        ans = max(ans, d[i]);
    }
    printf("%d\n", ans);
}


struct _t{
    int x,y;
    friend bool operator < ( const _t&a,const _t&b){
        return (a.x == b.x && a.y > b.y ) ||
            a.x < b.x ;
    }
} node[SIZE];
int main(){
    int t;
    scanf("%d",&t);
    while ( t-- ){

        int n;
        scanf("%d",&n);
        for (int i = 0; i < n ;++i ){
            scanf("%d%d",&node[i].x,&node[i].y);
        }

        sort( node,node+n);
        for (int i = 0;i < n;++i ){
            A[i+1] = node[i].y;
            //cout << A[i+1] << " ";
        }
        //cout <<endl;
        dp(n);
    }



}
