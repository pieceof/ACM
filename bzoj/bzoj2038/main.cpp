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

typedef long long llt;
int const SIZE = 60100;
int const BLOCK_SIZE = 250;

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
int const Q_SIZE = 200100;
mo_t Mo_query[Q_SIZE];

llt Answer1[Q_SIZE];
llt Answer2[Q_SIZE];

int Cnt[1000100];

llt MoAns;
inline void insert( int n ){
    Cnt[n]++;
    Cnt[n] > 1 ? MoAns += Cnt[n]*2-2 :false;
}
inline void remove( int n ){
    Cnt[n] > 1 ? MoAns -= Cnt[n]*2-2:false;
    Cnt[n]--;
}
void Mo(){
    sort(Mo_query,Mo_query+q);
    int cur_left = 1;
    int cur_right = 0;
    MoAns = 0;
    for (int i = 0;i < q;++i ){
        while ( cur_right < Mo_query[i].e ) insert(A[++cur_right]);
        while ( cur_left > Mo_query[i].s  ) insert(A[--cur_left]);
        while ( cur_right > Mo_query[i].e  ) remove(A[cur_right--]);
        while ( cur_left < Mo_query[i].s  ) remove(A[cur_left++]);
        Answer1[Mo_query[i].idx] = MoAns;
        llt len = cur_right-cur_left+1;
        Answer2[Mo_query[i].idx] = (MoAns==0) ? 1: (len)*(len-1);

    }
}

llt gcd(llt a,llt b){
    return b == 0? a: gcd( b ,a%b );
}
int main(){
    while ( scanf("%d%d",&n,&q) != EOF ){
        for (int i = 1;i <= n;++i )
            scanf("%lld",A+i);
//        scanf("%d",&q);
        for (int i = 0;i < q;++i ){
            scanf("%d%d",&Mo_query[i].s,&Mo_query[i].e);
            Mo_query[i].idx = i;
        }
        Mo();
        for (int i = 0;i < q;++i )
            printf("%lld/%lld\n", Answer1[i]/gcd(Answer1[i],Answer2[i]) , Answer2[i]/gcd(Answer1[i],Answer2[i]) );

    }
    return 0;
}
