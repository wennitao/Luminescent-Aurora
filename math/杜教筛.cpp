#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
const int maxn = 5e6 + 10 ;
int prime[maxn], tot ;
ll mu[maxn], phi[maxn] ;
map<int, ll> sum_phi, sum_mu ;
bool vis[maxn] ;
void init () {
    mu[1] = phi[1] = 1 ;
    for (int i = 2; i < maxn; i ++) {
        if (!vis[i]) prime[++ tot] = i, phi[i] = i - 1, mu[i] = -1 ;
        for (int j = 1; j <= tot && i * prime[j] < maxn; j ++) {
            vis[i * prime[j]] = 1 ;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j] ;
                mu[i * prime[j]] = 0 ;
                break ;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1) ;
            mu[i * prime[j]] = -mu[i] ;
        }
    }
    for (int i = 1; i < maxn; i ++)
        phi[i] += phi[i - 1], mu[i] += mu[i - 1] ;
}
ll cal_phi (int n) {
    if (n < maxn) return phi[n] ;
    if (sum_phi.count (n)) return sum_phi[n] ;
    ll res = 1ll * n * (n + 1) / 2 ;
    for (int i = 2, nxt; i <= n; i = nxt + 1) {
        nxt = n / (n / i) ;
        res -= 1ll * (nxt - i + 1) * cal_phi (n / i) ;
    }
    return sum_phi[n] = res ;
}
ll cal_mu (int n) {
    if (n < maxn) return mu[n] ;
    if (sum_mu.count (n)) return sum_mu[n] ;
    ll res = 1 ;
    for (int i = 2, nxt; i <= n; i = nxt + 1) {
        nxt = n / (n / i) ;
        res -= 1ll * (nxt - i + 1) * cal_mu (n / i) ;
    }
    return sum_mu[n] = res ;
}
int main() {
    init () ;
    int T ;
    cin >> T ;
    while (T --) {
        int n ;
        scanf("%d", &n) ;
        printf("%lld %lld\n", cal_phi (n), cal_mu (n)) ;
    }
    return 0 ;
}
