/**
 *  LCA -> RMQ
 *  下标从 1 开始
 *  初始化 & depth = 1
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#define clear(a) memset((a),0,sizeof(a) )
#define FLAG(a) memset((a) , -1, sizeof(a))
using namespace std;
typedef long long llt;

const int SIZE_V = 100000;
const int SIZE_E = 100000;
struct edge_t{
    int node;
    int k;
    edge_t* next;
    edge_t( int nn = 0 ,int kk = 0,edge_t *ne = 0 ): node(nn),k(kk),next(ne) {};
}Edge[SIZE_E];

edge_t* Ver[SIZE_V];
int toUsed ;

void mkEdge( int a,int b,int k = 0){
    Edge[toUsed] = edge_t(a,k,Ver[b]);
    Ver[b] = Edge + toUsed++;

    Edge[toUsed] = edge_t(b,k,Ver[a]);
    Ver[a] = Edge + toUsed++;
}
int dep[SIZE_V];

int _visIdx[SIZE_V<<2];
int _visDep[SIZE_V<<2];
int _visTime[SIZE_V];
int _totVis;

void init( ){
    // Graph
    toUsed = 0;
    clear(Ver);

    // LCA -> RMQ
    _totVis = 0 ;
    FLAG(_visTime);
}
void dfs( int father,int u,int depth ){
    //if ( u == 1 ) dist[u] = 0;
    ++_totVis;
    _visIdx[_totVis] = u;
    _visDep[_totVis] = depth;
    dep[u] = depth;
    if ( _visTime[u] == -1 ) _visTime[u] = _totVis;

    for ( edge_t*p = Ver[u]; p ; p = p->next) {
        int v = p->node;
        if ( father == v ) continue;

        dfs( u,v,depth+1);
        ++_totVis;
        _visIdx[_totVis] = u;
        _visDep[_totVis] = depth;
    }

}


//int a[SIZE_V]; // 原数组
int RMQ[SIZE_V][18]; //预处理数组

void getRMQ( ){
    for (int i = 1;i <= _totVis;++i) RMQ[i][0] = i;
    for (int j = 1;(1<<j) <= _totVis;++j )
        for (int i = 1;i+(1<<j) <= _totVis+1 ;++i ){
            int a = RMQ[i][j-1];
            int b = RMQ[i+(1<<(j-1))][j-1];
            RMQ[i][j] = ( _visDep[a] <= _visDep[b] ) ? RMQ[i][j-1] : RMQ[i+(1<<(j-1))][j-1] ;
        }

}
int querry(int A,int B){
    int k = (int)(log((double)(B+1-A))/log(2.0));
    int a = RMQ[A][k];
    int b = RMQ[B+1-(1<<k)][k];
    return ( _visDep[a] <= _visDep[b] ) ? RMQ[A][k] : RMQ[B+1-(1<<k)][k] ;
}

int LCA( int u,int v ){
    int l = _visTime[u] ;
    int r = _visTime[v] ;
    if ( l > r ) swap(l,r);
    int f = querry(l,r);
    return _visIdx[f];
}


int main()
{
    int t,n,m;
    scanf("%d",&t);
    while ( t-- ){
        init();
        scanf("%d%d",&n,&m);
        int x,y,z;
        for ( int i = 0;i < n-1;++i ){
            scanf("%d%d%d",&x,&y,&z);
            mkEdge(x,y,z);
        }
        dfs(-1,1,1);
        getRMQ();
    }
    return 0;
}
