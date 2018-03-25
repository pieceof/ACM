#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
// 按位截取位 x的第startbit 位开始的len长的位数
#define InterceptBit(x,startbit,len)  (((x)<<(31-(startbit)))>>(31-(len-1)))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;

using namespace std;

const int SIZE_V = 300;
const int SIZE_E = 40000;
struct edge_t{
    int node;
    int c;
    edge_t* next;
    edge_t* redge;
}Edge[SIZE_E];

edge_t* Ver[SIZE_V];
int toUsed ;
void init( ){
    toUsed = 0;
    CLEAR(Ver);
}
void mkEdge( int a,int b,int c ){
    Edge[toUsed] = (edge_t){b,c,Ver[a],Edge+toUsed+1 };
    Ver[a] = Edge + toUsed++;

    Edge[toUsed] = (edge_t){a,0,Ver[b],Edge+toUsed-1 };
    Ver[b] = Edge + toUsed++;
}
int layer[SIZE_V];

int bfs(int s,int t){
    FLAG(layer);
    layer[s] = 0;
    queue<int>que;
    que.push(s);
    while ( !que.empty() ){
        int u = que.front();
        que.pop();
        for ( edge_t* p = Ver[u]; p ; p = p->next){
            int v = p->node;
            if ( layer[v] != -1 || p->c <= 0 ) continue;
            que.push( v );
            layer[v] = layer[u] + 1;
        }
    }
    if ( layer[t] == -1 ) return 0;
}
int dfs( int u ,int t, int cf ){
    if ( u == t ) return cf;
    int ret = 0 ;
    for ( edge_t* p = Ver[u] ; p ; p=p->next ){
        int v = p->node;
        if ( ret >= cf ) return ret;
        if ( p->c <= 0 || layer[u]+1 != layer[v] ) continue;

        int f = dfs( v,t,min(p->c,cf-ret));
        p->c -= f;
        p->redge->c += f;
        ret += f;
    }
    if ( ret == 0 ) layer[u] = -1;
    return ret;
}
int N,M;
void solve( ){
    int ans = 0;
    while ( bfs( 1, M ) ) {
        int tmp;
        while ( tmp = dfs( 1, M, INT_MAX ))
            ans += tmp ;
    }
    printf("%d\n",ans);
}

int main()
{
    while( EOF != scanf("%d%d",&N,&M) ){
        init();
        for(int i=0;i<N;++i){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            mkEdge(a,b,c);
        }
        solve();
    }

    return 0;
}
