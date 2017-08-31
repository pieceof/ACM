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
//               ·ð×æ±£ÓÓ         ÓÀÎÞBUG               //
//////////////////////////////////////////////////////////

#include "../../headers.h"


const llt MOD = 10000007;
struct Cube{
//private:
    enum {Cube_SIZE=110,mod=MOD};
//    int mod;
//public:
    int spec;
    llt mat[Cube_SIZE][Cube_SIZE];
    Cube(int s=0):spec(s){ init(); };
    void init(int sp = -1 ){
        CLEAR(mat);
        if ( sp != -1 ) spec = sp;
        for (int i = 0;i < spec;++i ) mat[i][i] = 1;
    }
    ///¾ØÕó³Ë·¨
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
    ///¾ØÕó¿ìËÙÃÝ
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

llt n,m;
llt nub[15] = {23};
int main(){
    Cube arr;
//    int t;scanf("%d",&t);
    while ( scanf("%I64d%I64d",&n,&m) != EOF ){

        for (int i = 1 ;i <= n;++i ) scanf("%d",nub+i);
        nub[0] = 23;
        nub[++n] = 3; n++;

        arr.init(n);
        for (int i = 0;i < n-1;++i ){
            arr.mat[i][0] = 10;
            for (int j = 1;j < n-1;++j )
                arr.mat[i][j] = ( j > i ) ? 0 : 1;
            arr.mat[i][n-1] = 1;
        }
        arr.mat[n-1][n-1] = 1;
        arr = arr ^ m ;
        llt ans = 0;
        for (int i = 0;i < n;++i )
            ans = (ans + (nub[i]*arr.mat[n-2][i])%MOD ) % MOD;

        printf("%lld\n",ans);
    }
    return 0;
}
