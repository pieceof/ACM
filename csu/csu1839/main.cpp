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
#define MEM(a,x) memset(a,x,sizeof(a))

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
const int SIZE = 105000;

struct _t {
    int wt,st;
    int sp,ep;
    _t(int ww = 0,int sst = 0,int ss = 0,int ee = 0):wt(ww),st(sst),sp(ss),ep(ee) {}
} trap[SIZE];

double quyu( double a,double b){
    int cnt = int(a/b);
    return a - cnt*b;

}


int main() {
    //freopen("in_runner.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int t;
    scanf("%d",&t);
    while( t-- ) {
        int n;
        scanf("%d",&n);
        int a,b,c,d;
        double maxdirt = INT_MAX;
        for (int i = 0; i < n; ++i ) {
            scanf("%d%d%d%d",&a,&b,&c,&d);
            trap[i].wt = a;
            trap[i].st = b;
            trap[i].sp = c;
            trap[i].ep = d;
            maxdirt = min(maxdirt, double(b) / double(d-c) );
        }
        //cout <<maxdirt<<endl;
        bool isOk = 0;
        double nowdirt;
        // now pos
        double ans = 0;
        for (int np = 0; np < n ; ++np ) {
            //if ( isOk ) break;
            // now time
            for ( int i = 0 ; true ; ++ i ) {

                nowdirt = i * ( trap[np].wt + trap[np].st ) + trap[np].wt;
                nowdirt /= trap[np].sp;
                double tmp = nowdirt;
                if (  nowdirt <= maxdirt ) {
                    bool flag = 1;
                    // all trap
                    for (int j = 0; j < n; ++j) {
                        if ( np == j ) continue;
                        double hs = nowdirt * trap[j].sp;
                        double he = nowdirt * trap[j].ep;
                        int cnt1 = hs / (trap[j].wt + trap[j].st);
                        int cnt2 = he / (trap[j].wt + trap[j].st);

                        if ( quyu( he, (trap[j].wt + trap[j].st)) < EPS )cnt2--;
                        if (
                            quyu(hs,(trap[j].wt + trap[j].st))
                            < trap[j].wt
                                || cnt1 != cnt2)    flag = 0;
                        if ( !flag ) break;

                    }
                    if ( flag )isOk = 1, ans = max(nowdirt,ans);
                }
                //if ( isOk ) break;
                nowdirt = (i+1) * ( trap[np].wt + trap[np].st );
                nowdirt /= trap[np].ep;
                //if ( nowdirt < ans ) break;
                if ( nowdirt <= maxdirt ) {
                    bool flag = 1;
                    // all trap
                    for (int j = 0; j < n; ++j) {
                        if ( np == j )continue;
                        double hs = nowdirt * trap[j].sp;
                        double he = nowdirt * trap[j].ep;
                        int cnt1 = hs / (trap[j].wt + trap[j].st);
                        int cnt2 = he / (trap[j].wt + trap[j].st);
                         if ( quyu( he, (trap[j].wt + trap[j].st)) <EPS )cnt2--;
                        if (
                                quyu(hs,(trap[j].wt + trap[j].st))
                             < trap[j].wt
                                || cnt1 != cnt2
                           ) flag = 0;
                        if ( !flag ) break;

                    }
                    if ( flag )isOk = 1, ans = max(nowdirt,ans);
                    //if ( isOk ) break;
                }


                if ( nowdirt > maxdirt && tmp > maxdirt )break;

            }
        }

        //cout <<ans<<endl;;
        if ( isOk ) printf("%.4f\n",1/ans);//printf("%lf\n",double(1/ans));
        else puts("IMPOSSIBLE");
    }
    return 0;
}

