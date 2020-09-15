#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10 ;
int head[maxn], to[maxn * 2], nxt[maxn * 2] ;
int dfn[maxn], low[maxn], tot = 1, num ;
bool bridge[maxn * 2] ;
void addEdge (int u, int v) {
    to[++ tot] = v; nxt[tot] = head[u]; head[u] = tot ;
}
void tarjan (int v, int in_edge) {
    dfn[v] = low[v] = ++ num ;
    for (int i = head[v]; i; i = nxt[i]) {
        if (!dfn[to[i]]) {
            tarjan (to[i], i) ;
            low[v] = min (low[v], low[to[i]]) ;
            if (low[to[i]] > dfn[v]) bridge[i] = bridge[i ^ 1] = true ;
        } else if (i != (in_edge ^ 1))
            low[v] = min (low[v], dfn[to[i]]) ;
    }
}
int c[maxn], dcc ;
void dfs (int v) {
    c[v] = dcc ;
    for (int i = head[v]; i; i = nxt[i]) {
        if (c[to[i]] || bridge[i]) continue ;
        dfs (to[i]) ;
    }
}
vector<int> G[maxn] ;
int main() {
    int n, m ;
    scanf("%d%d", &n, &m) ;
    for (int i = 1; i <= m; i ++) {
        int u, v ;
        scanf("%d%d", &u, &v) ;
        addEdge (u, v); addEdge (v, u) ;
    }
    for (int i = 1; i <= n; i ++)
        if (!dfn[i]) tarjan (i, 0) ;
    for (int i = 1; i <= n; i ++)
        if (!c[i]) ++ dcc, dfs (i) ;
    printf("There are %d e-DCCs.\n", dcc) ;
    for (int i = 1; i <= n; i ++)
        printf("%d belongs to DCC %d.\n", i, c[i]) ;

    //边双连通分量缩点
    for (int i = 2; i <= tot; i ++) {
        int x = to[i ^ 1], y = to[i] ;
        if (c[x] == c[y]) continue ;
        G[c[x]].push_back (c[y]) ;
    }
    return 0 ;
}
