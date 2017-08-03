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

const int SIZE  = 110;
int graph[SIZE][SIZE];
int n,k,m;
bool vis[SIZE];

int minc = 0;
void dfs ( int s ,int e ,int cnt ,int now){
    vis[s] = 1;
    for (int i = 0;i < n;++i ){

        if ( vis[i] || graph[s][i] == 0 ) continue;
        if ( i == e ){
            minc = max(minc,now);
            continue;
        }
        //充电
        {
            if ( cnt == 0 )
                continue;
            minc = max(minc,now);
            dfs(i,e,cnt-1,0);
        }
        //不充电
        {
            minc = max(minc,now+graph[s][i]);
            dfs(i,e,cnt,now+graph[s][i]);
        }
    }
}

int  solve( int s,int e ){
    int ret = INT_MAX;
    memset( vis,0,sizeof(vis) );
    vis[s] = 1;
    for (int i = 0;i < n;++i ){
        if ( graph[i][s] && i != s ){
            if ( e == i ) {
                ret = min(ret,graph[i][s]);
                continue;
            }
            minc = 0;
            memset( vis,0,sizeof(vis) );
            vis[s] = 1;
            dfs(i,e,k,graph[i][s]);
            ret = min(ret,minc);
        }
    }

    return ret;
}

int main(){
    freopen("in.in", "r", stdin);
    int t;
    scanf("%d",&t);
    while ( t-- ){

        scanf("%d%d%d",&n,&k,&m) ;
        int a,b,c;
        memset(graph,0,sizeof(graph));
        for (int i = 0;i < m;++i ){
            scanf("%d%d%d",&a,&b,&c);
            graph[a][b] = graph[b][a] = c;
        }
        int ans = 0;
        for (int i = 0;i < n;++i){
            for (int j = i+1;j < n;++j){
                ans = max( ans ,solve(i,j));
            }
        }
        printf("%d\n",ans);

    }


    return 0;
}
