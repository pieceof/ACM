#include "../../headers.h"

/// ------------------------------ code line ------------------------------//



typedef llt int_t;
/**< �ǵݹ��gcd */
int_t gcd(int_t a,int_t b){
    if (0L == a || 0L == b) return 1;
    if ( a < 0 ) a = -a;
    if ( b < 0 ) b = -b;
    while(b){
        int_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

/** \�ǵݹ����չŷ������㷨
 *����a��b��gcd��ͬʱx��y����ax+by=gcd
 */
int_t exEuclid(int_t a,int_t b,int_t&x,int_t&y){
    int_t x0 = 1, y0 = 0;
    int_t x1 = 0, y1 = 1;
    x = 0; y = 1;
    int_t r = a % b;
    int_t q = ( a - r ) / b;
    while( r ){
        x = x0 - q * x1;
        y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        a = b; b = r; r = a % b;
        q = ( a - r ) / b;
    }
    return b;
}
/**< ��a�����p����Ԫ��a��p���ʲŴ�����Ԫ */
int_t inv(int_t a,int_t p){
    int_t x,y , r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    return ( x < 0 ) ? x+p : x;
}

/**< ���ٳ�ȡģ */
int_t multiMod(int_t a,int_t b,int_t mod){
    int_t ret = 0LL;
    a %= mod;
    while( b ){
        if ( b & 1LL ) ret = ( ret + a ) % mod, --b;
        b >>= 1LL;
        a = ( a + a ) % mod;
    }
    return ret;
}
/**< ������ȡģ */
int_t Pow_Mod( int_t x,int_t n , int_t mod ){
    int_t ans = 1LL;
    x %= mod;
    while ( n ){
        if ( n & 1LL ) ans = multiMod(ans,x,mod); //ans = ans*x%mod;
        n >>= 1; x = multiMod(x,x,mod); //x = x*x%mod;
    }
    return ans;
}

/**<  Miller-Rabin����,����n�Ƿ�Ϊ���� */
bool Miller_Rabin(int_t n,int repeat){
    if ( 2LL == n || 3LL == n ) return true;
    if ( !( n & 1LL ) ) return false;

    /**< ��n�ֽ�Ϊ2^s*d */
    int_t d = n - 1LL;
    int s = 0;
    while( !( d & 1LL ) ) ++s, d>>=1LL;

    //srand((unsigned)time(0));
    for(int i=0;i<repeat;++i){ /**< �ظ�repeat��  */
        int_t a = rand() % ( n - 3 ) + 2;//ȡһ�������,[2,n-1)
        int_t x = Pow_Mod(a,d,n);
        int_t y = 0LL;
        for(int j=0;j<s;++j){
            y = multiMod(x,x,n);
            if ( 1LL == y && 1LL != x && n-1LL != x ) return false;
            x = y;
        }
        if ( 1LL != y ) return false;
    }
    return true;
}



/** \Pollard-Rho�����ֽ���������
 *  n == 1 ���� ����ѭ��
 *
 */
int const Repeat = 5; /**< Miller_Rabin ���Դ��� */
int_t Fac[100]; /**< �������ֽ������շ���ʱ������ģ� */
int FCnt; /**<  �������ĸ���������С���0��ʼ */
int_t Pollard_Rho(int_t n,int_t c){
    int_t k = 2;
    int_t x = rand() % n;
    int_t y = x;
    for (int_t i = 1;;i++){
        x = ( multiMod(x,x,n) - c ) % n;
        if ( x < 0 ) x += n;
        int_t d = gcd(y-x,n);
        if (d!=1LL && d!=n) return d;
        if (y == x) return n;
        if ( i == k ) y = x, k <<= 1;
    }
}
void Find_fac(int_t n){
    if ( Miller_Rabin(n,Repeat) ){
        Fac[FCnt++] = n;
        return;
    }
    int_t p;
    while( ( p = Pollard_Rho(n,rand()%(n-3)+3) ) == n );
    Find_fac(p);
    Find_fac(n/p);
}
/** \RSA
 *  ���������� p,q ;
 *  n = p*q ,  ��(n) = (p-1)*(q-1) ; ( ��(n) ��ŷ������ )
 *  ��Կ  e = ���ѡ��һ������e��������1< e < ��(n)����e���(n) ���ʡ�
 *  ��Կ  d = e���ڦ�(n)��ģ��Ԫ��
 *  ����  m -> C : ( m^e % n )
 *  ����  C -> m : ( c^d % n )
 */
inline int_t _encode( int_t m,int_t e,int_t n ){return Pow_Mod(m,e,n);}
inline int_t _decode( int_t C,int_t d,int_t n ){return Pow_Mod(C,d,n);}
void RSA( int_t p,int_t q,int_t e,int_t &nub,int l=0 ){
    int_t n = p*q;
    int_t fn = (p-1)*(q-1);
    int_t d = inv(e,fn);
//    for (int i = 0;i < l;++i )
//        nub[i] = _encode(nub[i],e,n);   /**< e�ǹ�Կ,���ڼ��� */
//        nub[i] = _decode(nub[i],d,n);   /**< d��˽Կ,���ڽ��� */
    nub = _decode(nub,d,n);
}

///========================================== code line ========================================//

const int SIZE = 1000000;
//llt nub[SIZE];
int main(){
    int t;scanf("%d",&t);while(t--){
        llt x;scanf("%lld",&x);
        if(Miller_Rabin(x,2))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
