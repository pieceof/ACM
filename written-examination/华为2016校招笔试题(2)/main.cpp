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
typedef map<string,int>::iterator msi_iter;
typedef map<string,string>::iterator mss_iter;
typedef map<int,vector<int> >::iterator mivi_iter;
typedef vector<int>::iterator vi_iter;
typedef vector<string>::iterator vs_iter;
typedef string::iterator s_iter;
typedef long long llt ;
// ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
//freopen("cin.txt", "r", stdin);
//freopen("cout.txt", "w", stdout);
const int SIZE = 105000;
map < pair<string,int> ,int > mp;
vector < pair<string,int> > vs ;
struct _t{
    string s;
    int hangshu;
    int cnt;
    _t(string ss,int h ,int cc) : s(ss),hangshu(h),cnt(cc){}
    friend bool operator < (const _t&a ,const _t&b ){
        if (a.cnt != b.cnt)
            return a.cnt > b.cnt;
        vector < pair<string,int> >::iterator x = find(vs.begin(),vs.end(),make_pair(a.s,a.hangshu));
        vector < pair<string,int> >::iterator y = find(vs.begin(),vs.end(),make_pair(b.s,b.hangshu));

        return x < y;
    }
};


string make( string str){
    string ret = "";

    if ( str.find('\\') != string::npos  ){
        s_iter it = str.end()-1;
        while(*it != '\\' )it--;
        ret = string(it+1,str.end());
        if ( ret.size() > 16 )
            ret = string (str.end()-16,str.end());
    }else {
        if ( str.size() > 16 ){
            ret = string (str.end()-16,str.end());
        }else {
            ret = str;
        }
    }
    //cout <<ret<<endl;
    return ret;
}
int main(){

    string a;
    int hangshu;
    mp.clear();
    while ( cin>>a ){

        cin>>hangshu;
        string ss = make(a);
        vs.push_back(make_pair(ss,hangshu));
        if ( mp.count(make_pair(ss,hangshu)) == 0 ){
            mp[make_pair(ss,hangshu)] = 1;
        }else {
            mp[make_pair(ss,hangshu)]++;
        }
    }
    set<_t>st;
    map < pair<string,int> ,int >::iterator it;
    for ( it = mp.begin();it!=mp.end();++it){
        //cout <<it->first<<" "<<it->second<<endl;
        st.insert( _t( it->first.first,it->first.second,it->second));
    }
    int ct = 0;
    for (auto i : st){
        if ( ct ++ > 7 )break;
        cout <<i.s<<" "<<i.hangshu<<" "<<i.cnt<<endl;
    }

    return 0;
}

