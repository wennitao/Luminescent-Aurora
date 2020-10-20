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
//求1-n最大素因子 <= p的数的个数
inline int solve (int p, int n) {
	if (p == 1) return 1 ;
	return calc (n, p) ;
}
