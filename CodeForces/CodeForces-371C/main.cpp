#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
typedef long long llt;
const int SIZE = 11000;

llt price[3];
llt need[3];
llt have[3];
char str[SIZE];
llt r,l,k;


bool check ( llt sum ,llt k ){
    for (int i = 0 ;i < 3;++i ){
        if ( need[i] == 0 ) continue;
        llt nowmake = have[i]/need[i];
        llt leave = have[i] % need[i];
        llt willneed = (sum-nowmake)*need[i] - leave;
        if ( willneed <= 0 ) continue;
        if ( willneed > (k /price[i]) ) return 0;
        k -= willneed*price[i];
    }
    return true;
}
bool read() {
    if ( EOF == scanf("%s",str) ) return 0;
    int len = strlen( str );
    CLEAR(need);
    for (int i = 0;i < len;++i ){
        if ( str[i] == 'B' ) need[0]++;
        if ( str[i] == 'S' ) need[1]++;
        if ( str[i] == 'C' ) need[2]++;
    }
    for (int i = 0;i < 3;++i )
        scanf("%I64d", have+i);
    for (int i = 0;i < 3;++i )
        scanf("%I64d", price+i);
    return 1;
}


int main(){

    while ( read() ){
        l = 0 , r = 1100000000000LL ;
        while ( l < r ){
            llt  mid = l + (r-l)/2;
            if ( check(mid ,k) ) l = mid+1;
            else r = mid;
        }
        printf("%I64d\n",l-1);
    }
    return 0;
}
