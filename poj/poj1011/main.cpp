#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int SIZE = 1000;
int sticks[SIZE];
int n;
int isok = 0;
bool isUsed[SIZE];
int len = 0;

void dfs ( int nowlen ,int nowid ,int UsedStick ){
    if ( isok ) return ;
    if ( n == UsedStick ) {
        isok = 1;
        return;
    }
    if ( 0 == nowlen ){
        dfs( len , 0, UsedStick );
        return;
    }
    if ( len == nowlen ){
        int i = 1 ;
        while ( isUsed[i] && nowlen >= sticks[i] ) i++;
        isUsed[i] = 1 ;
        dfs( nowlen-sticks[i] , i+1 , UsedStick+1 );
        isUsed[i] = 0;
        return;
    }
    for ( int i = nowid ; i <= n ;++ i ){
        if ( isUsed[i] ) continue;
        if ( !isUsed[i-1] && sticks[i] == sticks[i-1] ) continue;
        if ( nowlen >= sticks[i] ){
            isUsed[i] = 1;
            dfs( nowlen-sticks[i] ,i+1 , UsedStick+1 );
            isUsed[i] = 0;
        }
    }

}
bool cmp ( int const&a, int const&b ){
    return a > b;
}

int main()
{

    while ( scanf( "%d",&n ) && n ){
        int sum = 0;
        int maxlen = 0;
        for (int i = 1; i <= n ;++ i ){
            scanf("%d", sticks+i);
            sum += sticks[i];
            maxlen = max(maxlen,sticks[i]);
        }
        sort( sticks+1, sticks+n+1 , cmp );
        isok = 0;
        sticks[0] = -1;

        int ans = maxlen ;
        //cout << "sum : " << sum << endl;
        //dfs( 6 , 1 , 4 );
        for (; ans <= sum ;++ans ){
            if ( isok ) break;
            if ( 0 == sum % ans ){
                len = ans;
                memset( isUsed, 0 , sizeof(isUsed) );
                dfs( ans , 1, 0);
                if ( isok ) break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
