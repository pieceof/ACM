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
const int SIZE = 100060;

char str[SIZE];

int cnt[30];
//inline toID( char const&ch ){
//
//}

void just( int n ){
    CLEAR(cnt);
    for (int i = 0;i < n;++i ){
        if ( str[i] > 'a' )cnt[str[i]-'a']++;
        else cnt[str[i]-'A']++;
    }
    int ans = INT_MAX;
    ans = min( ans , cnt['i'-'a'] );
    ans = min( ans , cnt['l'-'a'] );
    ans = min( ans , cnt['o'-'a'] );
    ans = min( ans , cnt['v'-'a'] );
    ans = min( ans , cnt['e'-'a']/2 );
    ans = min( ans , cnt['c'-'a'] );
    ans = min( ans , cnt['s'-'a'] );
    printf("%d\n",ans);
}

int main()
{
    while( scanf("%s",str) != EOF){
        just(strlen(str));
    }

    return 0;
}
