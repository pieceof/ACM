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


llt MOD ,mod;
struct Cube{
//private:
    enum {Cube_SIZE=100};
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

Cube arr;
llt solve(llt a,llt b,llt n,llt m) {
    MOD = mod = m;
    arr.spec = 2;
    arr.mat[0][0] = (a+a+m)%m;arr.mat[0][1] = ( (b-a*a)%m + m ) % m ;
    arr.mat[1][0] = 1;        arr.mat[1][1] = 0;
    if ( n == 0 ) { return 2  ; }
    if ( n == 1 ) { return a+a; }
    arr = arr ^ (n-1);
    return (  ( arr.mat[0][0]*(a+a) )%m + ( arr.mat[0][1]*(2) )%m + m )%m;
}
llt a,b,n,m;
int main(){
    while ( scanf("%lld%lld%lld%lld",&a,&b,&n,&m) != EOF){
        llt ans = solve(a,b,n,m);
        printf("%lld\n",ans);
    }
    return 0;
}

