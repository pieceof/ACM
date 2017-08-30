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

#include "../../headers.h"



const llt MOD = 7;
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

llt a,b,n;

int main(){
//    readfile("in.txt");
//    writefile("out.txt");
    Cube arr;
//    int t;scanf("%d",&t);
    while ( scanf("%lld%lld%lld",&a,&b,&n) != EOF &&(a||b||n)){
        if ( n == 1 || n == 2 ){
            printf("1\n");
            continue;
        }
        arr.spec = 2;
        arr.mat[0][0] = a%MOD; arr.mat[0][1] = b%MOD;
        arr.mat[1][0] = 1; arr.mat[1][1] = 0;
        arr = arr ^ ( n-2 );
        llt ans = arr.mat[0][0]%MOD + arr.mat[0][1] % MOD;// + arr.mat[0][1]%MOD;
        printf("%lld\n",ans%MOD);

    }
    return 0;
}
