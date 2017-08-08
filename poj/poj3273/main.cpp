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
const int SIZE = 110000;

int cost[SIZE];
int n,m;
int r,l,k;


bool check ( int sum ){
    int tmp = sum;
    int cnt = 0;
    for (int i = 0 ;i < n;++i ){
        if (sum < cost[i] ) return 0;
        if ( tmp < cost[i] )
            cnt++,tmp = sum,i--;
        else
            tmp -= cost[i];
    }
    if ( cnt < m || (cnt==m&&tmp==0) )return 1;
    return 0;
}
bool read() {
    if ( EOF == scanf("%d%d",&n,&m) ) return 0;
    for (int i = 0;i < n;++i )
        scanf("%d", cost+i);
    return 1;
}


int main(){

    while ( read() ){
        l = 0 , r = 1000000000;
        while ( l < r ){
            int  mid = (l+r)/2;
            if ( check(mid) ==0) l = mid+1;
            else r = mid;
        }
        printf("%d\n",r);
    }
    return 0;
}
