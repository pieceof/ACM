#include <cstdio>
#include <algorithm>
#include<cstring>
using namespace std;

const int SIZE = 30100;
const int BLOCK_SIZE = 200;
struct _t{
    int s,e;
    int idx;
    friend bool operator < ( _t const&a, _t const&b){
        int ln = a.s / BLOCK_SIZE;
        int rn = b.s / BLOCK_SIZE;
        return ln < rn || ( ln == rn && a.e < b.e );
    }
}qt[200010];

int n,q;
int nub[SIZE];
int MoAns;
int Cnt[1000010];
int ans[200010];

void init( ){
    MoAns = 0;
    memset(Cnt,0,sizeof(Cnt));
}
void insert( int x ){
    Cnt[x]++;
    if ( 1 == Cnt[x] ) MoAns++;
}
void remove( int x ){
    Cnt[x]--;
    if ( 0 == Cnt[x] ) MoAns--;
}

void solve( ){
    init();
    sort(qt,qt+q);
    int curRight =0,curLeft = 1;

    for (int i = 0;i < q; ++i ){
        while( curRight < qt[i].e ) insert(nub[++curRight]);
        while( curLeft  > qt[i].s ) insert(nub[--curLeft]);
        while( curRight > qt[i].e ) remove(nub[curRight--]);
        while( curLeft  < qt[i].s ) remove(nub[curLeft++]);
        ans[qt[i].idx] = MoAns;

    }
}


void read(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",nub+i);
    scanf("%d",&q);
    for(int i=0;i<q;++i){
        scanf("%d%d",&qt[i].s,&qt[i].e);
        qt[i].idx = i;
    }
}


int main()
{
    read();
    solve();
    for (int i = 0;i < q;++i ){
        printf("%d\n",ans[i]);
    }
    return 0;
}
