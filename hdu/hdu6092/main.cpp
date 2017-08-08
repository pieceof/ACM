#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
const int SIZE = 1000000;
typedef long long llt;
llt b[SIZE];
/*
先确定a[1] , 减去a[1]的贡献....
反向背包,依次减去之前的贡献
  b[j] -= b[j-i];
*/
int answer[100];
int main(){
//    readfile("in.txt");
    int n,m;
    int t;scanf("%d",&t);
    while ( t-- ){
        scanf("%d%d",&n,&m);
        for ( int i = 0;i <= m;++i){
            scanf("%lld",b+i);
        }
        int anscnt = 0;
        for (int i = 1;i < m;++i ){
            if ( anscnt >= n ) break;
            while ( b[i] && anscnt < n ){
                b[i]--;
                answer[anscnt++] = i;
                for ( int j = i+i; j <= m;++j )
                    b[j] -= b[j-i];
            }
        }
        for (int i = 0;i < n-1;++i ) printf("%d ",answer[i]);
        printf("%d\n",answer[n-1]);
    }
    return 0;
}
