const int maxn = 1e5 + 10 ;
struct Dominator_Tree {
	int n, s, cnt ;
	int dfn[maxn], id[maxn], pa[maxn], semi[maxn], idom[maxn], p[maxn], mn[maxn] ;
	vector<int> G[maxn], dom[maxn], be[maxn] ;

    void addEdge (int u, int v) {
        G[u].push_back (v) ;
    }

	void dfs (int v) {
		dfn[v] = ++ cnt; id[cnt] = v ;
		for (auto to : G[v])
		{
			if (!dfn[to]) dfs(to), pa[dfn[to]] = dfn[v] ;
			be[dfn[to]].push_back (dfn[v]);
		}
	}

    int get (int v) {
        if (p[v] != p[p[v]]) {
            if (semi[mn[v]] > semi[get (p[v])]) mn[v] = get (p[v]) ;
            p[v] = p[p[v]] ;
        }
        return mn[v] ;
    }

    void LT () {
		for (int i = cnt; i > 1; i --)
		{
			for (auto j : be[i]) semi[i] = min (semi[i], semi[get (j)]) ;
			dom[semi[i]].push_back (i) ;
			int x = p[i] = pa[i] ;
			for (auto j : dom[x])
				idom[j] = (semi[get (j)] < x ? get(j) : x) ;
			dom[x].clear() ;
		}
		for (int i = 2; i <= cnt; i ++) {
			if (idom[i] != semi[i]) idom[i] = idom[idom[i]] ;
			dom[id[idom[i]]].push_back (id[i]) ;
		}
	}

	void build() {
		for (int i = 1; i <= n; i ++)
			dfn[i] = 0, dom[i].clear(), be[i].clear(), p[i] = mn[i] = semi[i] = i ;
		cnt = 0; dfs(s); LT();
	}
};
