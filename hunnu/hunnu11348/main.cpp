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

const int SIZE = 510;
int isJust[SIZE]; // 1 is ok . 0 is no
int Graph[SIZE][SIZE];
bool just( int i ,int n){
    isJust[i] = 1;
    bool ret = 1;
    for (int j = 1;j <= n;++j ){
        if (i == j ) continue;

        if ( Graph[i][j] ) {
            if ( isJust[j] == 1) return 0;
            Graph[j][i] = 0;
            //isJust[j] = 1;
            if ( 0 == just(j,n) )
                ret = 0;
        }
    }
    return ret;
}
int solve( int n  ){
    int cnt = 0;
    for (int i = 1;i <= n;++i ){
        if ( isJust[i] == 1 ) continue;
        if ( just( i , n )  ) {
            cnt++;
        }

    }
    return cnt;
}

void init(){
    memset(isJust,-1,sizeof(isJust));
    memset(Graph,0,sizeof(Graph));
    //memset()
}
int main()
{
//freopen("trees.in", "r", stdin);
//freopen("trees.out", "w", stdout);
    int n,m;
    int t = 1;
    while( scanf("%d%d",&n,&m) && ( n+m != 0 ) ){
        init();
        int a,b;
        for (int i = 0;i < m;++i ){
            scanf("%d%d",&a,&b);
            Graph[a][b] = Graph[b][a] = 1;
        }
        int ans = solve( n);

        if ( ans == 1 ){
            printf("Case %d: There is one tree.\n",t++);
        }else if ( ans > 1){
            printf("Case %d: A forest of %d trees.\n",t++,ans);
        }else
            printf("Case %d: No trees.\n",t++,ans);

    }
    return 0;
}
