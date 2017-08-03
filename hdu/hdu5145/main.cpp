#include <cstdio>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef long long llt ;

const int MOD = 1000000007;

llt const SIZE = 55000;
llt BLOCK_SIZE ;//分块大小为接近根号n的整数，这样容易调试
llt gcd(llt a,llt b){  return b==0?a:gcd(b,a%b); }

struct _t{
    llt s,e;
    llt idx;
};

bool operator  < (_t const&lhs,_t const&rhs){
    llt ln = lhs.s / BLOCK_SIZE;
    llt rn = rhs.s / BLOCK_SIZE;
    return ln < rn || ( ln == rn && lhs.e < rhs.e );
}

llt N,Q;
llt A[SIZE];
_t B[50010];
llt Ans1[50010];

llt Cnt[1000010] = {0};

//逆元筛
int const  Ns = 3e4+7;
llt inv[Ns]={0,1};
void init(){
    for (int i = 2;i <= Ns;++i ){
        inv[i]=inv[MOD%i]*(MOD-MOD/i)%MOD;
    }
}
llt MoAns;
llt len;
inline void insert(llt n){
    Cnt[n]++;
    len++;
    MoAns = (MoAns*len % MOD * inv[Cnt[n]] %MOD);

}

inline void remove(llt n){

    MoAns = (MoAns*Cnt[n] % MOD * inv[len] %MOD);
    --Cnt[n];
    len--;
}

void Mo(){
    sort(B,B+Q);

    llt curLeft = 1;
    llt curRight = 0;
    MoAns = 1;
    len = 0;
    for(llt i=0;i<Q;++i){
        while( curRight < B[i].e  )
            insert(A[++curRight]);
        while( curLeft > B[i].s )
            insert(A[--curLeft]);
        while( curRight > B[i].e )
            remove(A[curRight--]);
        while( curLeft < B[i].s )
            remove(A[curLeft++]);
        Ans1[B[i].idx] = MoAns;
    }
}

void read(){
    scanf("%lld%lld",&N,&Q);
    for(llt i=1;i<=N;++i)scanf("%lld",A+i);
    BLOCK_SIZE = sqrt(N);
    for(llt i=0;i<Q;++i){
        scanf("%lld%lld",&B[i].s,&B[i].e);
        B[i].idx = i;
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    int t;
    init();
    scanf("%d",&t);
    while( t-- ){
        read();
        Mo();
        memset(Cnt,0,sizeof(Cnt));

        for(llt i=0;i<Q;++i){
            llt a = Ans1[i];
            printf("%lld\n",a);
        }


    }
    return 0;
}
