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
#include <utility>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <bitset>
//unused
#include <complex>
#include <functional>
#include <fstream>
#include <ctime>
#include <stdexcept>
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
typedef int llt ;
//cout.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
//freopen("cin.txt", "r", stdin);
//freopen("cout.txt", "w", stdout);
const int SIZE = 105000;

llt num[SIZE];
llt yy[SIZE],zz[SIZE];
llt zhei[SIZE],yhei[SIZE],hei[SIZE];

map<int,vector<int> > pre;
stack<int>st;
bool vis[SIZE];

void ArrayPrint(int *a,int n){
    for (int i = 1;i <= n ;++i )
        cout <<a[i]<<" ";
    cout <<endl;
}
void init(){
    MEM(vis,0);
    MEM(zhei,0);
    MEM(yhei,0);
    MEM(hei,0);

    MEM(zz,0);
    MEM(yy,0);

}

void dfszz( int nowi){
    vis[nowi] = 1;
    int prei;
    if ( pre.count(nowi) == 0 ){
        return;
    }
    for ( vi_iter iter = pre[nowi].begin(); iter != pre[nowi].end() ;++iter ){
        prei = *iter;
        int tmp = hei[prei]-num[prei] < 0 ? 0 : hei[prei]-num[prei];

        zz[prei] = zz[nowi] + (tmp)*abs(nowi-prei);
        dfszz( prei );
    }
}

void dfsyy( int nowi){
    vis[nowi] = 1;
    int prei;
    if ( pre.count(nowi) == 0 ){
        return;
    }
    for ( vi_iter iter = pre[nowi].begin(); iter != pre[nowi].end() ;++iter ){
        prei = *iter;
        int tmp = hei[prei]-num[prei] < 0 ? 0 : hei[prei]-num[prei];

        yy[prei] = yy[nowi] + (tmp)*abs(nowi-prei);
        dfsyy( prei );
    }
}

int main(){
//freopen("in.txt", "r", stdin);
//freopen("in.txt", "w", stdout);


    int t;
    scanf("%d",&t);
    while( t-- ){
        int n;
        scanf("%d",&n);

        init();
        for (int i = 1;i <= n;++i )
            scanf("%d",num+i);

        llt youmax = 0;
        for (int i = n;i >= 1;--i ){
            youmax = max(youmax,num[i]);
            yhei[i] = youmax;
        }
        llt zuomax = 0;
        for (int i = 1;i <= n;++i ){
            zuomax = max(zuomax,num[i]);
            zhei[i] = zuomax;
        }
        for (int i = 1;i <= n-1;++i)
            hei[i] = min(zhei[i],yhei[i+1]);


        pre.clear();
        while ( !st.empty() )st.pop();

        st.push(1);
        int ii = 2;
        while( ii <= n  ){
            while ( num[ii] < num[st.top()] && ii <= n )
                st.push(ii++);
            while ( !st.empty() && num[ii] >= num[st.top()] ){
                int tmp = st.top();
                st.pop();
                pre[ ii ].push_back(tmp);

            }
            st.push(ii++);
        }

//        for (int i = n;i >= 1;--i )
//            if ( pre.count( i ) )
//                for (vi_iter iter = pre[i].begin();iter != pre[i].end();++iter)
//                    cout <<i<<"  "<< *iter<<endl;
        for (int i = n;i >= 1;--i)
            if ( vis[i] == 0 )
                dfszz(i);


        //ArrayPrint(zz,n);


        pre.clear();
        while ( !st.empty() )st.pop();
        st.push(n);
        int jj = n-1;
        while( jj >= 1 ){
            while ( num[jj] < num[st.top()] && jj >= 1 )
                st.push(jj--);
            while ( !st.empty() && num[jj] >= num[st.top()] ){
                int tmp = st.top();
                st.pop();
                pre[ jj ].push_back(tmp);
            }
            st.push(jj--);
        }

//        for (int i = n;i >= 1;--i )
//            if ( pre.count( i ) )
//                for (vi_iter iter = pre[i].begin();iter != pre[i].end();++iter)
//                    cout <<i<<"  "<< *iter<<endl;
        MEM(vis,0);
        for (int i = 1;i <= n;++i )
            if ( vis[i] == 0 )
                dfsyy(i);
        //ArrayPrint(yy,n);

        llt ans = 0;
        for ( int i = 1; i <= n-1;++i ){
            ans = max(ans,hei[i]+yy[i]+zz[i+1]);
            //printf("%d ",hei[i]+yy[i]+zz[i+1] );
        }
        //cout <<endl;

        printf("%d\n",ans);
    }

}


