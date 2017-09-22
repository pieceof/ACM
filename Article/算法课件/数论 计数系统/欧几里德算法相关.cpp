typedef int int_t;

//�ǵݹ��gcd
int_t gcd(int_t a,int_t b){
    while( b ){
        int_t r = b;
        b = a % b;
        a = r;
    }
    return a;
}

//�ǵݹ����չŷ������㷨
//����a��b��gcd��ͬʱx��y����ax+by=gcd
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

//��a�����p����Ԫ��a��p���ʲŴ�����Ԫ
int_t inv(int_t a,int_t p){
    int_t x,y;
    int_t r = exEuclid(a,p,x,y);
    if ( r != 1 ) return 0;
    x = x % p;
    if ( x < 0 ) x += p;
    return x;
}

llt powerMod(llt a,llt b,llt MOD){
    llt ret = 1LL;
    a %= MOD;
    while( b ){
        if ( b & 1LL ) ret = ret * a % MOD,--b;
        b >>= 1LL;
        a = a * a % MOD;
    }
    return ret;
}
