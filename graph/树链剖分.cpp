#include <bits/stdc++.h>
#define lson l, m, rt * 2
#define rson m + 1, r, rt * 2 + 1
using namespace std;
typedef long long ll ;
inline ll read() {
    ll x = 0, f = 1; char c; c = getchar() ;
    while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar() ;
    return x * f ;
}
template <typename T> void print (T x) {
    if (x > 9) print (x / 10) ;
    putchar (x % 10 + '0') ;
}
template <typename T> inline void println (T x) {
    print (x); putchar('\n') ;
}
const int maxn = 1e5 + 10 ;
int n, m, rt, mod, dfn ;
int a[maxn] ;
int head[maxn], to[maxn * 2], nxt[maxn * 2], tot = 1 ;
int sz[maxn], dep[maxn], son[maxn], fa[maxn], top[maxn], id[maxn] ;
inline void addEdge (int u, int v) {
    to[++ tot] = v; nxt[tot] = head[u]; head[u] = tot ;
}
void dfs (int v) {
    sz[v] = 1; dep[v] = dep[fa[v]] + 1 ;
    for (int i = head[v]; i; i = nxt[i]) {
        if (to[i] == fa[v]) continue ;
        fa[to[i]] = v ;
        dfs (to[i]) ;
        sz[v] += sz[to[i]] ;
        if (sz[to[i]] > sz[son[v]]) son[v] = to[i] ;
    }
}
void dfs (int v, int tp) {
    top[v] = tp; id[v] = ++ dfn ;
    if (son[v]) dfs (son[v], tp) ;
    for (int i = head[v]; i; i = nxt[i]) {
        if (to[i] == fa[v] || to[i] == son[v]) continue ;
        dfs (to[i], to[i]) ;
    }
}
inline void Add (ll &x, ll y) {x = (x + y) % mod;}
ll sum[maxn * 4], add[maxn * 4] ;
inline void pushup (int rt) {
    sum[rt] = (sum[rt * 2] + sum[rt * 2 + 1]) % mod ;
}
inline void pushdown (int rt, int l, int r) {
    if (add[rt]) {
        int m = (l + r) >> 1 ;
        Add (sum[rt * 2], 1ll * (m - l + 1) * add[rt] % mod) ;
        Add (sum[rt * 2 + 1], 1ll * (r - m) * add[rt] % mod) ;
        Add (add[rt * 2], add[rt]) ;
        Add (add[rt * 2 + 1], add[rt]) ;
        add[rt] = 0 ;
    }
}
void update (int L, int R, ll val, int l, int r, int rt) {
    if (L <= l && R >= r) {
        Add (sum[rt], 1ll * (r - l + 1) * val) ;
        Add (add[rt], val) ;
        return ;
    }
    pushdown (rt, l, r) ;
    int m = (l + r) >> 1 ;
    if (L <= m) update (L, R, val, lson) ;
    if (R > m) update (L, R, val, rson) ;
    pushup (rt) ;
}
ll query (int L, int R, int l, int r, int rt) {
    if (L <= l && R >= r) return sum[rt] ;
    pushdown (rt, l, r) ;
    int m = (l + r) >> 1 ;
    ll res = 0 ;
    if (L <= m) Add (res, query (L, R, lson)) ;
    if (R > m) Add (res, query (L, R, rson)) ;
    return res ;
}
int main() {
    n = read(), m = read(), rt = read(), mod = read() ;
    for (int i = 1; i <= n; i ++) a[i] = read() % mod ;
    for (int i = 1; i < n; i ++) {
        int u = read(), v = read() ;
        addEdge (u, v); addEdge (v, u) ;
    }
    dfs (rt); dfs (rt, rt) ;
    for (int i = 1; i <= n; i ++) update (id[i], id[i], a[i], 1, n, 1) ;
    while (m --) {
        int op = read() ;
        if (op == 1) {
            int x = read(), y = read(); ll z = read() % mod ;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap (x, y) ;
                update (id[top[x]], id[x], z, 1, n, 1) ;
                x = fa[top[x]] ;
            }
            if (dep[x] > dep[y]) swap (x, y) ;
            update (id[x], id[y], z, 1, n, 1) ;
        } else if (op == 2) {
            int x = read(), y = read() ;
            ll ans = 0 ;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) swap (x, y) ;
                Add (ans, query (id[top[x]], id[x], 1, n, 1)) ;
                x = fa[top[x]] ;
            }
            if (dep[x] > dep[y]) swap (x, y) ;
            Add (ans, query (id[x], id[y], 1, n, 1)) ;
            println (ans) ;
        } else if (op == 3) {
            int x = read(); ll z = read() % mod ;
            update (id[x], id[x] + sz[x] - 1, z, 1, n, 1) ;
        } else {
            int x = read() ;
            println (query (id[x], id[x] + sz[x] - 1, 1, n, 1)) ;
        }
    }
    return 0 ;
}
