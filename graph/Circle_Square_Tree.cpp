#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10 ;
vector<int> G[maxn], T[maxn * 2] ;
int dfn[maxn], low[maxn], st[maxn], num, top, cnt ;
void addEdge (int u, int v) {
    G[u].push_back (v); G[v].push_back (u) ;
}
void treeAddEdge (int u, int v) {
    T[u].push_back (v); T[v].push_back (u) ;
}
void tarjan (int v) {
    dfn[v] = low[v] = ++ num ;
    st[++ top] = v ;
    for (int i = 0; i < G[v].size(); i ++) {
        int to = G[v][i] ;
        if (!dfn[to]) {
            tarjan (to) ;
            low[v] = min (low[v], low[to]) ;
            if (dfn[v] == low[to]) {
                ++ cnt ;
                for (int x = 0; x != to; -- top) {
                    x = st[top] ;
                    treeAddEdge (cnt, x) ;
                    //T[cnt].push_back (x) ;
                    //T[x].push_back (cnt) ;
                }
                treeAddEdge (cnt, v) ;
                //T[cnt].push_back (v); T[v].push_back (cnt) ;
            }
        } else {
            low[v] = min (low[v], dfn[to]) ;
        }
    }
}
int main() {
    int n, m ;
    scanf("%d%d", &n, &m) ;
    cnt = n ;
    for (int i = 1; i <= m; i ++) {
        int u, v ;
        scanf("%d%d", &u, &v) ;
        addEdge (u, v) ;
    }
    for (int i = 1; i <= n; i ++)
        if (!dfn[i]) tarjan (i), -- top ;
    return 0 ;
}
