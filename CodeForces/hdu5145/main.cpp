#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
typedef int int_t;
const int mod = 1000000007;
//非递归的扩展欧几里德算法
//返回a、b的gcd，同时x、y满足ax+by=gcd
int_t exEuclid(int_t a,int_t b,int_t&x,int_t&y){
    int_t x0 = 1, y0 = 0;
    int_t x1 = 0, y1 = 1;
    x = 0; y = 1;
    int_t r = a % b;
    int_t q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}
//求a相对于p的逆元，a、p互质才存在逆元
int_t inv(int_t a,int_t p){
    int_t x,y;
    int_t r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}


typedef long long llt;
int const SIZE = 61100;
int const BLOCK_SIZE = 200;

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
int const Q_SIZE = 40000;
mo_t Mo_query[Q_SIZE];

llt Answer[Q_SIZE];
int len;
int Cnt[40000];

llt MoAns;
inline void insert( int n ){
    len++;
    Cnt[n]++;
    (Cnt[n] >= 1 && len > 1) ? MoAns = ( (MoAns*len)%mod * inv(Cnt[n],mod) ) % mod:false;
}
inline void remove( int n ){
    (Cnt[n] >= 1 && len > 1) ? MoAns = ( (MoAns*Cnt[n])%mod*inv(len,mod)) % mod :false;
    len--;
    Cnt[n]--;
}

void Mo(){
    sort(Mo_query,Mo_query+q);
    int cur_left = 1;
    int cur_right = 0;
    MoAns = 1;
    len = 0;
    for (int i = 0;i < q;++i ){
        while ( cur_right < Mo_query[i].e )
            insert(A[++cur_right]);
        while ( cur_left > Mo_query[i].s  ) insert(A[--cur_left]);
        while ( cur_right > Mo_query[i].e  ) remove(A[cur_right--]);
        while ( cur_left < Mo_query[i].s  ) remove(A[cur_left++]);
        Answer[Mo_query[i].idx] = MoAns % mod ;

    }
}

llt gcd(llt a,llt b){
    return b == 0? a: gcd( b ,a%b );
}
int main(){
    int t;scanf("%d",&t);

    while ( t-- ){
        scanf("%d%d",&n,&q);
        CLEAR(Cnt);
        for (int i = 1;i <= n;++i )
            scanf("%lld",A+i);
//        scanf("%d",&q);
        for (int i = 0;i < q;++i ){
            scanf("%d%d",&Mo_query[i].s,&Mo_query[i].e);
            Mo_query[i].idx = i;
        }
        Mo();
        for (int i = 0;i < q;++i )
            printf("%lld\n", Answer[i] );
    }
    return 0;
}

