#include "../../headers.h"

llt MOD = 10000;
int mod;
struct Cube{
//private:
    enum {Cube_SIZE=100};
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
int n,k,m;
int orz[SIZE][SIZE];
int ans[SIZE][SIZE];


int main(){
//    readfile("in.txt");
//    writefile("out.txt");
    Cube arr;
//    int t;scanf("%d",&t);
    while ( scanf("%d%d%d",&n,&k,&m) != EOF ){
        mod = MOD = m;
        CLEAR(arr.mat);
        CLEAR(orz);
        arr.spec = n+n;
        for (int i = 0;i < n;++i )
            arr.mat[i][i] = arr.mat[i][i+n] = 1;
        for (int i = 0;i < n;++i )for (int j = 0;j < n;++j ){
            scanf("%d",&arr.mat[i+n][j+n]);
            orz[i+n][j] = arr.mat[i+n][j+n] = arr.mat[i+n][j+n]%MOD;
        }
//        arr.Disp();
//        ArrayDisp((int*)orz,n+n,n,SIZE);
        arr = arr ^ (k);
//        arr.Disp();
//        printf("\n");
        for (int i = 0;i < n;++i ){
            for (int j = 0;j < n;++j ){
                ans[i][j] = 0;
                for (int k = 0;k < n;++k ){
                    ans[i][j] += arr.mat[i][k+n]*orz[k+n][j] % MOD;
                    ans[i][j] %= MOD;
                }

            }
        }
        for (int i = 0;i < n;++i ){
            printf("%d",ans[i][0]);
            for (int j = 1;j < n;++j )
                printf(" %d",ans[i][j]);
            printf("\n");
        }
    }
    return 0;
}
