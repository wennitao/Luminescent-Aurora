#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10, maxm = 1e6 + 10 ;
int head[maxn], to[maxm], nxt[maxm], tot = 1 ;
int st[maxm], ans[maxm] ;
bool vis[maxm] ;
int top, t ;
void addEdge (int u, int v) {
    to[++ tot] = v; nxt[tot] = head[u]; head[u] = tot ;
}
void euler () {
    st[++ top] = 1 ;
    while (top > 0) {
        int x = st[top], i = head[x] ;
        while (i && vis[i]) i = nxt[i] ;
        if (i) {
            st[++ top] = to[i] ;
            vis[i] = vis[i ^ 1] = true ;
            head[x] = nxt[i] ;
        } else {
            top -- ;
            ans[++ t] = x ;
        }
    }
}
int main() {
    int n, m ;
    scanf("%d%d", &n, &m) ;
    for (int i = 1; i <= m; i ++) {
        int u, v ;
        scanf("%d%d", &u, &v) ;
        addEdge (u, v); addEdge (v, u) ;
    }
    euler () ;
    for (int i = t; i; i --) printf("%d ", ans[i]) ;
    puts ("") ;
    return 0 ;
}
