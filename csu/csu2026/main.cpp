//
// Created by bitwater on 18-4-2.
//

#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;
typedef long long llt;

llt price[10000];
int main()
{
    int n;
    while(scanf("%d",&n) != EOF){
        for(int i = 0;i < n;i++ )cin>>price[i];
        llt ans = 100;
        int idx = 1;
        while( idx < n && price[idx]<=price[idx-1] )idx++;
        if(idx == n ) {
            cout << 100 << endl;
            continue;
        }
        llt cnt = ans/price[idx-1];
        ans %= price[idx-1];
        for(int i = idx;i < n; ){
            int j = i;
            if ( price[j] - price[j-1] >= 0){
                while( j < n && price[j] - price[j-1] >= 0 )j++;
                ans += cnt*price[j-1];
                cnt = 0;
            }else {
                while( j < n && price[j] - price[j-1] <= 0 )j++;

                if( j-1 == n-1 )break;
                llt tmp = ans/price[j-1];
                if( tmp > 100000 )tmp = 100000;
                ans -= tmp*price[j-1];
                cnt = tmp;
            }
            i = j;
        }
        cout <<ans<<endl;
    }
    return 0;
}
