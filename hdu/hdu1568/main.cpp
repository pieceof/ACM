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

const llt MOD = 1e10;

struct Cube{
//private:
    enum {Cube_SIZE=40,mod=MOD};
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


llt p,q,n;

int main(){
//    readfile("in.txt");
//    writefile("out.txt");
    Cube arr;
//    int t;scanf("%d",&t);
    while ( scanf("%lld",&n) != EOF ){
        if ( n == 0 ){
            printf("0\n");
            continue;
        }
        if ( n == 1 ){
            printf("1\n");
            continue;
        }
        arr.spec = 2;
        arr.mat[0][0] = 1; arr.mat[0][1] = 1;
        arr.mat[1][0] = 1; arr.mat[1][1] = 0;
        arr = arr ^ ( n-1 );
        llt ans1 = arr.mat[0][0]%MOD;// + arr.mat[0][1]%MOD;
        double ans2 = log10( 1/sqrt(5) ) + n * log10( (1+sqrt(5))/2 );
//        deBug(ans2);
        ans2 = floor( pow(10,ans2 - int(ans2))*1000 );
        if ( n > 40 )
            printf("%.0f\n",ans2);
        else{
             while ( ans1 > 10000 )ans1/=10;
            printf("%lld\n",ans1);
        }

    }
    return 0;
}
