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
#define INF 1000000000000000LL
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

//cout.sync_with_stdio(false);  /// cin, 不能跟 scanf，sscanf, getchar, fgets之类的一起使用
//freopen("cin.txt", "r", stdin);
//freopen("cout.txt", "w", stdout);
/*Kruskal 算法
 *注意：点是从1到n编号
 *
 */

typedef int weight_t;
const int SIZE_V = 101;
const int SIZE_E = SIZE_V / 2 * SIZE_V;
int Father[SIZE_V];
int Ecnt = 0;
//int n;  // 此处写点的全局变量

//并查集算法
void init(int vn){
    for(int i = 0;i <= vn;++i)
        Father[i] = i;
}
int find(int x){
    return (Father[x] == x) ? x :
         Father[x] = find(Father[x]);
}
inline void unite(int x,int y){
    Father[find(y)] = Father[find(x)];
}

struct edge_t{
    int s,e;
    weight_t w;
    friend bool operator < (edge_t const&a,edge_t const&b){
        if (a.w != b.w) return a.w < b.w;
        if (a.s != b.s) return a.s < b.s;
        return a.e < b.e;
    }
}Edge[SIZE_E];

inline void mkEdge(int a,int b,weight_t w){
    if (a > b)swap(a,b);
    Edge[Ecnt].s = a;
    Edge[Ecnt].e = b;
    Edge[Ecnt++].w = w;
}

weight_t Kruskal(int vn,int en){
    init(vn);
    sort(Edge,Edge+en);

    weight_t ret = 0;
    for (int i = 0;i < en; ++i){
        if ( find(Edge[i].s) == find(Edge[i].e))
            continue;
        ret += Edge[i].w;
        unite(Edge[i].s,Edge[i].e);
        --vn;
        if (1 == vn)break;
    }
    return ret;
}

int main()
{
    int n;
    while( scanf("%d",&n) && n){
        Ecnt = 0;

        int en = n*(n-1)/2;

        int a,b;weight_t w;
        for (int i = 0;i < en;++i){
            scanf("%d%d%d",&a,&b,&w);
            mkEdge(a,b,w);
        }

        int ans = Kruskal(n,en);
        printf("%d\n",ans);
    }

    return 0;
}
