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

int const SIZE = 30100;
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
int A[SIZE];
int const Q_SIZE = 200100;
mo_t Mo_query[Q_SIZE];
int Answer[Q_SIZE];
int Cnt[1000100];

int MoAns;
inline void insert( int n ){
    ++ Cnt[n] == 1 ? ++MoAns:false;
}
inline void remove( int n ){
    -- Cnt[n] == 0 ? --MoAns:false;
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
        Answer[Mo_query[i].idx] = MoAns;
    }
}


int main(){
    while ( scanf("%d",&n) != EOF ){
        for (int i = 1;i <= n;++i )
            scanf("%d",A+i);
        scanf("%d",&q);
        for (int i = 0;i < q;++i ){
            scanf("%d%d",&Mo_query[i].s,&Mo_query[i].e);
            Mo_query[i].idx = i;
        }
        Mo();
        for (int i = 0;i < q;++i )
            printf("%d\n",Answer[i]);
    }
    return 0;
}
