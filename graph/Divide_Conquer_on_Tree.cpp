#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10 ;
vector<int> G[maxn] ;
int root, son[maxn], sz[maxn], sum ;
bool vis[maxn] ;
void dfs_root (int v, int fa) {
    sz[v] = 1; son[v] = 0 ;
    for (int i = 0; i < G[v].size(); i ++) {
        int to = G[v][i] ;
        if (to == fa || vis[to]) continue ;
        dfs_root (to, v) ;
        sz[v] += sz[to] ;
        son[v] = max (son[v], sz[to]) ;
    }
    son[v] = max (son[v], sum - sz[v]) ;
    if (!root || son[v] < son[root]) root = v ;
}
void dfs_chain (int v, int fa) {
    // your code here

    for (int i = 0; i < G[v].size(); i ++) {
        int to = G[v][i] ;
        if (vis[to] || to == fa) continue ;
        dfs_chain (to, v) ;
    }
}
void calc (int v) {
    for (int i = 0; i < G[v].size(); i ++) {
        int to = G[v][i] ;
        if (vis[to]) continue ;
        dfs_chain (to, v) ;

        //your code here
    }
}
void work (int v) {
    vis[v] = 1 ;
    calc (v) ;
    for (int i = 0; i < G[v].size(); i ++) {
        int to = G[v][i] ;
        if (vis[to]) continue ;
        root = 0 ;
        sum = sz[to] ;
        dfs_root (to, 0) ;
        work (root) ;
    }
}
int main() {
    int n ;
    root = 0; sum = n ;
    dfs_root (1, 0) ;
    work (root) ;
    return 0 ;
}
