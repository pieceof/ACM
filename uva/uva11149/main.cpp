//////////////////////////////////////////////////////////
//                       _oo0oo_                        //
//                      o8888888o                       //
//                      88" . "88                       //
//                      (| -_- |)                       //
//                      0\  =  /0                       //
//                    ___/`---'\___                     //
//                  .' \\|     |// '.                   //
//                 / \\|||  :  |||// \                  //
//                / _||||| -:- |||||- \                 //
//               |   | \\\  -  /// |   |                //
//               | \_|  ''\---/''  |_/ |                //
//               \  .-\__  '-'  ___/-. /                //
//             ___'. .'  /--.--\  `. .'___              //
//          ."" '<  `.___\_<|>_/___.' >' "".            //
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |          //
//         \  \ `_.   \_ __\ /__ _/   .-` /  /          //
//     =====`-.____`.___ \_____/___.-`___.-'=====       //
//                       `=---='                        //
//                                                      //
//                                                      //
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      //
//                                                      //
//               佛祖保佑         永无BUG               //
//////////////////////////////////////////////////////////

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <cstring>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <set>
#include <queue>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a),-1,sizeof(a))
#define varName(x) #x
#define deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define deBugPair(exp1,exp2) cout<< " == > " << "(" << #exp1<<" : "<< (exp1) << "," << #exp2 << " : " << (exp2) << ")" << endl
#define Case   printf("Case %d:\n",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path)  freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
typedef long long llt;
double const PI = acos(-1.0);

const int MOD = 10;

struct Cube{
//private:
    static const int Cube_SIZE = 100;   //矩阵大小
    static const int mod = MOD;
//public:
    int spec;
    int mat[Cube_SIZE][Cube_SIZE];
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
    Cube operator ^ (int n){
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
        printf("\n");
        for (int i = 0;i < spec;++i ){
            for (int j = 0;j < spec;++j )
                printf("%3d",mat[i][j]);
            printf("\n");
        }printf("\n");
    }
};

const int SIZE = 100;
int n,k;
int orz[SIZE][SIZE];
int ans[SIZE][SIZE];


int main(){
//    readfile("in.txt");
//    writefile("out.txt");
    Cube arr;
//    int t;scanf("%d",&t);
    while ( scanf("%d%d",&n,&k) == 2 && (n) ){

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
        printf("\n");
    }
    return 0;
}
