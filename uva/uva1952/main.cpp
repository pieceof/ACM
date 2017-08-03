#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;

using namespace std;


const int SIZE = 10010;
vector< int > datebase[SIZE];
typedef string::iterator str_iter;
map< pair<int,int> , int > sm;

map<string ,int > cache_ID;
vector <string > cache_str;

int main()
{
//    freopen("out.txt","r",stdin);
//    freopen("out2.txt","w",stdout);
//    ios::sync_with_stdio(false);
    int n,m;
    while ( cin>>n>>m ){
        cin.get();
        for (int i = 0 ;i < n;++i ) datebase[i].clear();
        string a;
        sm.clear();
        cache_ID.clear();
        cache_str.clear();
        int Cnt = -1;
        for (int i = 0 ;i < n;++i ){
            getline(cin,a);
//            deBug(a);
            str_iter si = a.begin();
            string b;

            while ( si != a.end() ){
                str_iter ei = si+1;
                while ( *ei != ',' && ei != a.end() ) ei++;
                b = string(si,ei);
                if ( cache_ID.count(b) == 0 ) {
                    cache_ID[b] = ++Cnt;
//                    deBug(b);
//                    cache_str.push_back(b);
                    datebase[i].push_back(Cnt);
                }else{
//                    deBug(cache_ID[b]);
                    datebase[i].push_back(cache_ID[b]);
                }
                if ( ei == a.end() )break;
                si = ei+1;
            }

        }
        pair<int,int> c;
        bool flag = 0;
        for (int c1 = 0;c1 < m;++c1){
            if (flag) break;
            for ( int c2 = c1+1;c2 < m;++c2){
                if (flag ) break;
                sm.clear();
                for (int i = 0 ;i < n;++i ){
//                    cout <<  datebase[i][c1] << datebase[i][c2] << endl;
                    c = make_pair(datebase[i][c1] ,datebase[i][c2]) ;
                    if ( sm.count( c ) == 0 )sm[c] = i;
                    else{
                        flag = 1;
                        cout << "NO" <<endl;
                        cout << sm[c]+1 << " " << i+1 << endl;
                        cout << c1+1 << " " << c2+1 << endl;
                        break;
                    }
                }
            }
        }
        if ( 0 == flag ) cout <<"YES"<< endl;
    }
    return 0;
}
