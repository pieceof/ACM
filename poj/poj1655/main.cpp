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
const int SIZE = 20500;

vector<int>tree[SIZE];
int d[SIZE];

int minNode;
int mini;
void init(int n){
    MEM(d,0);
    for (int i = 0 ;i <= n ;++i )
        tree[i].clear();
    minNode = INT_MAX;
    mini = 0;
}

void dfs( int i ,int parent ,int n ){
    d[i] = 1;
    int maxnode = 0;
    for ( vi_iter it = tree[i].begin() ;it !=  tree[i].end();++it){
        if ( *it == parent ) continue;
        dfs( *it ,i , n);
        d[i] += d[*it];
        maxnode = max(maxnode , d[*it]);

    }

    maxnode = max( maxnode , n-d[i] );

    if ( minNode > maxnode ) {
        minNode = maxnode ;
        mini = i;
    }
}


int main(){
    int n,t;
    scanf("%d",&t);
    while( t-- ){
        scanf("%d",&n);
        int a,b;

        init( n );
        for ( int i = 1; i < n ;++i ){
            scanf("%d%d",&a,&b);
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
        dfs(1,0,n);
        printf("%d %d\n",mini,minNode);
    }

    return 0;
}

