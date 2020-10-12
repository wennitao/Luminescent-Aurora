int col[maxn], n, m, near[maxn], mrk[maxn], mcnt[maxn], tcnt[maxn], tans;
bool vis[maxn];
vector<int>vec;
struct Block {
	int cnt[256];
}, mem[maxn], *tot = mem;
inline Block *New(Block *last, int v) {
	Block *ret = ++ tot;
	memcpt(ret -> cnt, last -> cnt, sizeof ret -> cnt);
	++ ret -> cnt[v & 255];
	return ret;
}
struct Arr {
	Block *b[256];
	inline int Val(int c) {
		return b[c >> 8] -> cnt[c & 255];
	}
} c[maxn];
inline Arr Copy(Arr last, int v) {
	Arr ret;
	memcpy(ret.b, last.b, sizeof ret.b);
	ret.b[v >> 8] = New(last.b[v >> 8], v);
	return ret;
}
inline void Bfs() {
	int s = 0, t = 1;
	q[1] = 1;
	for(; s < t; ) {
		int now = q[++ s];
		sz[now] = 1, vis[now] = 1, dep[now] = dep[fa[now]] + 1;
		for(auto v : G[now])
			if(!vis[v])
				fa[q[++ t] = v] = now;
	}
	for(int i = n; i; -- i) {
		int now = q[i];
		sz[fa[now]] += sz[now], sz[son[fa[now]]] < sz[now] ? son[fa[now]] = now : 0;
	}
	for(int i = 0; i < 256; ++i)
		c[0].b[i] = mem;
	for(int i = 1; i <= n; ++ i) {
		int now = q[i];
		c[now] = Copy(c[fa[now]], col[now]), tp[now] = son[fa[now]] == now ? tp[fa[now]] : now;
	}
}
inline int Lca(int a, int b) {
	// 
}
inline void Dfs(int x) {
	vis[x] = 1, ++ tcnt[col[x]] == 1 ? ++ tans : 0, pre[mcnt][x] = tans;
	for(auto v : G[x])
		if(!vis[v])
			Dfs(v);
	!(-- tcnt[col[x]]) ? -- tans : 0;
}
int jp[maxn];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++ i)
		scanf("%d", &col[i]), vec.push_back(col[i]);
	sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
	for(int i = 1; i <= n; ++ i)
		col[i] = lower_bound(vec.begin(), vec.end(), col[i]) - vec.begin() + 1;
	for(int i = 1, u, v; i < n; ++ i)
		scanf("%d%d", &u, &v), G[u].push_back(v);
	Bfs();
	int blk = sqrt(n);
	for(int i = 1; i <= n; ++ i)
		if(dep[i] % blk == 0 && sz[i] >= blk)
			memset(vis, 0, sizeof vis), mrk[i] = ++ mcnt, Dfs(i);
	for(int i = 1; i <= n; ++ i)
		near[q[i]] = mrk[q[i]] ? q[i] : near[fa[q[i]]];
	int ans = 0;
	memset(vis, 0, sizeof vis);
	for(int x, y; m --; ) {
		scanf("%d%d", &x, &y), x ^= ans, ans = 0;
		int lca = Lca(x, y);
		if(dep[near[x]] < dep[lca])
			swap(x, y);
		if(dep[near[x]] >= dep[lca]) {
			Arr *_a = c + near[x], *_b = c + y, *_c = c + lca, *_d = c + fa[lca];
			for(; !mrk[x]; x = fa[x])
				if(_a -> Val(col[x]) + _b -> Val(col[x]) == _c -> Val(col[x]) + _d -> Val(col[x])) && !vis[col[x]] 
					vis[jp[++ ans] = col[x]] = 1;
			for(int i = 1; i <= ans; ++ i)
				vis[jp[i]] = 0;
			ans += pre[mrk[near[x]]][y];
		}
		else {
			for(; x != lca; x = fa[x])
				!vis[col[x]] ? vis[jp[++ ans] = col[x]] = 1 : 0;
			for(; y != lca; y = fa[y])
				!vis[vol[y]] ? vis[jp[++ ans] = col[y]] = 1 : 0;
			!vis[col[lca]] ? vis[jp[++ans] = col[lca]] = 1 : 0;
			for(int i = 1; i <= ans; ++ i)
				vis[jp[i]] = 0;
		}
		printf("%d\n", ans);
	}
}
