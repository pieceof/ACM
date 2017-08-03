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
typedef string::iterator iter;
map<string ,string > mp;
int main()
{
//freopen("in", "r", stdin);
//freopen("cout.txt", "w", stdout);

    int n;
    cin>>n;
    string str,tmp,word;
    getline(cin,str);
    iter  it ,s , e;
    while( n-- ){
        getline(cin,str);
        //cout <<str<<endl;
        it = str.begin();
        while( *it != ' ' && it!=str.end())it++;
        word = string(str.begin(),it);
        s = ++it;
        while ( 1 ){
            if ( *it == ' ' || it == str.end() ){
                tmp = string(s,it);
                //cout <<tmp<<endl;
                if ( tmp == "") continue;
                for ( iter j = tmp.begin();j != tmp.end();++j )
                    if ( *j <= 'Z' )
                        *j += 'a' - 'A';
                mp[tmp] = word;
                if ( it == str.end( ) )
                    break;
                s = ++it;
                continue;
            }
            it++;
        }
    }
    getline(cin,str);
    int t = 1;

    while( getline(cin,str) ){
        //cout <<t++<<" " << str;
        s = it = str.begin();
        while( 1 ){
            if (*it ==' ' ||
                *it =='(' ||
                *it ==')' ||
                *it ==';' ||
                *it ==',' ||
                *it =='.' ||
                *it =='?' ||
                *it =='!' ||
            it == str.end( ) ){

                tmp = string(s,it );
                for ( iter j = tmp.begin();j != tmp.end();++j )
                    if ( *j <= 'Z' )
                        *j += 'a' - 'A';
                if ( mp.find( tmp ) != mp.end() ){
                    cout<<mp[tmp]<<endl;
                    break;
                }
                if ( it == str.end())
                    break;
                s = ++it;
                continue;
            }
            it++;

        }
    }

    return 0;
}
