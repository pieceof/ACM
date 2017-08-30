#include "../../headers.h"

const llt MOD = 9973;
struct Cube{
//private:
    enum {Cube_SIZE=100,mod=MOD};
//    int mod;
//public:
    int spec;
    llt mat[Cube_SIZE][Cube_SIZE];
    Cube(int s=0):spec(s){ init(); };
    void init(){
        CLEAR(mat);
        for (int i = 0;i < spec;++i ) mat[i][i] = 1;
    }
    ///矩阵乘法
    Cube operator * ( Cube const&B ){
        Cube _tmpCube(spec);
        for (int i = 0;i < spec;++i)for (int j = 0;j < spec;++j){
            _tmpCube.mat[i][j] = 0;
            for (int k = 0;k < spec;++k){
                _tmpCube.mat[i][j] += mat[i][k]*B.mat[k][j]%mod;
                _tmpCube.mat[i][j] %= mod;
            }
        }
        return _tmpCube;
    }
    ///矩阵快速幂
    Cube operator ^ (llt n){
        Cube _tmpCube(spec);
        Cube A = *this;
        while(n){
            if(n & 1)
                _tmpCube = _tmpCube * A;
            A = A * A;
            n >>= 1;
        }
        return _tmpCube;
    }
    void Disp(){
        cout << endl;
        for (int i = 0;i < spec;++i ){
            for (int j = 0;j < spec;++j )
                cout << std::right << setw(3) << mat[i][j];
            cout << endl;
        }cout << endl;
    }
};

const int SIZE = 100;
int n;
llt k;

int main(){
//    readfile("in.txt");
//    writefile("out.txt");
    Cube arr;
    int t;scanf("%d",&t);while( t-- ){
//    while ( scanf("%d%d%d",&n,&k,&m) != EOF ){

        scanf("%d%lld",&n,&k);
        CLEAR(arr.mat);
        arr.spec = n;

        for (int i = 0;i < n;++i )for (int j = 0;j < n;++j ){
            scanf("%d",&arr.mat[i][j]);
            arr.mat[i][j] %= MOD;
        }
        arr = arr ^ (k);
        llt ans = 0;
        for (int i = 0;i < n;++i )
            ans = ( ans + arr.mat[i][i] )%MOD;
        printf("%lld\n",ans);

    }
    return 0;
}
