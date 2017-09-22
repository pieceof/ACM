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

typedef int weight_t;

int const SIZE = 101;

int n;

weight_t Graph[SIZE][SIZE];
bool flag[SIZE];
weight_t D[SIZE];

weight_t Prim(){

    fill(D,D+SIZE,INT_MAX);
    MEM(flag,0);

    weight_t ret = D[1] = 0;

    for (int i  = 1;i <= n;++i){

        int k = -1;

        for (int j = 1;j <= n;++j)
            if (!flag[j] && ( -1 == k || D[j] < D[k] ))
                k = j;

        flag[k] = true;
        ret += D[k];

        for (int j = 1;j <= n;++j)
            if( !flag[j] && Graph[k][j] < D[j])
                D[j] = Graph[k][j];
    }
    return ret;
}
bool read(){

    scanf("%d",&n);
    if (0 == n)return false;
    int m = n*(n-1)/2;

    for (int i = 0;i < m;++i){
        int a,b,w;
        scanf("%d%d%d",&a,&b,&w);
        Graph[a][b] = Graph[b][a] = w;
    }
    return true;
}

int main()
{
    while( read()){

        int ans = Prim();
        printf("%d\n",ans);
    }

    return 0;
}
