//#include <Complex>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define PI acos(-1)
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define varName(x) #x
#define deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
const int SIZE = 200050;

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
int convolution ( char const a[],int n1,char const b[],int n2,int *c ){
    /**< fft需要补足到2的整次幂 */
    int bini_len = 1;
    while ( bini_len < n1*2 || bini_len < n2*2 ) bini_len <<= 1;

    for (int i = 0;i < n1;++i )
//        x1[i] = Complex( a[n1-i-1]-'0',0);
        x1[i].real = a[n1-i-1]-'0' , x1[i].imag = 0 ;

    for (int i = n1;i < bini_len;++i ) x1[i].real = x1[i].imag = 0 ;

    for (int i = 0;i < n2;++i )
//        x2[i] = Complex( b[n2-i-1] -'0',0);
        x2[i].real = b[n2-i-1] -'0' , x2[i].imag = 0 ;

    for (int i = n2;i < bini_len;++i ) x2[i].real = x2[i].imag = 0 ;

    DIT_FFT(x1,bini_len,1);
    DIT_FFT(x2,bini_len,1);

    for (int i = 0;i < bini_len;++i ) x1[i] = x1[i] * x2[i];

    DIT_FFT(x1,bini_len,-1);

    for (int i = 0 ;i < bini_len;++i )
        c[i] = (int)(x1[i].real+0.5);
    return bini_len;
}

char str1[SIZE];
char str2[SIZE];
int nub1[SIZE];
int nub2[SIZE];
int nub3[SIZE];

int main()
{
    while ( gets(str1) ){
        gets(str2);

        int len1 = strlen(str1);
        int len2 = strlen(str2);

        int len = convolution(str1,len1,str2,len2,nub3);

        int len3 = len1+len2-1;
        for ( int i = 0;i < len-1;++i ){
            nub3[i+1] += nub3[i]/10;
            nub3[i] %= 10;
        }
        int s = len3;
        while( nub3[s]<=0 && s > 0 )s--;
        while(s >= 0 ) printf("%c",nub3[s--]+'0');
        puts("");
    }
    return 0;
}
