#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 1e5 + 5;
int a[maxn], n, q, tp, dfn[maxn], pos[maxn], timer, inv[maxn], st[maxn], fa[maxn], sz[maxn], dep[maxn], son[maxn], top[maxn];
bool vis[maxn], imp[maxn];
vector<int>G[maxn];
vector<pii>F[maxn];
inline void Dfs1(int x) {
	// Ê÷ÆÊ
}
inline void Dfs2(int x) {
	// Ê÷ÆÊ 
}
inline int Lca(int x, int y) {
	// Çólca
}
inline int Cmp(int a, int b) {
	return dfn[a] < dfn[b];
}
inline int Isson(int a, int b) {
	return dfn[a] <= dfn[b] && dfn[b] <= inv[a];
}
inline void Add(int u, int v, int w) {
	F[u].push_back(pii(v, w));
}
int main() {
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; ++ i)
		scanf("%d%d", &x, &y), G[x].push_back(y), G[y].push_back(x);
	Dfs1(1), Dfs2(1), memset(sz, 0, sizeof sz);
	for(scanf("%d", &q); q --; ) {
		scanf("%d", &k), tp = 0;
		for(int i = 1; i <= k; ++ i)
			scanf("%d", &a[i]), vis[a[i]] = imp[a[i]] = 1;
		sort(a + 1, a + k + 1, Cmp);
		int p = k;
		for(int i = 1, lca; i < k; ++ i)
			if(!vis[lca = Lca(a[i], a[i + 1])])
				vis[a[++ p] = lca] = 1;
		sort(a + 1, a + p + 1, Cmp), st[++ tp] = a[1];
		for(int i = 2; i <= p; ++ i) {
			while(!Isson(st[tp], a[i]))
				-- tp;
			Add(st[tp], a[i], dep[a[i]] - dep[st[top]]), st[++ top] = a[i];
		}
		/*
			Write Code Here.
		*/
		for(int i = 1; i <= p; ++ i)
			vis[a[i]] = imp[a[i]] = 0, F[a[i]].clear();
	}
}
