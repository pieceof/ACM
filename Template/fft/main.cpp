//#pragma comment(linker,"/STACK:102400000,102400000")
//#include <Complex>
#include <iostream>
#include <cmath>
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
const int MOD = 1004535809;


void dispArray( int const a[],int n ) {
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



class BigInteger{
private:
    const static int BASE = 10;
    const static char CharCase = '0';
    const static int INT_SIZE=SIZE;
public:
    int a[INT_SIZE];
//    int *a;
    int len;
//    ~BigInteger(){ delete a; }
    void clear(){ CLEAR(a); len = 1;}
    BigInteger(){ CLEAR(a); len = 1;}
    BigInteger(int x){
        len = 0;
        CLEAR(a);
        do{
            a[len++] = x%BASE;
            x/=BASE;
        }
        while(x);
    }
    BigInteger(char const str[],int slen){
        int s = 0;len = 0;
        while ( str[s] == '0' )s++;
        CLEAR(a);
        for (int i = slen-1;i >= s;--i )
            a[len++] = str[i] - '0';
        assert( len == slen-s);
    }
//    void operator += (const BigInteger&b)const{
//        this->len = max(this->len,b.len);
//        for (int i = 0;i < len;++i ){
//            a[i] += b[i];
//            a[i+1] += a[i] / BASE;
//            a[i] %= BASE;
//        }
//        if ( a[len] > 0 )len++;
//    }
    BigInteger operator + ( const BigInteger&x)const{
        BigInteger res;
        res.len = max(len,x.len);
        for ( int i = 0;i <= res.len;++i ){
            res.a[i] += ((i<len)?a[i]:0) + ((i<x.len)?x.a[i]:0);
            res.a[i+1] += res.a[i] / BASE;
            res.a[i] %= BASE;
        }
        if ( res.a[res.len] > 0 )res.len++;
        return res;
    }
    BigInteger operator * ( const BigInteger&x)const{
        BigInteger res;
        for (int i = 0;i < len;++i ){
            int up = 0;
            for (int j = 0 ;j < x.len;j++ ){
                int temp = a[i]*x.a[j] + res.a[i+j] + up;
                res.a[i+j] = temp%BASE;
                up = temp/BASE;
            }
            if ( up != 0 ) res.a[i+x.len] = up;
        }
        res.len = len+x.len;
        while( res.a[res.len-1] == 0 && res.len > 1 ) res.len--;
        return res;
    }
    void print(){for (int i = len-1;i > 0;i--)printf("%d",a[i]);printf("%d\n",a[0]); }

    BigInteger operator / ( int const&b )const{
        BigInteger ret;
        int down = 0;
        for (int i = len-1;i >= 0;i-- ){
            ret.a[i] = (a[i]+down*BASE)/b;
            down = a[i] + down*BASE - ret.a[i]*b;
        }
        ret.len=len;
        while ( ret.a[ret.len-1] == 0 && ret.len > 1)
            ret.len--;
        return ret;
    }

    BigInteger fast_multi( BigInteger const&x)const{
        BigInteger res;
        convolution(a,len+1,x.a,x.len+1,res.a);
        res.len = len+x.len+2;
//        for ( int i = 0;i <= res.len;++i ){
//            res.a[i+1] += res.a[i]/10;
//            res.a[i] %= 10;
//        }
        while( !res.a[res.len-1] && res.len > 1 )res.len--;
        return res;
    }
    int operator % (int const&m){
        int d=0;
        for (int i = len-1;i >= 0;i--)
            d = ((d*BASE)%m+a[i])%m;
        return d;
    }
    BigInteger operator ^ (llt b)const{
        assert(b>=0);
        if ( b==0 ) return 1;
        if ( b==1 ) return *this;
        BigInteger t = *this,ret(1);
        while ( b ){
            if ( b & 1LL ) ret = ret.fast_multi(t);
            b >>= 1;
            t = t.fast_multi(t);
        }
        return ret;
    }
    bool operator ==( BigInteger const&x )const{
        if ( len != x.len ) return false;
        for (int i = 0 ;i < len;++i )
            if ( a[i] != x.a[i] ) return false;
        return true;
    }
    bool operator < ( BigInteger const&x )const{
        int ln=len-1;
        if ( len != x.len ) return len < x.len;
        while ( a[ln] == x.a[ln] && ln >= 0 )ln--;
        if ( ln >= 0 && a[ln] < x.a[ln] ) return true;
        else return false;
    }
    bool operator <= ( BigInteger const&x )const{
        int ln=len-1;
        if ( len != x.len ) return len < x.len;
        while ( a[ln] == x.a[ln] && ln >= 0 )ln--;
        if ( ln >= 0 && a[ln] <= x.a[ln] ) return true;
        else return false;
    }
    BigInteger operator - (BigInteger const&T)const  //两个大数之间的相减运算
    {
        int i,j,big;
        bool flag;
        BigInteger t1,t2;
        if(T<*this)
            t1 =* this, t2 = T, flag = 0;
        else
            t1 = T,t2 = *this ,flag = 1;
        big = t1.len;
        for( i=0;i < big;i++ ){
            if(t1.a[i] < t2.a[i]){
                j=i+1;
                while( t1.a[j] == 0 )j++;
                t1.a[j--]--;
                while(j>i)t1.a[j--] += BASE-1;
                t1.a[i] += BASE - t2.a[i];
            }else t1.a[i] -= t2.a[i];
        }
        t1.len=big;
        while(t1.a[t1.len-1]==0 && t1.len>1)
            t1.len-- , big--;
        if(flag) t1.a[big-1] = 0-t1.a[big-1];
        return t1;
    }
};

const int _size = SIZE+SIZE;
int _unit[_size];

//int m,mod;
void vector_pow( int const a[] ,int n,int p,int *ret){
    assert(n>=1);
    for (int i = 0;i < n;++i )_unit[i] = ret[i] = a[i],
    p--;
    int len;
    while( p ){
        if ( p&1 ){
            len = convolution(ret,n,_unit,n,ret);
            for (int i = n;i < len;++i ) ret[i%n] += ret[i],ret[i];
            for (int i = 0;i < n;++i )   ret[i] %= MOD;

        }
        p >>= 1;
        len = convolution(_unit,n,_unit,n,_unit);
        for (int i = n;i < len;++i ) ret[i%n] += ret[i];
        for (int i = 0;i < n;++i )   ret[i] %= MOD;
    }
}
//int t,n;




int nub[SIZE];

int ans[SIZE];
//int cnt
int main()
{
    BigInteger a (12),b(12);
    a = a.fast_multi(b).fast_multi(b).fast_multi(b);
    a.print();
//    int n,m,x,s;
//    while ( scanf("%d%d%d%d",&n,&m,&x,&s) != EOF ){
//        CLEAR(nub);
//        int tmp;
//        for (int i = 0 ;i < s;++i ){
//            scanf("%d",&tmp);
//            nub[tmp]++;
//        }
//        CLEAR(ans);
//        vector_pow(nub,m,n,ans);
//        dispArray(ans,m+m);
//    }
    return 0;
}



