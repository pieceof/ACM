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
#define UP(i,x,y) for(int i=x;i<=y;i++)
#define MEM(a,x) memset(a,x,sizeof(a))

int gcd(int a,int b){  return b==0?a:gcd(b,a%b); }
typedef long long llt ;



//cout.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
//freopen("cin.txt", "r", stdin);
//freopen("cout.txt", "w", stdout);
using namespace std;
map<string , int > mp;
stringstream stream;
typedef string::iterator siter;
void get( string a,int statu) {
    if ( a == "" ) return;
    siter st ,en ,numst,numen;
    int itmp;
    for ( siter it = a.begin() ; it != a.end();){
        if ( *it == '(' ){
            int dumz=1;

            st = it+1;
            it++;
            while( 1 ){
                if( *it == '(' ){
                    dumz++;
                    it++;
                }else if ( *it == ')'){
                    it++;
                    if ( dumz > 1 ) dumz--;
                    else {
                        break;
                    }
                }else {
                    it++;
                }
            }
            en = it-1;
            //cout <<*it<<endl;
            numst = it;
            while( *it >= '0' && *it <= '9' )
                it++;
            numen = it;
            //cout <<numen - numst<<endl;
            //cout <<*it<<endl;
            string tmp(st,en);
            //cout <<tmp<<endl;
            string num(numst,numen);
            //cout <<num<<endl;
            if ( num == "")
                itmp = 1;
            else {
                stream.clear();
                stream << num;
                stream >>itmp;
            }
            //cout <<*it<<endl;
            //cout <<()<<endl;
            get(tmp , statu*itmp );
            if (it == a.end() ) break;
            //it++;
            continue;
        }
        //cout <<*it<<endl;
        if (it == a.end() ) break;
        st = it++;
        while( *it <= 'z' && *it >= 'a' ) it++;
        en = it;
        numst = it;
        //cout <<*it<<endl;
        while( *it >= '0' && *it <= '9' )
                it++;

        numen = it;
        //cout <<*it<<endl;
        string tmp(st,en);
        //cout <<tmp<<endl;
        string num = string(numst,numen);
        //cout <<num<<endl;
        if ( num == "")
            itmp = 1;
        else {
            stream.clear();
            stream << num;
            stream >>itmp;
        }

        if ( mp.find(tmp) != mp.end()  )
            mp[tmp] += itmp*statu;
        else
            mp[tmp] = itmp*statu;
        //it--;
    }
    return ;
}
int main()
{
    //freopen("chemistry.in", "r", stdin);
    //freopen("cout.txt", "w", stdout);
    string a;
    while (cin>>a){
        mp.clear();
        get(a,1);

        map<string,int>::iterator it = mp.begin();
        if ( it->second != 1 ){
                cout <<it->second;
            }
        cout <<it->first;
        for ( it++ ;it != mp.end();++it){
            cout <<"+";
            if ( it->second != 1 ){
                cout <<it->second;
            }
            cout <<it->first;
        }
        cout <<endl;
    }

    return 0;
}
