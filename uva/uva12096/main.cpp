#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
// 按位截取位 x的第startbit 位开始的len长的位数
#define InterceptBit(x,startbit,len)  (((x)<<(31-(startbit)))>>(31-(len-1)))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
typedef long long llt;
using namespace std;

#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())

map < set<int> , int > set_ID;
vector< set<int> > set_cache;

stack <int> s;
char op[10];


int ID ( set <int > x ){
    if ( set_ID.count(x) != 0 ) return set_ID[x];
    set_cache.push_back(x);
    return set_ID[x] = set_cache.size()-1;
}
void oper( ){

    scanf("%s",op);
    if ( *op == 'P' ){
        s.push( ID(set<int>()) );
    }else if ( *op == 'D' ){
        s.push( s.top() );
    }else {
        set<int> s1 = set_cache[s.top()]; s.pop();
        set<int> s2 = set_cache[s.top()]; s.pop();
        set<int> x;

        if ( *op == 'U' )
            set_union(ALL(s1),ALL(s2),INS(x));
        if ( *op == 'I')
            set_intersection(ALL(s1),ALL(s2),INS(x));
        if ( *op == 'A'){
            x = s2 ;
            x.insert( ID(s1) );
        }
        s.push(ID(x));
    }

}
void solve( ){
    int t,n;
    scanf("%d",&t);
    while ( t-- ){
        scanf("%d",&n);
        while ( n -- ){
            oper();
            printf("%d\n",set_cache[s.top()].size());
        }
        puts("***");
    }
}

int main()
{
    solve();
    return 0;
}
