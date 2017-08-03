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
const int SIZE = 1150;
char chess[SIZE][SIZE];
int cost[30];
int t,m,k,h;
int x,y;

//inline int Dist( int a,int b ){
//    return min( min( a,abs(a-h)), min(b,abs(b-k)) );
//}
inline int isout( int a,int b ){
    return a <= 0 || b <= 0 || b > k || a > h ;
}
bool vis[SIZE][SIZE];
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};
struct _t{
    int x,y;
    int cost;
    _t( int xx ,int yy, int cc ){
        x = xx;
        y = yy;
        cost = cc;
    }
    friend bool operator < ( const _t&a,const _t&b) {
        return a.cost > b.cost ;
    }
};
//int dist[SIZE][SIZE];
int mincost ;


void bfs( ){
    priority_queue<_t > que;
    que.push( _t( x,y,0 ) );
    int tx ,ty ,tc;
    //dist[x][y] = 0;
    //vis[x][y] = 1;
    while ( !que.empty() ){
        _t tmp = que.top();
        que.pop();
        if ( vis[tmp.x][tmp.y] ){
            continue;
        }
        vis[tmp.x][tmp.y] = 1;
        for (int i = 0;i < 4;++i ){
            tx = tmp.x + dx[i];
            ty = tmp.y + dy[i];

            tc = tmp.cost + cost[chess[tx][ty]-'A'] ;
            if ( isout( tx, ty ) ){

                cout <<tmp.cost<<endl;

                return;
            }
            if ( vis[tx][ty] == 0 ){
                //dist[tx][ty] = tc;
                que.push( _t(tx,ty,tc) );
                //vis[tx][ty] = 1;
                continue;
            }
        }
    }
}
int main(){
//freopen("Escape.in", "r", stdin);
//freopen("out", "w", stdout);

    int t;
    memset( cost,0,sizeof(cost));
    scanf("%d",&t);
    //cout<<t--<<endl;
    while( t-- ){
        //cout <<t<<endl;
        scanf("%d%d%d",&m,&k,&h);

        char ch[2];
        int c;
        for  (int i = 0;i < m;++i ){
            scanf("%s%d",ch,&c);
            cost[*ch-'A'] = c;
        }
        for (int i = 1; i <= h;++i ){
            scanf("%s",chess[i]+1);
            //printf("%s\n",chess[i]+1);
        }
        bool flag = 0;
        for (int i = 1; i <= h;++i  ){
            if ( flag ) break;
            for (int j = 1; j <= k;++ j){
                if ( chess[i][j] == 'E' ){
                    flag = 1;
                    x = i , y = j ;
                    break;
                }
            }
        }
        //cout <<x<<" "<<y<<endl;
        //cout <<Dist(x,y)<<endl;
        //continue;
//        for (int i = 0;i <= h+1;++i ){
//            for (int j = 0;j <= k+1;++j ){
//                dist[i][j] = INT_MAX;
//            }
//        }
        MEM(vis,0);
        //mincost = INT_MAX;
        bfs();


    }


    return 0;

}



