#include"../../headers.h"
const int MOD = 10000007;
const int Cube_SIZE = 15;   //矩阵大小
struct Cube{
    int spec;
    llt mat[Cube_SIZE][Cube_SIZE];
};
//单位矩阵
Cube const _UnitCube = {15,
{
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
}
};
///矩阵乘法
Cube _Multiply(Cube const&A,Cube const&B,llt mod){
    Cube _tmpCube;
    _tmpCube.spec = A.spec;
    for (int i = 0;i < A.spec;++i)
    for (int j = 0;j < A.spec;++j){
        _tmpCube.mat[i][j] = 0;
        for (int k = 0;k < A.spec;++k){
            _tmpCube.mat[i][j] += A.mat[i][k]*B.mat[k][j];
            _tmpCube.mat[i][j] %= mod;
        }
    }
    return _tmpCube;
}
///矩阵快速幂
Cube power_Cube(Cube &A,llt n,llt mod)
{
    Cube _tmpCube = _UnitCube;
    _tmpCube.spec = A.spec;
    while(n){
        if(n & 1)
            _tmpCube = _Multiply(_tmpCube, A ,mod);
        A = _Multiply(A, A, mod);
        n >>= 1;
    }
    return _tmpCube;
}
llt n,m;
int nub[15] = {23};
int main(){
    Cube arr;
//    int t;scanf("%d",&t);
    while ( scanf("%I64d%I64d",&n,&m) != EOF ){
        for (int i = 1 ;i <= n;++i )
            scanf("%d",nub+i);
        nub[0] = 23;
        nub[++n] = 3; n++;
        for (int i = 0;i < n-1;++i ){
            arr.mat[i][0] = 10;
            for (int j = 1;j < n-1;++j ){
                if ( j > i ) arr.mat[i][j] = 0;
                else arr.mat[i][j] = 1;
            }
            arr.mat[i][n-1] = 1;
        }
        arr.spec = n;
        for (int i = 0;i < n;++i )
            arr.mat[n-1][i] = 0;
        arr.mat[n-1][n-1] = 1;
//        ArrayDisp( (llt*)arr.mat,n,n,15);
        arr = power_Cube(arr,m,MOD);
//        ArrayDisp( (llt*)arr.mat,n,n,15);
        llt ans = 0;
        for (int i = 0;i < n;++i  ){
            ans += (nub[i]*arr.mat[n-2][i])%MOD;
            ans %= MOD;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
