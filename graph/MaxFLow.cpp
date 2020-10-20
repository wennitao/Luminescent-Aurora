#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
inline int read() {
    int x = 0, f = 1; char c; c = getchar() ;
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
const int maxn = 1e4 + 10, maxm = 1e5 + 10 ;
struct edge {
    int to, cap, rev ;
    edge () {}
    edge (int _to, int _cap, int _rev) {to = _to, cap = _cap, rev = _rev;}
} ;
vector<edge> G[maxn] ;
int level[maxn], iter[maxn] ;
inline void addEdge (int from, int to, int cap) {
    G[from].push_back (edge (to, cap, G[to].size())) ;
    G[to].push_back (edge (from, 0, G[from].size() - 1)) ;
}
inline void bfs (int s) {
    memset (level, -1, sizeof level) ;
    queue<int> que ;
    que.push (s); level[s] = 0 ;
    while (!que.empty()) {
        int v = que.front(); que.pop() ;
        for (int i = 0; i < G[v].size(); i ++) {
            edge e = G[v][i] ;
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1 ;
                que.push (e.to) ;
            }
        }
    }
}
int dfs (int v, int t, int f) {
    if (v == t) return f ;
    for (int &i = iter[v]; i < G[v].size(); i ++) {
        edge &e = G[v][i] ;
        if (e.cap > 0 && level[e.to] > level[v]) {
            int d = dfs (e.to, t, min (f, e.cap)) ;
            if (d > 0) {
                e.cap -= d ;
                G[e.to][e.rev].cap += d ;
                return d ;
            }
        }
    }
    return 0 ;
}
inline int maxflow (int s, int t) {
    int flow = 0 ;
    for (;;) {
        bfs (s) ;
        if (level[t] < 0) return flow ;
        memset (iter, 0, sizeof iter) ;
        int f ;
        while ((f = dfs (s, t, 1e9)) > 0) flow += f ;
    }
    return flow ;
}
int main() {
    int n = read(), m = read(), s = read(), t = read() ;
    for (int i = 1; i <= m; i ++) {
        int u = read(), v = read(), c = read() ;
        addEdge (u, v, c) ;
    }
    println (maxflow (s, t)) ;
    return 0 ;
}
