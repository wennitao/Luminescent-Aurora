#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10 ;
vector<int> G[maxn], scc[maxn] ;
int dfn[maxn], low[maxn], st[maxn], ins[maxn], c[maxn] ;
int tot, num, top, cnt ;
void addEdge (int u, int v) {
    G[u].push_back (v) ;
}
void tarjan (int v) {
    dfn[v] = low[v] = ++ num ;
    st[++ top] = v; ins[v] = 1 ;
    for (int i = 0; i < G[v].size(); i ++) {
        int to = G[v][i] ;
        if (!dfn[to]) {
            tarjan (to) ;
            low[v] = min (low[v], low[to]) ;
        } else if (ins[to]) {
            low[v] = min (low[v], dfn[to]) ;
        }
    }
    if (dfn[v] == low[v]) {
        cnt ++; int y ;
        do {
            y = st[top --]; ins[y] = 0 ;
            c[y] = cnt; scc[cnt].push_back (y) ;
        } while (v != y) ;
    }
}
vector<int> cG[maxn] ;
int main() {
    int n, m ;
    scanf("%d%d", &n, &m) ;
    for (int i = 1; i <= m; i ++) {
        int u, v ;
        scanf("%d%d", &u, &v) ;
        addEdge (u, v) ;
    }
    for (int i = 1; i <= n; i ++)
        if (!dfn[i]) tarjan (i) ;

    for (int i = 1; i <= n; i ++) {
        for (int j = 0; j < G[i].size(); j ++) {
            int to = G[i][j] ;
            if (c[i] == c[to]) continue ;
            cG[c[i]].push_back (c[to]) ;
        }
    }
    return 0 ;
}
