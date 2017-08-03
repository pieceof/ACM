#include <bits/stdc++.h>
#define MEM(a,x) memset(a , x , sizeof(a))
using namespace std;

/**下标从1开始，只能存一条边
  *注意初始化
  */
typedef int weight_t;
const int SIZE_V  = 110;
int n;

weight_t Road[SIZE_V][SIZE_V];
///不能存多条边，所以存边要先判断
inline void mkEdge(int const &a,int const &b,weight_t const &w){
    Road[a][b] = max(Road[a][b],w);
}
weight_t D[SIZE_V];
bool flag[SIZE_V];
void spfa(int s){

    MEM(flag,0);
    fill(D,D+SIZE_V,0);
    D[s] = 0;
    flag[s] = true;

    queue<int>q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        flag[u] = false;
        for (int i = 1;i <= n+1;++i){
            ///注意是减法，初始化没边是int_max，加上D[u]会变成负数
            if ( Road[u][i] == 0 ) continue;
            if ( D[i] < Road[u][i] + D[u] ){
                D[i] = Road[u][i]+D[u];
                if (!flag[i]){
                    flag[i] = true;
                    q.push(i);
                }
            }
        }
    }
}


void init(){
    for (int i = 0;i<= n+1;++i)for (int j = 0;j <= n+1;++j){
        Road[i][j] = 0;
    }
}

int main(){
    int p,q;
    int t;scanf("%d",&t);
    while ( t-- ) {
        scanf("%d%d%d",&n,&p,&q);
        int a,b,c;
        init();
        while ( p-- ){
            scanf("%d%d",&a,&b);
            a++;
            mkEdge(a,1,b);
        }
        while ( q-- ){
            scanf("%d%d%d",&a,&b,&c);
            a++,b++;
            mkEdge(a,b,c);
        }
        spfa(2);
        int ans = 0;
        for (int i = 1;i <= n+1;++i ){
            ans = max(ans,D[i]);
            cout << D[i] <<endl;
        }
        cout << ans << endl;
    }

}
