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
const int MOD = 1000000007;
const int Cube_SIZE = 2;   //矩阵大小
struct Cube{
    llt mat[Cube_SIZE][Cube_SIZE];
};
//单位矩阵
Cube const _UnitCube = {
    1, 0,
    0, 1,
};
///矩阵乘法
Cube _Multiply(Cube A,Cube B,llt mod){
    Cube _tmpCube;
    for (int i = 0;i < Cube_SIZE;++i)
    for (int j = 0;j < Cube_SIZE;++j){
        _tmpCube.mat[i][j] = 0;
        for (int k = 0;k < Cube_SIZE;++k){
            _tmpCube.mat[i][j] += A.mat[i][k]*B.mat[k][j];
            _tmpCube.mat[i][j] %= mod;
        }
    }
    return _tmpCube;
}
///矩阵快速幂
Cube power_Cube(Cube A,llt n,llt mod)
{
    Cube _tmpCube = _UnitCube;
    while(n){
        if(n & 1)
            _tmpCube = _Multiply(_tmpCube, A ,mod);
        A = _Multiply(A, A, mod);
        n >>= 1;
    }
    return _tmpCube;
}
llt n,m;
int main(){
    Cube arr;
    llt x,y;
//    int t;scanf("%d",&t);
    while ( scanf("%I64d%I64d",&x,&y) != EOF ){

        scanf("%I64d",&n);
        llt ans = 0;
        arr.mat[0][0] = 1;arr.mat[0][1] = -1;
        arr.mat[1][0] = 1;arr.mat[1][1] = 0;
        if ( n == 1 ) ans = x;
        else if ( n == 2 ) ans = y;
        else {
            arr = power_Cube(arr,n-2,MOD);
            ans = (arr.mat[0][0] * y  + arr.mat[0][1] * x )%MOD;
        }


        printf("%I64d\n",(ans+MOD)%MOD);
//        cout <<ans<<endl;
    }
    return 0;
}
