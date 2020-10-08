#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10, mod = 1e9 + 7 ;
typedef long long ll ;
int pr[maxn / 10], prcnt, N, lim, fp[maxn] ;
bool vis[maxn] ;
const int moha = 333331 ;
struct Hash {
	int next, ans; ll key ;
} mem[moha * 21], *tot = mem ;
int last[moha] ;

int S (int n, int k) {
	if (!k) return 1 ;
	if (n <= pr[k]) return n ;
	if (n < 1ll * pr[k] * pr[k])
		return S (n, k - 1) + n / pr[k] ;
	int ret ;
	ll key = 1ll * n * prcnt + k - 1 ;
	int pos = key % moha ;
	for (int iter = last[pos]; iter; iter = mem[iter].next)
		if (mem[iter].key == key)
			return mem[iter].ans ;
	ret = S (n, k - 1) + S (n / pr[k], k) ;
	*++ tot = (Hash) {last[pos], ret, key}; last[pos] = tot - mem ;
	return ret ;
}
inline int calc (int x, int p) {
	N = x; lim = (int) sqrt (x) ;
	memset (last, 0, sizeof last) ;
	tot = mem ;
	return S (x, fp[p]) ;
}
void init() {
	for (int i = 2; i < maxn; i ++) {
		if (!vis[i]) pr[++ prcnt] = i ;
		fp[i] = fp[i - 1] + !vis[i] ;
		for (int j = 1; j <= prcnt && i * pr[j] < maxn; ++ j) {
			vis[i * pr[j]] = 1 ;
			if (i % pr[j] == 0) break ;
		}
	}
}
inline int solve (int p, int n) {
	if (p == 1) return 1 ;
	return calc (n, p) ;
}
inline ll sub_mod (ll x, ll y, ll mod) {
	return (x - y + mod) % mod ;
}
inline ll pow_mod (ll a, ll n, ll m) {
	ll res = 1 ;
	for (a %= m; n; n >>= 1) {
		if (n & 1) res = res * a % m ;
		a = a * a % m ;
	}
	return res ;
}
pair<vector<ll>, vector<ll> >prime_count (ll n, ll k, ll mod) {
	auto pow_sum = [](ll n, ll k, ll mod) {
		if (k == 0) return n ;
		if (k == 1) return n * (n + 1) / 2 % mod ;
	} ;
	const ll v = static_cast<ll> (sqrt (n)) ;
	vector<ll> ssum (v + 1), lsum (v + 1) ;
	vector<bool> mark (v + 1) ;
	for (int i = 1; i <= v; i ++) {
		ssum[i] = pow_sum (i, k, mod) - 1 ;
		lsum[i] = pow_sum (n / i, k, mod) - 1 ;
	}
	for (ll p = 2; p <= v; ++ p) {
		if (ssum[p] == ssum[p - 1]) continue ;
		ll psum = ssum[p - 1], q = p * p, ed = min (v, n / q) ;
		ll pk = pow_mod (p, k, mod) ;
		int delta = (p & 1) + 1 ;
		for (int i = 1; i <= ed; i += delta)
			if (!mark[i]) {
				ll d = i * p ;
				if (d <= v) {
					lsum[i] = sub_mod (lsum[i], sub_mod (lsum[d], psum, mod) * pk % mod, mod) ;
				} else {
					lsum[i] = sub_mod (lsum[i], sub_mod (ssum[n / d], psum, mod) * pk % mod, mod) ;
				}
			}
		for (ll i = q; i <= ed; i += p * delta) mark[i] = 1 ;
		for (ll i = v; i >= q; i --) {
			ssum[i] = sub_mod (ssum[i], sub_mod (ssum[i / p], psum, mod) * pk % mod, mod) ;
		}
	}
	return {move (ssum), move (lsum)} ;
}
int main() {
	init () ;
	int T ;
	cin >> T ;
	while (T --) {
		int n, k ;
		scanf("%d%d", &n, &k) ;
		if (k < maxn)
			printf("%d\n", solve (k, n)) ;
		else {
			int ans = 0, pre = prime_count(k, 0, 1e9 + 7).second[1] ;
			for (int i = k + 1, j; i <= n; i = j + 1) {
				j = n / (n / i) ;
				auto it1 = prime_count (j, 0, 1e9 + 7);
				ans += (n / i) * (it1.second[1] - pre) ;
				pre = it1.second[1];
			}
			printf("%d\n", n - ans) ;
		}
	}
	return 0 ;
}
