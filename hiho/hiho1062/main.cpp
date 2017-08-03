#include <bits/stdc++.h>
//define
#define MOD  1000000007
#define S(r) r*r*PI
#define PI acos(-1.0)
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define InterceptBit(x,startbit,len)  (((x)<<(31-(startbit)))>>(31-(len-1)))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
using namespace std;

class Disjoint_Set
{
public:
    void init(){ Father.clear(); }
    string find(string x){
        if ( Father.count(x) == 0 ){
            Father[x] = x;
            return x;
        }
        return (Father[x] == x) ? x :
             Father[x] = find(Father[x]);
    }
    void unite(string x,string y){Father[find(y)] = find(x) ;}
    map<string ,string > Father;
private :

};

map< string, vector< string > > Graph;
void init_Graph( ){ Graph.clear(); }
void mkEdge( string a,string b){ Graph[a].push_back(b); }

const int LOG = 20;

map<string,int> dep;
map<string,vector<string> > fa;


void dfs( string father,string u,int depth ){
    dep[u] = depth;
    fa[u].push_back(father);
    for ( int i = 1 ; i < LOG;++i )
        fa[u].push_back(fa[fa[u][i-1]][i-1]);
    for ( auto v : Graph[u] )
        dfs(u , v , depth+1);
}

string up(string u,int d){
    for (int i = 0;i < LOG;++i )
        if ( d&(1<<i) ) u = fa[u][i];
    return u;
}

string LCA( string u,string v ){
    if ( dep[u] < dep[v] ) swap( u , v );
    u = up(u,dep[u]-dep[v] );
    if ( u == v ) return u;
    for (int i = LOG-1;i >= 0;--i ){
        if ( fa[u][i] == fa[v][i] )continue;
        u = fa[u][i];
        v = fa[v][i];
    }
    return fa[u][0];
}

int n,m;
Disjoint_Set ds;
string a,b,f;
int read( ){
    if ( !(cin>>n) )return false;

    ds.init();
    init_Graph();

    for (int i = 0 ;i < n;++i ){
        cin>>a>>b;
        ds.unite(a,b);
        mkEdge(a,b);
    }
    return true;
}
void init_lca( ){
    for ( int i = 0 ; i < LOG;++i ) fa[f].push_back(f);
    for ( auto tmp : Graph[f] ) dfs(f,tmp,2);
}

void solve(){
    cin>>m;
    while ( m-- ){
        cin>>a>>b;
        if ( ds.find(a) != ds.find(b) ) {
            cout << "-1" <<endl;
        }else{
            f = ds.find(a);
            init_lca();
            f = LCA(a,b);
            cout << f << endl;
        }
    }
}
int main(){
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while ( read() )solve();
    return 0;
}

