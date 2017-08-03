#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;
using namespace std;

/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/

const int SIZE = 30;

int Graph[SIZE][SIZE];
int Graph2[SIZE][SIZE];

vector<string> str_cache;
map<string,int> str_id;
int str_cnt = INT_MAX;
int get_str_id ( string const&a ){
    if ( str_id.count(a) )return str_id[a];
    str_cache.push_back(a);
    return str_id[a] = str_cnt++;
}

void init( int n ){
    str_cache.clear();
    str_id.clear();
    str_cnt = 0;
//    for (int i = 1;i <= n;++i ){
//        for (int j = 1;j <= n;++j ){
//            Graph[i][j] = 0;
//        }
//    }
    CLEAR(Graph);
    CLEAR(Graph2);
}

void floyd( int n ){
    for ( int k = 1;k <= n;++k ){
        for ( int i = 1;i <= n;++i ){
            for ( int j = 1;j <= n;++j ){
                Graph[i][j] = Graph[i][j] || ( Graph[i][k] && Graph[k][j]);
            }
        }
    }

}
string str;


int Father[SIZE];

void _init_set( int n ){
    for (int i = 0;i <= n;++i ) Father[i] = i;
}

int _find( int x ){
    return Father[x] == x ? x :  Father[x] = _find(Father[x]);
}
inline void _unite(int x,int y){
    Father[_find(y)] = Father[_find(x)];
}

bool vis[SIZE];
void dfs( int u ,int n ){
//    if ( s == u ) return;
    if ( u > n ) return;
    for (int v = 1 ;v <= n ;++v ){
//        if ( f == v ) continue;
//        if ( u == v ) continue;
        if ( vis[v] ) continue;
        if ( Graph2[u][v] == 0 ) continue;
        vis[v] = 1;
//        deBug(v);
        cout << ", " << str_cache[v-1];
        dfs( v,n );
    }
}
int main()
{
//    freopen("cout.txt", "w", stdout);
    ios::sync_with_stdio(false);
    int n,m;
    int kase = 1;
    while ( cin>>n>>m ){
        if ( n == 0 && m == 0 ) break;

        int a,b;
        init(n);
        for (int i = 0 ; i < m;++i ){
            cin>>str;
            a = get_str_id(str);
            cin>>str;
            b = get_str_id(str);
            if ( a == b ) continue;
            Graph[a+1][b+1] = 1;
        }
        n = str_cnt;
        floyd( n );
        _init_set(n);
        for (int i = 1;i <= n;++i ){
            for ( int j = 1;j <= n;++j ){
                if ( i != j && Graph[i][j] == Graph[j][i] && Graph[i][j] == 1 ) {
                    Graph2[i][j] = Graph2[j][i] = 1;
                }
            }
        }
//        for (int i = 1;i <= n;++i ){
//            deBug( _find(i) );
//            deBug( str_cache[_find(i)-1] );
//        }
        CLEAR(vis);
        if ( kase > 1 )
            cout << endl;
        cout << "Calling circles for data set " << kase++ << ":" << endl;
        for ( int i = 1, j;i <= n;++i ){
            if (vis[i]) continue;
//            deBug(i);
            cout << str_cache[i-1];
            j = i+1;
            vis[i] = 1;
            while ( j<=n&&(vis[j] || Graph2[i][j] == 0) )j++;
            dfs(j,n);
            cout << endl;
        }
    }

    return 0;
}
