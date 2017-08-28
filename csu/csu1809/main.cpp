#include "../../headers.h"

const int SIZE = 300000;
int _RMQ_max[SIZE][20]; //预处理数组
int _RMQ_min[SIZE][20]; //预处理数组

void getRMQ( int const a[] ,int n ){
    for (int i = 0;i < n;++i) _RMQ_min[i][0] = a[i];//_RMQ_max[i][0] = a[i];;
    for (int j = 1;(1<<j) <= n;++j )
        for (int i = 0;i+(1<<j) <=n;++i )
            _RMQ_min[i][j] = min( _RMQ_min[i][j-1] ,_RMQ_min[i+(1<<(j-1))][j-1] );
//            _RMQ_max[i][j] = max( _RMQ_max[i][j-1] ,_RMQ_max[i+(1<<(j-1))][j-1] );
}
int querry_min(int A,int B){
    int k = (int)(log((double)(B+1-A))/log(2.0));
    return min( _RMQ_min[A][k] , _RMQ_min[B+1-(1<<k)][k] );
}
//int querry_max(int A,int B){
//    int k = (int)(log((double)(B+1-A))/log(2.0));
//    return max( _RMQ_max[A][k] , _RMQ_max[B+1-(1<<k)][k] );
//}

int suf[SIZE];
char str[SIZE];

int main(){
    int n,m;
    while ( scanf("%d%d",&n,&m) != EOF ){
        scanf("%s",str);
        suf[0] = 1;
        for (int i = 1;i < n;++i ){
            if ( str[i] == '(' )
                suf[i] = suf[i-1] + 1;
            else
                suf[i] = suf[i-1] - 1;
        }
//        ArrayDisp(suf,n);
        getRMQ(suf,n);
        int x,y;
        while ( m-- ){
            scanf("%d%d",&x,&y);
            if ( x-- > y-- )swap( x,y );
            if ( str[x] == str[y] ||
                ( str[x] == ')' && str[y] == '(' ) ) printf("Yes\n");
            else {
                if ( querry_min(x,y-1) <= 1 )
                    printf("No\n");
                else
                    printf("Yes\n");
            }
        }
    }
    return 0;
}
