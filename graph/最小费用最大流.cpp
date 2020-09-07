#include <bits/stdc++.h>
#define fi first
#define se second
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
typedef pair<int, int> P ;
const int maxn = 5010, INF = 0x3f3f3f3f ;
struct edge {
    int to, cap, cost, rev ;
    edge () {}
    edge (int _to, int _cap, int _cost, int _rev) {to = _to, cap = _cap, cost = _cost, rev = _rev;}
} ;
vector<edge> G[maxn] ;
inline void addEdge (int from, int to, int cap, int cost) {
    G[from].push_back (edge (to, cap, cost, G[to].size())) ;
    G[to].push_back (edge (from, 0, -cost, G[from].size() - 1)) ;
}
int dis[maxn], prevv[maxn], preve[maxn] ;
bool ins[maxn] ;
P min_cost_flow (int s, int t) {
    int flow = 0, res = 0 ;
    while (1) {
        memset (dis, 0x3f, sizeof dis) ;
        memset (ins, 0, sizeof ins) ;
        queue<int> que ;
        que.push (s); dis[s] = 0; ins[s] = 1 ;
        while (!que.empty()) {
            int v = que.front(); que.pop(); ins[v] = 0 ;
            for (int i = 0; i < G[v].size(); i ++) {
                edge e = G[v][i] ;
                if (e.cap > 0 && dis[e.to] > dis[v] + e.cost) {
                    dis[e.to] = dis[v] + e.cost ;
                    prevv[e.to] = v; preve[e.to] = i ;
                    if (!ins[e.to]) que.push (e.to), ins[e.to] = 1 ;
                }
            }
        }
        if (dis[t] == INF) return P (flow, res) ;
        int d = INF ;
        for (int v = t; v != s; v = prevv[v])
            d = min (d, G[prevv[v]][preve[v]].cap) ;
        flow += d; res += d * dis[t] ;
        for (int v = t; v != s; v = prevv[v]) {
            edge &e = G[prevv[v]][preve[v]] ;
            e.cap -= d ;
            G[v][e.rev].cap += d ;
        }
    }
}
int main() {
    int n = read(), m = read(), s = read(), t = read() ;
    for (int i = 1; i <= m; i ++) {
        int u = read(), v = read(), cap = read(), cost = read() ;
        addEdge (u, v, cap, cost) ;
    }
    P res = min_cost_flow (s, t) ;
    printf("%d %d\n", res.fi, res.se) ;
    return 0 ;
}
