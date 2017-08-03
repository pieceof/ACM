
//#pragma comment(linker,"/STACK:102400000,102400000")
//#include <Complex>
#include <iostream>
#include <cmath>
#include <set>
#include <cstdio>
#include <algorithm>
#include <assert.h>
#include <cstring>
#define PI acos(-1)
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define varName(x) #x
#define deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define Anslld(x) printf("%lld\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
typedef long long llt;
const int SIZE = 1000+500;
const llt MOD = 998244353;
const llt mod = 998244353;
template <class T>
void dispArray( T const a[],int n ) {
//    printf("this array is  ==  > ");
    if( n < 1) puts("");
    printf("%4d",a[0]);
    for (int i = 1 ; i < n; ++i )printf("%3d",a[i]);
    puts("");
}

//复数结构体
struct Complex{
    double real,imag;
    Complex(double r = 0.0,double i = 0.0):real(r),imag(i) {}
    Complex operator +(const Complex &b){ return Complex(real+b.real,imag+b.imag);}
    Complex operator -(const Complex &b){ return Complex(real-b.real,imag-b.imag);}
    Complex operator *(const Complex &b){ return Complex(real*b.real-imag*b.imag,real*b.imag+imag*b.real);}
};
/*
 * 进行FFT和IFFT前的反转变换。
 * 位置i和 （i二进制反转后位置）互换
 * len必须去2的幂
 */
void Cal_Sort(Complex *y,int len){
    int i,j,k;
    for(i = 1, j = len/2;i < len-1; i++){
        if(i < j)swap(y[i],y[j]);
        k = len/2;
        while( j >= k) j -= k, k /= 2;
        if(j < k) j += k;
    }
}

void DIT_FFT(Complex x[],int len,int on)
{
    Cal_Sort(x,len);
    for(int h = 2; h <= len; h <<= 1){
        Complex wn( cos(-on*2*PI/h),sin( -on*2*PI/h ) );
        for(int j = 0;j < len;j += h){
            Complex w(1,0);
            for(int k = j;k < j+h/2;k++ ){
                Complex u = x[k];
                Complex t = w*x[k+h/2];
                x[k] = u+t;
                x[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)for(int i = 0;i < len;i++) x[i].real /= len;
}

Complex x1[SIZE];
Complex x2[SIZE];

template<class T>
int convolution ( T const a[],int n1,T const b[],int n2,T *c ){
    /**< fft需要补足到2的整次幂 */
    int bini_len = 1;
    while ( bini_len < n1*2 || bini_len < n2*2 ) bini_len <<= 1;

    for (int i = 0;i < n1;++i )
//        x1[i] = Complex( a[n1-i-1]-'0',0);
        x1[i].real = a[i] , x1[i].imag = 0 ;

    for (int i = n1;i < bini_len;++i ) x1[i].real = x1[i].imag = 0 ;

    for (int i = 0;i < n2;++i )
//        x2[i] = Complex( b[n2-i-1] -'0',0);
        x2[i].real = b[i] , x2[i].imag = 0 ;

    for (int i = n2;i < bini_len;++i ) x2[i].real = x2[i].imag = 0 ;

    DIT_FFT(x1,bini_len,1);
    DIT_FFT(x2,bini_len,1);

    for (int i = 0;i < bini_len;++i ) x1[i] = x1[i] * x2[i] ;

    DIT_FFT(x1,bini_len,-1);

    for (int i = 0 ;i < bini_len;++i ) c[i] = (T)(x1[i].real+0.5);
    return bini_len;
}

void FWT_xor(llt a[],int n)
{
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)%mod,a[i+j+d]=(x-y+mod)%mod;
//                //xor:a[i+j]=x+y,a[i+j+d]=(x-y+mod)%mod;
                //and:a[i+j]=x+y;
                //or:a[i+j+d]=x+y;
            }
}
void FWT_or(llt a[],int n)
{
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
//                a[i+j]=(x+y)%mod,a[i+j+d]=(x-y+mod)%mod;
//                //xor:a[i+j]=x+y,a[i+j+d]=(x-y+mod)%mod;
                //and:a[i+j]=x+y;
//                or:
                    a[i+j+d]=x+y;
            }
}
void UFWT_xor(llt a[],int n)
{
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
//                a[i+j]=1LL*(x+y)*rev%mod,a[i+j+d]=(1LL*(x-y)*rev%mod+mod)%mod;
//                xor:
                    a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                //and:a[i+j]=x-y;
                //or:a[i+j+d]=y-x;
            }
}
void UFWT_or(llt a[],int n)
{
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
//                a[i+j]=1LL*(x+y)*rev%mod,a[i+j+d]=(1LL*(x-y)*rev%mod+mod)%mod;
                //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                //and:a[i+j]=x-y;
//                or:
                    a[i+j+d]=y-x;
            }
}
void solve_xor(llt a[],llt b[],int n)
{
    FWT_xor(a,n);
    FWT_xor(b,n);
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%mod;
    UFWT_xor(a,n);
}
void solve_or(llt a[],llt b[],int n)
{
    FWT_or(a,n);
    FWT_or(b,n);
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%mod;
    UFWT_or(a,n);
}
//const int SIZE = 1000000;
int n;
llt a[SIZE],b[SIZE];

llt power[SIZE];
void init(){
    power[0] = 1;
    for (int i = 1 ; i < n;++i ){
        power[i] = (power[i-1]*1526)%MOD;
    }
}

llt da[SIZE],db[SIZE];


llt ta[SIZE],tb[SIZE];
llt c[100];
void init2(){
    for (int i = 0;i < 4;++i) tb[i] = ta[i] = i;
    solve_xor(ta,ta,4);
    solve_or(tb,tb,4);
}

int main(){
//    int m; scanf("%d",&m);
//    n = ( 1<<m ) ;
//    for (int i = 0;i < n;++i )
//        scanf("%lld",a+i);
////    reverse(a,a+n);
//    CLEAR(c);
//    for (int i = 0;i < n;++i )
//        scanf("%lld",b+i);
//    for (int i = 0;i < n;++i ){
//        for (int j = 0;j < n;++j ){
//            c[i&j] += a[i^j] * b[i|j];
//        }
//    }
//    dispArray(c,8);
    set< pair<int,int> > st;
    printf("i j & ^ |\n");
    for (int i = 0;i < 4;++i ){
        for(int j = 0;j < 4;++j ){
            int y = i^j;
            int x = i|j;
//            if ( st.count(make_pair(y,x)) == 0 ){
//                st.insert(make_pair(y,x));
//                printf("%d %d %d %d %d\n",i,j,i&j,i^j,i|j);
//            }
//            if ( (x & y) == y )
                printf("%d %d %d %d %d\n",i,j,i&j,i^j,i|j);
            assert( (x & y) == y );
            assert( (x ^ y) == (i&j) );
        }
    }
//    init2();
//    dispArray(ta,n);
//    dispArray(tb,n);
//    for (int i = 0;i < n ;++i ){
//        da[ i ] = a[ abs(ta[i]) ];
//        db[ i ] = b[ abs(tb[i]) ];
//    }
//
//    reverse(da,da+n);
//    writefile("out.txt");
//    int m; scanf("%d",&m);
//    n = ( 1<<m ) ;
//    for (int i = 0;i < n;++i )
//        scanf("%lld",a+i);
//
//    for (int i = 0;i < n;++i )
//        scanf("%lld",b+i);
//    int len = convolution(da,n,db,n,da);
////
//    dispArray(da,len);
////    deBug(n);
//////    for (int i = 0;i < len;++i)a[i%n] += a[i];
////
//    init();
//    for (int i = 0;i < n;++i )cout << power[i] << endl;
////
////
//    llt ans = 0;
//    for (int i = 0;i < n;++i ){
//        ans += (c[i]*power[i]) % MOD;
//        ans %= MOD;
//    }
//    cout << ans<< endl;
//    return 0;
}
