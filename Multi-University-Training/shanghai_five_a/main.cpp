#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;
using namespace std;

/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/

const int SIZE = 1000;

int cnt[SIZE];
int main()
{
    int n,m;
    while ( scanf("%d%d",&n,&m) != EOF ){
        CLEAR(cnt);
        int x;
        for (int i = 0;i < n;++i ){

            for (int j = 0;j < m;++j ){
                scanf("%d",&x);
                if ( x == 1  ) cnt[j]++;
            }
        }
        for (int j = 0;j < m-1 ;++j )
            printf("%d ",cnt[j]);
        printf("%d\n",cnt[m-1]);
    }

    return 0;
}
