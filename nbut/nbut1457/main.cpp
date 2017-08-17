#include <cstdio>
#include <map>
#include <cmath>
#include <algorithm>
#include <set>
#include <cstring>
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
int const SIZE = 101100;
int BLOCK_SIZE ;

struct mo_t{
    int s,e;
    int idx;
    mo_t (){};
    mo_t (int ss,int ee,int ii):s(ss),e(ee),idx(ii) {};
    friend bool operator <(const mo_t&a,const mo_t&b){
        int ln = a.s / BLOCK_SIZE;
        int rn = b.s / BLOCK_SIZE;
        return ln < rn || ( ln==rn && a.e < b.e );
    }
};

int n,q;
llt A[SIZE];
int const Q_SIZE = SIZE;
mo_t Mo_query[Q_SIZE];

llt Answer[Q_SIZE];
int Cnt[SIZE];
llt MoAns;

//vector<llt> Intager_Cache;
map<llt,llt> Intager_Id;
int Intager_Cnt;

llt Get_Intager_Id( int x ){
    if ( Intager_Id.count(x) ) return Intager_Id[x];
    return Intager_Id[x] = Intager_Cnt++;
}




#define pow3(x) (x)*(x)*(x)
inline void insert( int n ){
    Cnt[n]++;
    (Cnt[n] >= 1 ) ? MoAns += pow3(Cnt[n]) - pow3(Cnt[n]-1) :false;
}
inline void remove( int n ){
    (Cnt[n] >= 1 ) ? MoAns -= pow3(Cnt[n]) - pow3(Cnt[n]-1) :false;
    Cnt[n]--;
}

void Mo(){
    sort(Mo_query,Mo_query+q);
    int cur_left = 1;
    int cur_right = 0;
    MoAns = 0;
    for (int i = 0;i < q;++i ){
        while ( cur_right < Mo_query[i].e )
            insert(A[++cur_right]);
        while ( cur_left > Mo_query[i].s  ) insert(A[--cur_left]);
        while ( cur_right > Mo_query[i].e  ) remove(A[cur_right--]);
        while ( cur_left < Mo_query[i].s  ) remove(A[cur_left++]);
        Answer[Mo_query[i].idx] = MoAns ;

    }
}

//template <typename T>
inline bool scan_d (llt &ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; //EOF
    while (c != '-' && (c < '0' || c > '9') ) {
        if((c = getchar()) == EOF) return 0;
    }
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}
//template<typename T>
char s[33], *s1;
void print(llt &x) {
    s1 = s;
    if (!x) *s1++ = '0';
    if (x < 0) putchar('-'), x = -x;
    while(x) *s1++ = (x % 10 + '0'), x /= 10;
    while(s1-- != s) putchar(*s1);
}
//template<typename T>
void println(llt &x) {
    print(x); putchar('\n');
}

int main(){
//    int t;scanf("%d",&t);

    while ( scanf("%d",&n) != EOF ){
//        scanf("%d%d",&n,&q);
        BLOCK_SIZE = (int)sqrt((double)n);
        CLEAR(Cnt);
        Intager_Cnt = 0;
        Intager_Id.clear();
        for (int i = 1;i <= n;++i ){
            llt x;
            scan_d(x);
            A[i] = Get_Intager_Id(x);
        }
        scanf("%d",&q);
        for (int i = 0;i < q;++i ){
            scanf("%d%d",&Mo_query[i].s,&Mo_query[i].e);
            Mo_query[i].idx = i;
        }
        Mo();
        for (int i = 0;i < q;++i )
            println( Answer[i] ) ;
    }
    return 0;
}
