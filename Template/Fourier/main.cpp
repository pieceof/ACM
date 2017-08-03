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

const int SIZE = 100500;
struct Complex{
    double real,image;
    Complex (double r = 0,double i = 0 ): real(r),image(i){}
    Complex operator + (const Complex &b) const{ return Complex(real+b.real,image+b.image);}
    Complex operator - (const Complex &b) const{ return Complex(real-b.real,image-b.image);}
    Complex operator * (const Complex &b) const{ return Complex(real*b.real-image*b.image,real*b.image+image*b.real);}
//    Complex operator + (const Complex &b) const{ return Complex(x-b.x,y-b.y);}
};

void Cal_Sort(Complex *A,int N){
    int LH = N/2 , j = LH,N1 = N-2;
    for (int i = 1; i <= N1 ;i++ ){
        if ( i < j ) swap( A[j] , A[i] );
        int k = LH ;
        while ( j >= k ) j -= k , k /= 2;
        j += k;
    }
}
void DIT_FFT( Complex *x ,int const &N ,bool DFFT){
    int M = log2(N);
    for ( int L = 1;L <= M; L++){
        int  B = 1 << (L-1);
        for (int J = 0; J <= B-1;J++ ){
            int P = J * ( 1 << (M-L) );
            double anger =  ( DFFT == 0 )? 2*PI*P/N : -2*PI*P/N ;
            Complex WnP( cos( anger) ,sin(-anger) );
            for ( int K = J;K <= N-1; K += (1<<L) ){
                Complex tmp = x[K];
                x[K] = x[K] + x[K+B] * WnP;
                x[K+B] = tmp - x[K+B] * WnP;
            }
        }
    }
    if ( DFFT == 1 )for(int i = 0 ;i < N;++i )
        x[i].real /= N , x[i].image /= N  ;
}

Complex x1[SIZE];
Complex x2[SIZE];
int convolution ( char const a[],int n1,char const b[],int n2,int *c ){
    /**< fft需要补足到2的整次幂 */
    int bini_len = 1;
    while ( bini_len < n1*2 || bini_len < n2*2 ) bini_len <<= 1;

    for (int i = 0;i < n1;++i )
//        x1[i] = Complex( a[n1-i-1]-'0',0);
        x1[i].real = a[n1-i-1]-'0' , x1[i].image = 0 ;
    for (int i = n1;i < bini_len;++i )
        x1[i].real = x1[i].image = 0 ;

    for (int i = 0;i < n2;++i )
//        x2[i] = Complex( b[n2-i-1] -'0',0);
        x2[i].real = b[n2-i-1] -'0' , x2[i].image = 0 ;
    for (int i = n2;i < bini_len;++i )
        x2[i].real = x2[i].image =  0 ;

    Cal_Sort(x1,bini_len);
    DIT_FFT(x1,bini_len,0);

    Cal_Sort(x2,bini_len);
    DIT_FFT(x2,bini_len,0);

    for (int i = 0;i < bini_len;++i ) x1[i] = x1[i] * x2[i];

    Cal_Sort(x1,bini_len);
    DIT_FFT(x1,bini_len,1);

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
//        deBug(str1);
//        deBug(str2);

        int len1 = strlen(str1);
        int len2 = strlen(str2);
//        reverse(str1,str1+len1);
//        reverse(str2,str2+len2);
//        for ( int i = 0;i < len1;++i )
//            nub1[i] = str1[len1-i-1] -'0';
//        for ( int i = 0;i < len2;++i )
//            nub2[i] = str2[len2-i-1] -'0';
//        CLEAR(nub3);
        int len = convolution(str1,len1,str2,len2,nub3);
//        for (int i = 0;i < len1+len2+2;++i )
//            cout << nub3[i] << " " ;
//        cout << endl;
        int len3 = len1+len2+1;
        for ( int i = 0;i < len;++i ){
            nub3[i+1] += nub3[i]/10;
            nub3[i] %= 10;
        }
        int s = len3;
        while( !nub3[s] && s > 0 )s--;
        while(s >= 0 ) printf("%c",nub3[s--]+'0');
        puts("");
    }
    return 0;
}
