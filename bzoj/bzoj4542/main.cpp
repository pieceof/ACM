
#include <bits/stdc++.h>
typedef long long llt;
using namespace std;
const llt SIZE = 500500;
llt BLOCK_SIZE;

struct _t{
    llt s,e;
    llt idx;
    friend bool operator < ( const _t&a,const _t&b){
        llt l = a.s/BLOCK_SIZE;
        llt r = b.s/BLOCK_SIZE;
        return l < r || ( l == r && a.e < b.e ) ;
    }
};


_t qst[SIZE];

llt Cnt[SIZE] = {0};
llt p,m,l,r;
llt mod[SIZE]={0};
llt Ans[SIZE];
char str[SIZE];
llt MoAns = 0;
void init( ){
    MoAns = 0;
    memset( Cnt,0,sizeof(Cnt) );
    memset( mod,0,sizeof(mod) );
}

void pro( ){
    int len = strlen(str+1);
    //cout <<str[len]<<endl;
    //cout <<111<<endl;
    llt mul10 = 1;
    BLOCK_SIZE = sqrt(len);
    for (int i = len;i >= 1;-- i ){
        mod[i] = ( (str[i]-'0')*mul10 + mod[i+1] )% p;
        mul10 = ( mul10*10 ) % p;
    }
//    for (int i = 1;i <= len;++i ){
//        cout  <<mod[i]<< " " ;
//    }
//    cout <<endl;
}

void insert( llt x ){
    Cnt[x]++;
    MoAns += Cnt[x]-1;
}
void remove( llt x ){
    //if ( x < 1)return;
    MoAns -= Cnt[x]-1;
    Cnt[x]--;
}
void Mo(){
    sort(qst,qst+m);
    llt curRight = -1,curLeft = 0;

    for (int i = 0;i < m; ++i ){
        while( curRight < qst[i].e ) {
            curRight++;
            insert(mod[(curRight)+1]);

        }
        while( curLeft  > qst[i].s ) insert(mod[(--curLeft)]);
        while( curRight > qst[i].e ){

            remove(mod[(curRight)+1]);
            curRight--;
        }
        while( curLeft  < qst[i].s ) {
            if (curLeft < 1 ){
                curLeft++;
                    continue;
            }
                remove(mod[(curLeft++)]);
        }
        Ans[qst[i].idx] = MoAns;
    }
}
llt cnt2[SIZE];
llt sum2[SIZE];
void cal( ){
    int len = strlen(str+1);
    memset(cnt2,0,sizeof(cnt2));
    memset(sum2,0,sizeof(sum2));
    llt x,y;
    for(int i=1;i<=len;i++) cnt2[i]=cnt2[i-1]+((str[i]-'0')%p==0);
    for(int i=1;i<=len;i++) sum2[i]=sum2[i-1]+((str[i]-'0')%p==0?i:0);
    for(int i=1;i<=m;i++){
        scanf("%lld%lld",&x,&y);
        printf("%lld\n",sum2[y]-sum2[x-1]-(cnt2[y]-cnt2[x-1])*(x-1));
    }
}

int main(){
//freopen("123.in", "r", stdin);
//freopen("cout.txt", "w", stdout);
    scanf("%lld%s%lld",&p,str+1,&m);

    if ( p == 2 || p == 5 ){
        cal();
        return 0;
    }
    init();
    llt  a,b;
    for (int i = 0;i < m;++i ){
        scanf("%lld%lld",&qst[i].s,&qst[i].e);
        qst[i].idx = i;
    }
    pro();
    Mo();
    for (int i = 0 ;i < m;++i )
        printf("%lld\n",Ans[i]);
    return 0;
}

