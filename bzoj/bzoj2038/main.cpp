#include <cstdio>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef long long llt ;

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
llt Ans2[50010];
llt Cnt[1000010] = {0};
void read(){
    scanf("%lld%lld",&N,&Q);
    for(llt i=1;i<=N;++i)scanf("%lld",A+i);
    BLOCK_SIZE = sqrt(N);
    for(llt i=0;i<Q;++i){
        scanf("%lld%lld",&B[i].s,&B[i].e);
        B[i].idx = i;
    }
}

llt MoAns;
inline void insert(llt n){
    Cnt[n]++;
    if ( Cnt[n] > 1 ) MoAns += Cnt[n]+Cnt[n]-2 ;
}

inline void remove(llt n){
    if ( Cnt[n] > 1  ) MoAns -= Cnt[n]+Cnt[n]-2 ;
    --Cnt[n];
}

void Mo(){
    sort(B,B+Q);

    llt curLeft = 1;
    llt curRight = 0;
    MoAns = 0;

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
        Ans2[B[i].idx] = (curRight-curLeft+1)*(curRight-curLeft);
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    read();
    Mo();
    for(llt i=0;i<Q;++i){
        llt a = Ans1[i];
        llt b = Ans2[i];
        if ( a == 0 ){
            printf("0/1\n");
        }else {
            printf("%lld/%lld\n",a/gcd(a,b),b/gcd(a,b));
        }

    }
    return 0;
}
