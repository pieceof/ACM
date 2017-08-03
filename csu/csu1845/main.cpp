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
const int V_SIZE = 360;
const int E_SIZE = V_SIZE*V_SIZE/2;
int Father[V_SIZE];
map < int , vector< pair<int,int> > > nedge;
int n;
struct edge_t{
    int s,e;
    int v;
    friend bool operator < ( const edge_t&a,const edge_t&b ){
        return a.v < b.v;
    }
}Edge[E_SIZE];

//并查集算法
void init(int vn){
    for(int i = 0;i <= vn;++i)
        Father[i] = i;
}
int find(int x){
    return (Father[x] == x) ? x :
         Father[x] = find(Father[x]);
}
inline void unite(int s,int e,int v){
    Father[find(e)] = Father[find(s)];

}

int minfire ,minstart,minend;
bool vis[V_SIZE];

void Delete ( int s ,int e, int fire ){
    nedge[s].erase( find( nedge[s].begin() ,nedge[s].end() , make_pair(e,fire) ) );
    nedge[e].erase( find( nedge[e].begin() ,nedge[e].end() , make_pair(s,fire) ) );
}
void dfs ( int node, int e ,int mins,int mine,int minf ){
    vis[node] = 1;
    if ( node == e ){
        minfire = minf;
        minstart = mins;
        minend = mine;
        return;
    }
    for ( auto iter : nedge[node] ){
        if ( vis[iter.first] == 1 ) continue;
        //if ( minf > iter.second ) minf = iter.second , mins = node , mine = iter.first;

        //dfs( iter->first , e, mins,mine,minf);
        if ( minf > iter.second)
            dfs( iter.first , e, node, iter.first,iter.second );
        else
            dfs( iter.first , e, mins, mine, minf);

    }
}

int solve( int m  ){
    sort( Edge,Edge+m);
    init(n);
    //vector< pair<int ,int> > r;r.clear();
//    for (int i = 0;i <=n ;++i ){
//        nedge.push_back( make_pair( i ,vector< pair<int ,int> >() ) );
//    }
for (int i = 0;i <= n;++i )nedge[i].clear();
    //nedge.clear();
    int ret = INT_MAX;
    int  s,e,v;
    int cnt = 0;
    multiset<int,less<int> > fair;
    for ( int i = 0;i < m;++i ){
        s = Edge[i].s;
        e = Edge[i].e;
        v = Edge[i].v;
        //cout << " v : " << v <<endl;
        fair.insert(v);
        if ( find(s) != find(e) ){
            unite(s,e,v);
            cnt++;
            nedge[s].push_back( make_pair( e,v ) );
            nedge[e].push_back( make_pair( s,v ) );
            //cout << *fair.begin() << " " << *fair.rbegin() <<endl;
            if ( cnt == n-1)
                ret = min(ret , -*fair.begin() + *fair.rbegin() );
            continue;
        }

        // s , e  make cycle
        MEM(vis,0);
        dfs( s, e, 0, 0, INT_MAX );
        Delete( minstart, minend,minfire );

        fair.erase(fair.find(minfire));

        //for ( auto i : fair )cout <<i<<endl;
        nedge[s].push_back( make_pair( e,v ) );
        nedge[e].push_back( make_pair( s,v ) );
        //cout << *fair.begin() << " " << *fair.rbegin()<<endl;
        if ( cnt == n-1)
            ret = min(ret , -*fair.begin() + *fair.rbegin());
    }
    return ret;
}



int main(){


    while ( scanf( "%d" ,&n ) && n ){
        int m;
        scanf("%d",&m);
        int a,b,c;
        for (int i = 0;i < m ;++i ){
            scanf("%d%d%d",&a,&b,&c);
            Edge[i].s = a;
            Edge[i].e = b;
            Edge[i].v = c;
        }
        int ans = solve( m );
        cout << ans << endl ;

    }
    return 0;
}
