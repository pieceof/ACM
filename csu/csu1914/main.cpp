#include <bits\stdc++.h>
#define lson(x) ( (x) << 1 )
#define rson(x) ( lson(x) | 1 )
using namespace std;
class SegmentTree{
public:
    void build(int t,int s,int e){
        this->Delay[t] = 0;
        if ( s == e ){
            this->ST[t] = -s;
            this->rank[t] = s;
            return;
        }
        int mid = (s+e) >> 1;
        this->build(lson(t),s,mid);
        this->build(rson(t),mid+1,e);
        this->_pushUp(t);
    }
    int query(int t,int s,int e,int a,int b){
        if ( a <= s && e <= b ){
            return this->ST[t];
        }
        int mid = (s+e)>>1;
        int lm,rm;
        if ( a <= mid )  lm = this->query(lson(t),s,mid,a,b);
        if ( mid < b )   rm = this->query(rson(t),mid+1,e,a,b);
        return max(lm,rm);
    }
    //单点更新;
    void modify(int t,int s,int e,int idx,int value){
        if ( s == e ){
            this->ST[t] = value;
            return;
        }
        this->_pushDown(t);
        int mid = ( s + e ) >> 1;
        if ( idx <= mid ) this->modify(lson(t),s,mid,idx,value);
        else this->modify(rson(t),mid+1,e,idx,value);
        this->_pushUp(t);
    }
    //区间更新;
    void modify(int t,int s,int e,int a,int b,int delta){
        if ( a <= s && e <= b ){
            this->ST[t] += delta;
            this->Delay[t] += delta;
            return;
        }
        this->_pushDown(t);
        int mid = (s+e) >> 1;
        if ( a <= mid ) this->modify(lson(t),s,mid,a,b,delta);
        if ( mid < b )  this->modify(rson(t),mid+1,e,a,b,delta);
        this->_pushUp(t);
    }
    void disPlay( int n ){
        cout << "ST : \n";
        for (int i = 1;i <= n;++i )
            cout << this->ST[i] << " "; cout << endl;
        cout << "Rank : \n";
        for (int i = 1;i <= n;++i )
            cout << this->rank[i] << " "; cout << endl;
    }

    static const int SIZE = 200500;
    int source[SIZE];
    int ST[SIZE<<2];
    int rank[SIZE<<2];
    int Delay[SIZE<<2];
private:

    void _pushUp(int t){
        this->ST[t] = max( this->ST[lson(t)] , this->ST[rson(t)] );
        if (this->ST[lson(t)] > this->ST[rson(t)])
            this->rank[t] = this->rank[lson(t)];
        else this->rank[t] = this->rank[rson(t)];
    }
    void _pushDown(int t){
        if ( 0 == this->Delay[t] ) return;
        int &x = this->Delay[t];
        this->Delay[lson(t)] += x;
        this->Delay[rson(t)] += x;
        this->ST[lson(t)] += x;
        this->ST[rson(t)] += x;
        x = 0;
    }
};

const int SIZE = 200500;
int ans[SIZE];
int main()
{
    SegmentTree *st = new SegmentTree;
    int n;

    while( scanf("%d", &n ) != EOF ){
        st->build(1,1,n);
        int a,x;
        fill(ans,ans+n+1,-1);
        for (int i = 1 ;i <= n;++i ){
            scanf("%d%d",&a,&x);
            if ( 0 == a ) st->modify(1,1,n,1,x,1);
            if ( 1 == a ) st->modify(1,1,n,x,n,1);
            //st->disPlay(n<<2);
            if ( st->ST[1] < 0 )continue;
            while ( 0 == st->ST[1] ){
                ans[st->rank[1]] = i;
                st->modify(1,1,n,st->rank[1],INT_MIN);
                //st->disPlay(n<<2);
            }
        }
        for (int i = 1 ;i <= n-1;++i ) printf("%d ",ans[i]);
        printf( "%d\n",ans[n] );
    }
    delete st;
    return 0;
}
