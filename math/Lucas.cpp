#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
const int maxn = 1e5 + 10 ;
inline ll power (ll x, int y, int mod) {
    ll res = 1 ;
    while (y) {
        if (y & 1) res = res * x % mod ;
        x = x * x % mod; y >>= 1 ;
    }
    return res ;
}
int C (int n, int m, int mod) {
    if (n < m) return 0 ;
    ll res = 1 ;
    for (int i = n; i >= n - m + 1; i --) res = res * i % mod ;
    for (int i = m; i >= 2; i --) res = res * power (i, mod - 2, mod) % mod ;
    return res ;
}
int lucas (int n, int m, int mod) {
    if (n < mod && m < mod) return C (n % mod, m % mod, mod) ;
    return 1ll * lucas (n / mod, m / mod, mod) * C (n % mod, m % mod, mod) % mod ;
}
int main() {
    int T ;
    cin >> T ;
    while (T --) {
        int n, m, p ;
        scanf("%d%d%d", &n, &m, &p) ;
        printf("%d\n", lucas (n + m, m, p)) ;
    }
    return 0 ;
}
