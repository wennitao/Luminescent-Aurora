扩展Lucas定理用于求：$\binom n m \mod p$，其中$p$不一定为素数

---

首先对$p$进行素因数分解：$p = \prod _i p_i ^{k_i}$

显然$p_i^{k_i}$之间两两互素，因此如果能求出$\binom n m \mod p_i^{k_i}$，最后用中国剩余定理合并即可。

---

####如何求$\binom n m \mod p^k$

$\binom n m \mod p^k = \frac {n!} {m!(n-m)!} \mod p^k$

其中$n!$，$m!$，$(n-m)!$可能含有质因子$p$，不能直接求逆元

可以将三个式子中的质因子$p$提出，最后再乘回去：$\frac {\frac {n!} {p^{k_1}}} {\frac {m!} {p^{k_2}} \cdot \frac {(n-m)!} {p^{k_3}}} \cdot p^{k_1 - k_2-k_3}$

其中$\frac {m!} {p^{k_2}}$和$\frac {(n-m)!} {p^{k_3}}$可以直接求逆元

---

####如何求$\frac {n!} {p^a} \mod p^k$

假设$n=22$，$p=3$，$k=2$

$22! = 3^7 \times (1 \times 2 \times 3 \times 4 \times 5 \times 6 \times 7) \times (1 \times 2 \times 4 \times 5 \times 7 \times 8 \times 10 \times 11 \times 13 \times 14 \times 16 \times 17 \times 19 \times 20 \times 22)$

分成了三个部分：$p$的幂次，$\lfloor \frac n p \rfloor!$，第三部分是$n!$中和$p$互质的部分。

第一部分$p$的幂次会在最后被统计，因此不需要计算。

第二部分递归计算。

第三部分中可以发现：$1 \times 2 \times 4 \times 5 \times 7 \times 8 \equiv 10 \times 11 \times 13 \times 14 \times 16 \times 17 \mod p^k$

即$\prod _{i, (i, p) = 1} ^{p^k} i \equiv \prod _{i, (i, p) = 1} ^{p^k} (i + tp^k) \mod p^k$

$\prod _{i, (i, p) = 1} ^{p^k} i$ 循环了$\lfloor \frac n {p^k} \rfloor$次，暴力求后快速幂

最后还要乘上$19 \times 20 \times 22$，即$\prod _{i, (i, p) = 1} ^{n \mod p^k} i$，暴力求即可。

~~~cpp
inline ll fac (ll n, ll p, ll pk) {
    if (!n) return 1 ;
    ll res = 1 ;
    for (int i = 1; i < pk; i ++)
        if (i % p) res = res * i % pk ;
    res = power (res, n / pk, pk) ;
    for (int i = 1; i <= n % pk; i ++)
        if (i % p) res = res * i % pk ;
    return res * fac (n / p, p, pk) % pk ;
}
~~~

---

Luogu P4720 【模板】扩展卢卡斯

~~~cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
const int maxn = 1e6 + 10 ;
inline ll power (ll x, ll y, ll mod) {
    ll res = 1 ;
    while (y) {
        if (y & 1) res = res * x % mod ;
        x = x * x % mod; y >>= 1 ;
    }
    return res ;
}
inline void exgcd (ll a, ll b, ll &x, ll &y) {
    if (b != 0) {
        exgcd (b, a % b, y, x) ;
        y -= (a / b) * x ;
    } else {
        x = 1; y = 0 ;
    }
}
inline ll inv (ll a, ll mod) {
    ll x, y ;
    exgcd (a, mod, x, y) ;
    return (x % mod + mod) % mod ;
}
inline ll fac (ll n, ll p, ll pk) {
    if (!n) return 1 ;
    ll res = 1 ;
    for (int i = 1; i < pk; i ++)
        if (i % p) res = res * i % pk ;
    res = power (res, n / pk, pk) ;
    for (int i = 1; i <= n % pk; i ++)
        if (i % p) res = res * i % pk ;
    return res * fac (n / p, p, pk) % pk ;
}
inline ll C (ll n, ll m, ll p, ll pk) {
    if (n < m) return 0 ;
    ll f1 = fac (n, p, pk), f2 = fac (m, p, pk), f3 = fac (n - m, p, pk), cnt = 0 ;
    for (ll i = n; i; i /= p) cnt += i / p ;
    for (ll i = m; i; i /= p) cnt -= i / p ;
    for (ll i = n - m; i; i /= p) cnt -= i / p ;
    return f1 * inv (f2, pk) % pk * inv (f3, pk) % pk * power (p, cnt, pk) % pk ;
}
ll a[maxn], c[maxn] ;
int cnt ;
inline ll crt () {
    ll M = 1, res = 0 ;
    for (int i = 1; i <= cnt; i ++) M *= c[i] ;
    for (int i = 1; i <= cnt; i ++) res = (res + a[i] * (M / c[i]) % M * inv (M / c[i], c[i]) % M) % M ;
    return res ;
}
inline ll exlucas (ll n, ll m, ll p) {
    for (int i = 2; 1ll * i * i <= p && p > 1; i ++) {
        ll tmp = 1 ;
        while (p % i == 0) tmp *= i, p /= i ;
        if (tmp > 1) a[++ cnt] = C (n, m, i, tmp), c[cnt] = tmp ;
    }
    if (p > 1) a[++ cnt] = C (n, m, p, p), c[cnt] = p ;
    return crt () ;
}
int main() {
    ll n, m, mod ;
    scanf("%lld%lld%lld", &n, &m, &mod) ;
    printf("%lld\n", exlucas (n, m, mod)) ;
    return 0 ;
}
~~~

