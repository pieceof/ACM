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



llt MOD;
llt mod;
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

llt n,m,k,b;

int main(){
//    readfile("in.txt");
//    writefile("out.txt");
    Cube arrk , arrb , arr , arrs ,arrsk , ans ;
//    int t;scanf("%d",&t);while( t-- ){
    while ( scanf("%lld%lld%lld%lld",&k,&b,&n,&m) != EOF ){
        mod = MOD = m;

        arr.spec = 2;
        arr.mat[0][0] = 1; arr.mat[0][1] = 1;
        arr.mat[1][0] = 1; arr.mat[1][1] = 0;

        arrk = arr ^ k;
        arrb = arr ^ b;

        arr.spec = 4;
        arr.init();
        for (int i = 0;i < 2;++i )
            arr.mat[i][i] = 1 , arr.mat[i][i+2] = 1 ;
        for (int i = 0;i < 2;++i ) for (int j = 0;j < 2;++j )
            arr.mat[i+2][j+2] = arrk.mat[i][j];

        arrs = arr ^(n);

        arrsk.spec = 2;
        for (int i = 0;i < 2;++i )for (int j = 0;j < 2;++j )
            arrsk.mat[i][j] = arrs.mat[i][j+2];

        ans = arrb * arrsk;
        printf("%lld\n",ans.mat[1][0]);

    }
    return 0;
}
