#include <cstdio>
#include<cstring>

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

const int SIZE = 10;

char chess[SIZE][SIZE];
bool col[SIZE];


int dfs( int k,int depth ,int n ,int l ){
    if ( k >= depth ) return 1;
    if ( l >= n ) return 0;

    int ret = 0;
    ret += dfs( k,depth,n,l+1);
    for ( int i = 0;i < n;++i ){
        if ( chess[l][i] == '#' && col[i] == 0 ){
            col[i] = 1;
            ret += dfs(k+1,depth,n,l+1);
            col[i] = 0;
        }
    }
    return ret;
}

int main()
{
    int n,k;
    while ( scanf("%d%d",&n,&k) != EOF ){
        if ( n == -1 && k == -1 ) return 0;
        for (int i = 0 ; i < n;++i )
            scanf("%s",chess[i]);
        int ans;
        CLEAR(col);
        ans = dfs(0,k,n,0);
        printf("%d\n",ans);
    }

    return 0;
}
