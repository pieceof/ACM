/** Ford-Fulkerson
 *  增广路算法的效率
    设n = |V|,  m = |E|
    每次增广都是一次BFS,效率为O(m),而在最坏的情况下需要（n-2增广。
    （即除源点和汇点外其他点都没有连通，所有点都只和s与t连通）
    所以,总共的时间复杂度为O(m*n)，所以在稀疏图中效率还是比较高的。
 *
 */


#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
// 按位截取位 x的第startbit 位开始的len长的位数
#define InterceptBit(x,startbit,len)  (((x)<<(31-(startbit)))>>(31-(len-1)))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;

using namespace std;

const int SIZE_V = 100000;
const int SIZE_E = 100000;
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
bool vis[SIZE_V];

int dfs( int u,int t ,int min_c ){
    if ( t == u ) return min_c;
    vis[u] = 1;
    for ( edge_t*p = Ver[u] ; p ; p = p->next ){
        int v = p->node;
        if ( vis[v] || p->c <= 0 ) continue;

        int ret = dfs( v, t ,min(min_c,p->c) );
        if ( ret <= 0 )continue;
        p->c -= ret;
        p->redge->c += ret;
        return ret;
    }
    return 0;
}
int N,M;
void solve( ){
    int ans = 0;
    while( 1 ){
        CLEAR(vis);
        int f = dfs(1,M,INT_MAX);
        if ( f <= 0 ) break;
        ans += f;
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
