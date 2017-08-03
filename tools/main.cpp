#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
// 按位截取位 x的第startbit 位开始的len长的位数
#define InterceptBit(x,startbit,len)  (((x)<<(31-(startbit)))>>(31-(len-1)))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )

using namespace std;
int RandomNumble(int a,int b){
    static int  t = time(0);
    t += 1000 ;
    srand(t);
    return (rand() % (b-a+1) )+a;
}
int main()
{

    return 0;
}
