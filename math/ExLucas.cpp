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
ll a[50], c[50] ;
int cnt = 0 ;
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
    ll n, m, p ;
    scanf("%lld%lld%d", &n, &m, &p) ;
    printf("%lld\n", exlucas (n, m, p)) ;
    return 0 ;
}
