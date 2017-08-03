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
char str[SIZE];
llt to_ten( int n ){
    llt ret = 0;
    llt tmp = 1;
    for (int i = n-1;i >= 0 ;--i ){
        ret += (str[i]-'a')*tmp;
        tmp *= 26;
    }
    return ret;
}
char str2[SIZE];
void ten_to( llt x ,int b){
    if ( x == 0 ){
        puts("0");
        return;
    }
    int i = 0;
    while ( x ){
        str2[i++] = ( x%b + '0');
        x/=b;
    }
    for ( i-- ;i >= 0 ;--i ){
        printf("%c",str2[i]);
    }
    puts("");
}
int main()
{
    ios::sync_with_stdio(false);
    int b;
    while(scanf("%s%d",str,&b)!=EOF ){
        llt x = to_ten( strlen( str) );
        ten_to( x , b);
    }

    return 0;
}
