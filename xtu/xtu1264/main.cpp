#include <bits/stdc++.h>

#define clear(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
typedef long long llt;

using namespace std;
const int SIZE =1e5+5;
int num  [SIZE];
int sum  [SIZE];


int main()
{
    int n , m ,c;
    while ( scanf("%d%d%d",&n,&m,&c) != EOF ){
        sum[0] = 0;
        for ( int i = 1  ; i <= n ;++i ){
            scanf("%d",num+i);
            sum[i] = sum[i-1] + num[i];
        }
        sort(sum,sum+n+1);
        int l = 0, r = n ;
        llt ans = 0;
        while ( m -- && l < r ){
            if ( sum[r] - sum[l] <= c ) break;
            ans += sum[r] - sum[l] - c;
            r-- , l++;
        }
        if ( ans > INT_MAX) while(1);
        printf("%I64d\n",ans);
    }

    return 0;
}
