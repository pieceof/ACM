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
#define Anslld(x) printf("%lld\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
typedef long long llt;
const int SIZE = 500050;

//�����ṹ��
struct Complex{
    double real,imag;
    Complex(double r = 0.0,double i = 0.0):real(r),imag(i) {}
    Complex operator +(const Complex &b){ return Complex(real+b.real,imag+b.imag);}
    Complex operator -(const Complex &b){ return Complex(real-b.real,imag-b.imag);}
    Complex operator *(const Complex &b){ return Complex(real*b.real-imag*b.imag,real*b.imag+imag*b.real);}
};
/*
 * ����FFT��IFFTǰ�ķ�ת�任��
 * λ��i�� ��i�����Ʒ�ת��λ�ã�����
 * len����ȥ2����
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
    /**< fft��Ҫ���㵽2�������� */
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

    for (int i = 0;i < bini_len;++i ) x1[i] = x1[i] * x2[i];

    DIT_FFT(x1,bini_len,-1);

    for (int i = 0 ;i < bini_len;++i )
        c[i] = (T)(x1[i].real+0.5);
    return bini_len;
}

int t,n;
int nub[SIZE];
llt stick[SIZE];
llt sum[SIZE];
llt prifix[SIZE];
int main()
{
    scanf("%d",&t);
    while ( t-- ){
        scanf("%d",&n);
        CLEAR(stick);

        for (int i = 0;i < n;++i ){
            scanf("%d",nub+i);
            stick[ nub[i] ] ++;
        }
        sort(nub,nub+n);
        int maxlen = nub[n-1]+1;

        convolution(stick,maxlen,stick,maxlen,sum);


        for (int i = 0;i < n;++i ){
            sum[ nub[i] + nub[i] ] --;
        }
        int len = 2*nub[n-1];
        prifix[0] = 0;
        for (int i = 1;i <= len;++i ){
            sum[i] /= 2;
            prifix[i] = prifix[i-1] + sum[i];
        }

        llt ans = 0;
        for (int i = 0;i < n;++i ){
            /**< �ȼ������п��ܵ���� */
            ans += prifix[len] - prifix[nub[i]];
            /**< һ��һС�����*/
            ans -= (llt) ( n-1-i )*i;
            /**< ȥ�������������� */
            ans -= (llt) ( n-1);
            /**< ȥ�������߶�����nub[i]�����*/
            ans -= (llt) ( n-1-i)*(n-2-i) / 2;
        }
        llt tot = (llt)n*(n-1)*(n-2)/6;
        printf("%0.7f\n",(double)ans/tot);
//        Anslld(ans );

    }
    return 0;
}
