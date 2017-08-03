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
#define MOD  2017
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
const int SIZE = 35000;

int phi[SIZE] = {0,0,1};
void init(){
    for (int i = 3;i < SIZE;++i){
        phi[i] = (i-1)*( phi[i-1] + phi[i-2] ) % MOD;
    }
}


int main(){
    init();
    int n;
    while( scanf("%d",&n) != EOF ){
        n /= 3;
        int ans = phi[n] * phi[n] % MOD;
        ans = ans * phi[n] % MOD;
        printf("%d\n",ans);
    }

    return 0;
}

