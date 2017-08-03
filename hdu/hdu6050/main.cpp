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
const int Cube_SIZE = 2;///矩阵大小
struct Cube{
    llt mat[Cube_SIZE][Cube_SIZE];
};
//单位矩阵
Cube const _UnitCube = {
    1, 0,
    0, 1,
};
///矩阵乘机
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
Cube power_Cube(Cube A,llt n,llt mod)  //矩阵快速幂
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
    int t;scanf("%d",&t);
    while ( t-- ){
        scanf("%lld%lld",&n,&m);
        llt ans = 0;
        arr.mat[0][0] = 0;arr.mat[0][1] = 1;
        arr.mat[1][0] = 2;arr.mat[1][1] = 1;
        arr = power_Cube(arr,n,MOD);
        if( n % 2 == 0 ){
            arr.mat[0][0] -= 1;
            arr.mat[1][1] -= 1;
        }else {
            arr.mat[0][0] -= -1;
            arr.mat[0][1] -= 1;
            arr.mat[1][0] -= 2;
            arr.mat[1][1] -= 0;
        }
        arr = power_Cube(arr,m-1,MOD);
        ans += (arr.mat[0][0] + arr.mat[0][1] )%MOD;
        ans %= MOD;
        printf("%lld\n",ans);
//        cout <<ans<<endl;
    }
    return 0;
}
