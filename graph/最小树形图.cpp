#include <bits/stdc++.h>
using namespace std;
const int maxn = 110, maxm = 1e4 + 10 ;
struct edge {
    int u, v, c ;
    edge () {}
    edge (int _u, int _v, int _c) {u = _u, v = _v, c = _c;}
}e[maxm] ;
int incost[maxn], pre[maxn], id[maxn], vis[maxn] ;
inline int zhuliu (int rt, int n, int m) {
    int res = 0, loopcnt, ecnt ;
    while (1) {
        for (int i = 1; i <= n; i ++)
            incost[i] = 1e9, pre[i] = id[i] = vis[i] = 0 ;
        ecnt = loopcnt = incost[rt] = 0 ;
        for (int i = 1; i <= m; i ++)
            if (incost[e[i].v] > e[i].c)
                incost[e[i].v] = e[i].c, pre[e[i].v] = e[i].u ;
        for (int i = 1; i <= n; i ++)
            if (incost[i] == 1e9) return -1 ;
        for (int i = 1; i <= n; i ++) {
            int v = i; res += incost[v] ;
            while (v != rt && vis[v] != i && !id[v]) vis[v] = i, v = pre[v] ;
            if (v != rt && !id[v]) {
                id[v] = ++ loopcnt ;
                for (int x = pre[v]; x != v; x = pre[x]) id[x] = loopcnt ;
            }
        }
        if (!loopcnt) return res ;
        for (int i = 1; i <= n; i ++)
            if (!id[i]) id[i] = ++ loopcnt ;
        for (int i = 1; i <= m; i ++)
            if (id[e[i].u] != id[e[i].v])
                e[++ ecnt] = edge (id[e[i].u], id[e[i].v], e[i].c - incost[e[i].v]) ;
        n = loopcnt; m = ecnt; rt = id[rt] ;
    }
    return res ;
}
int main() {
    int n, m, r ;
    scanf("%d%d%d", &n, &m, &r) ;
    for (int i = 1; i <= m; i ++) {
        int u, v, c ;
        scanf("%d%d%d", &u, &v, &c) ;
        e[i] = edge (u, v, c) ;
    }
    printf("%d\n", zhuliu (r, n, m)) ;
    return 0 ;
}
