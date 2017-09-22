#include <cstdio>
#include <climits>
#include <queue>
#include <algorithm>
using namespace std;

typedef int weight_t;

#define SIZE 2005

int N,M;
int S,T;

//边的结构
struct edge_t{
	int node;
	weight_t w;
	edge_t* next;
}Edge[SIZE];
int ECnt = 0;

//图的邻接表
edge_t* Ver[202];

//初始化
inline void init(){
	ECnt = 0;
	fill(Ver,Ver+N,(edge_t*)0);
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

//最短路径的结果
weight_t D[202];

//标志位
bool Flag[202];

//spfa算法，输入保证没有负环，s为源
void spfa(int s){
	//初始化
	fill(D,D+N,INT_MAX);
	fill(Flag,Flag+N,false);

	//初始化源
	D[s] = 0;
	Flag[s] = true;

	//队列
	queue<int> q;
	q.push(s);

	while( !q.empty() ){
		int u = q.front();
		q.pop();
		Flag[u] = false;

		//对u的每一条边
		for(edge_t*p=Ver[u];p;p=p->next){
			int v = p->node;
			weight_t tmp = D[u] + p->w;
			if ( D[v] > tmp ){
				D[v] = tmp;
				if ( !Flag[v] )
					Flag[v] = true, q.push(v);
			}
		}
	}

	return;
}

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) )
		return false;

	init();
	for(int i=0;i<M;++i){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		mkEdge(a,b,w);
	}
	scanf("%d%d",&S,&T);

	return true;
}

int main(){
	while( read() ){
		spfa(S);
		if ( INT_MAX == D[T] ) printf("-1\n");
		else printf("%d\n",D[T]);
	}
	return 0;
}
