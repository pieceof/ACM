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




const int SIZE = 100050;
int mini,minNode;
int d[SIZE];
typedef int  weight_t;
struct edge_t{
	int node;
	weight_t w;
	edge_t* next;
}Edge[SIZE*2];
int ECnt = 0;

//图的邻接表
edge_t* Ver[SIZE];

//初始化
inline void init(int n ){
    //MEM(d,0);
    mini = 0;
    minNode = INT_MAX;
	ECnt = 0;
	//MEM(Ver,0);
	fill(Ver,Ver+n+1,(edge_t*)0);
}
//生成双向边
inline void mkEdge(int a,int b,weight_t w){
	Edge[ECnt].node = b;
	Edge[ECnt].w = w;
	Edge[ECnt].next = Ver[a];
	Ver[a] = Edge + ECnt ++;

	Edge[ECnt].node = a;
	Edge[ECnt].w = w;
	Edge[ECnt].next = Ver[b];
	Ver[b] = Edge + ECnt ++;
}



void dfs( int node,int father,int n){
    d[node] = 1;
    int maxnode = 0;
    for ( edge_t*p = Ver[node];p;p = p->next ){
        int next = p->node;
        if  ( next == father ) continue ;
        dfs(next,node,n);
        d[node] += d[next];
        maxnode = max(maxnode , d[next]);

    }
    maxnode = max(maxnode , n-d[node]);
    if ( maxnode < minNode ){
        minNode = maxnode;
        mini = node;
    }
}


llt ans = 0;
void Cnt( int node ,int father ,int n ,int nowcost ){
    for ( edge_t*p = Ver[node];p;p = p->next ){
        int next = p->node;
        if(next != father ){
            ans += (nowcost + p->w)*2;
            Cnt( next , node, n,nowcost + p->w);
        }
    }
}

int main(){
    int t;
    int k = 1;
    scanf("%d",&t);
    while( t-- ){
        int n ,a,b ,c;
        scanf("%d",&n);
        init(n);
        for ( int i = 1;i < n ;++i ){
            scanf("%d%d%d",&a,&b,&c);
            mkEdge(a,b,c);
        }
        dfs(1,0,n);
        //printf("%d %d\n",mini,minNode);
        //dfs(mini,0,n);
        ans = 0;
        Cnt(mini,0,n,0);

        printf("Case #%d: %I64d\n",k++,ans);


    }

    return 0;
}

