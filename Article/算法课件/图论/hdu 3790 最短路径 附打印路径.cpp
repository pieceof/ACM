#include <iostream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <climits>
#include <deque>
#include <cmath>
#include <queue>
#include <stack>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <cstdio>
#include <bitset>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include <stdlib.h>
#define INF 1<<30
#define EPS 1e-13
#define S(r) r*r*PI
#define PI acos(-1.0)
#define UP(i,x,y) for(int i=x;i<=y;i++)
#define DOWN(i,x,y) for(int i=x;i>=y;i--)
#define MEM(a,x) memset(a,x,sizeof(a))
#define Wt while(t--)
#define endll printf("\n")
#define post cout <<"111111111111111111111111111"<<endl
using namespace std;

int gcd(int a,int b){  return b==0?a:gcd(b,a%b);  }
typedef long long llt ;

#define MOD  1000000007
const int maxn = 150000;
#define LEFT 0
#define RIGHT 1

//cout.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
//freopen("cin.txt", "r", stdin);
//freopen("cout.txt", "w", stdout);
struct weight_t{
    int cost = INT_MAX;
    int leight = INT_MAX;

    weight_t(int l = 0,int c = 0):leight(l),cost(c){}

    friend bool operator <(weight_t const &a,weight_t const &b){
        if ( a.leight == b.leight ) return a.cost < b.cost;
        return a.leight < b.leight;
    }
    void clr(){
        cost = INT_MAX;
        leight = INT_MAX;
    }
    friend bool operator == (weight_t const &a,weight_t const &b){
        return (a.leight == b.leight)&&(a.cost == b.cost);
    }
    friend weight_t operator +(weight_t const &a,weight_t const &b){
        weight_t temp;
        temp.cost = a.cost + b.cost;
        temp.leight = a.leight + b.leight;
        return temp;
    }
    bool isMax(){
        return (cost == INT_MAX) &&(leight == INT_MAX);
    }
};

//typedef int weight_t;
const int SIZE_V = 1050;
const int SIZE_E = 100010;

struct edge_t{
    int v;
    weight_t w;
    edge_t *next;
}Edge[SIZE_E];

edge_t *V[SIZE_V];
int n;
int ECnt = 0;

void mkEdge(int const &a,int const &b,weight_t const &w){
    Edge[ECnt].v = b;
    Edge[ECnt].w = w;
    Edge[ECnt].next = V[a];
    V[a] = Edge+ECnt++;

    Edge[ECnt].v = a;
    Edge[ECnt].w = w;
    Edge[ECnt].next = V[b];
    V[b] = Edge+ECnt++;
}

weight_t D[SIZE_V];
bool flag[SIZE_V];

int Pre[SIZE_V];
void disPathIter(int t){
    if (-1 != Pre[t]) disPathIter(Pre[t]);
    printf(" %d",t);
}
void disPath(int t){
    printf("SPFA: ");
    disPathIter(t);
    printf("\n");
}


void spfa(int s){
    MEM(Pre,-1);
    MEM(flag,0);

    for (int i = 0;i <= n;++i){
        D[i].clr();
    }
    D[s].cost = D[s].leight = 0;

    flag[s] = true;
    queue<int>q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        flag[u] = false;

        for(edge_t *p = V[u];p;p = p->next){

            int v = p->v;
            weight_t temp = D[u] + p->w;

            if (temp < D[v]){
                D[v] = temp;
                if (!flag[v]){
                    flag[v] = true;
                    q.push(v);
                    Pre[v] = u;
                }
            }
        }
    }
}
void init(){
    ECnt = 0;
    memset(V,0,sizeof(V));
    MEM(Edge,0);
}
int m;
int s,t;
bool read(){
    init();
    scanf("%d%d",&n,&m);
    if (n == 0&& m == 0) return false;
    int a,b,l,c;

    for (int i = 0;i < m;++i){
        scanf("%d%d%d%d",&a,&b,&l,&c);
        weight_t w(l,c);
        mkEdge(a,b,w);
    }
    scanf("%d%d",&s,&t);
    return true;
}
int main(){

    while(read()){
        spfa(s);
        printf("%d %d\n",D[t].leight,D[t].cost);
        disPath(t);
    }
    return 0;
}
