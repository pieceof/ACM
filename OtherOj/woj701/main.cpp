//
// Created by bitwater on 18-4-27.
//

#include<cstdio>

using namespace std;
typedef long long llt;


llt gcd(llt a, llt b) { return b == 0 ? a : gcd(b, a % b); }


/**< 直接求欧拉函数 */
llt phi(llt x) {
    llt tmp = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) x /= i;
            tmp /= i;
            tmp *= (i - 1);
        }
    }
    if (x > 1) tmp = tmp / x * (x - 1);
    return tmp;
}

/**< 快速幂取模 */
llt Pow_Mod(llt x, llt n, llt mod) {
    llt ans = 1;
    x %= mod;
    while (n) {
        if (n & 1LL) ans = ans * x % mod;
        n >>= 1;
        x = x * x % mod;
    }
    return ans;
}

llt Exp(llt x, llt m) {
    if (m == 1) return 0;
    if (x <= 2) return x % m;
    if (x == 3) return 9 % m;
    if (x == 4) return 262144 % m;
    if (gcd(x, m) == 1)
        return Pow_Mod(x, Exp(x - 1, phi(m)), m);
    else
        return Pow_Mod(x, Exp(x - 1, phi(m)) + phi(m), m);
}

int main() {
    llt n, m;
    while (scanf("%lld%lld", &n, &m) != EOF)
        printf("%lld\n", Exp(n, m));
    return 0;
}