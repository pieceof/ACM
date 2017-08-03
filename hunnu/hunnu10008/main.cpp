#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
#include <stdlib.h>
//stl
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <bitset>

//define
#define MOD  1000000007
#define INF 1<<30
#define EPS 1e-13
#define S(r) r*r*PI
#define PI acos(-1.0)
#define UP(i,x,y) for(llt i=x;i<=y;i++)
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define InterceptBit(x,startbit,len)  (((x)<<(31-(startbit)))>>(31-(len-1)))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

using namespace std;
typedef map<int,int>::iterator mii_iter;
typedef map<int,string>::iterator mis_iter;
typedef map<string,string>::iterator mss_iter;
typedef map<int,vector<int> >::iterator mivi_iter;
typedef vector<int>::iterator vi_iter;
typedef vector<string>::iterator vs_iter;
typedef string::iterator s_iter;
typedef long long llt ;
/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/
const int SIZE = 65536+1000;

llt nub[SIZE];
void init( ){
    nub[1] = 1;
    for (int i = 1;i < SIZE;++i ){
        nub[i]=nub[i-1]+i;
        if ( nub[i] < 0 ) break;

    }
}
llt row( llt x ){
    llt * p = lower_bound(nub,nub+SIZE,x);
    return p-nub;
}
//int row(int n)
//{
//    int r;
//    r = sqrt(2*n);
//    while(2*n > r*(r+1))
//        r++;
//    return r;
//}
llt first( llt x ) {
    return x*(x-1)/2 + 1;
}
int main(){
    init();
    llt a[3];
    while (scanf("%I64d%I64d%I64d",a+0,a+1,a+2) != EOF){
        printf("%I64d %I64d %I64d",a[0],a[1],a[2]);
        sort(a,a+3);

        llt ra = row(a[0]);
        llt rb = row(a[1]);
        llt rc = row(a[2]);
        bool isok = 0;
        if ( ra == rb ) {
            llt dx = a[1]-a[0];
            llt tar = first(dx+ra) + a[1] - first(ra);
//            deBug(tar);
            if ( tar == a[2] ) isok = 1;
        }
        if ( rb == rc ){
            llt dx = a[2]-a[1];
            llt tar = first(rb-dx) + a[1] - first(rb);
//            deBug(tar);
            if ( tar == a[0] ) isok = 1;
        }
        if ( ra == rc ) isok = 0;

        if ( isok ) printf(" are vertices of an equilateral triangle.\n");
        else printf(" are not vertices of an equilateral triangle.\n");
    }
    return 0;
}
