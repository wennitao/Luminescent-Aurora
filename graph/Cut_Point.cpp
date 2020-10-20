#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10 ;
vector<int> G[maxn] ;
int dfn[maxn], low[maxn], st[maxn], num, root, top, cnt ;
bool cut[maxn] ;
vector<int> dcc[maxn] ;
void addEdge (int u, int v) {
    G[u].push_back (v) ;
    G[v].push_back (u) ;
}
void tarjan (int v) {
    dfn[v] = low[v] = ++ num ;
    st[++ top] = v ;
    if (v == root && G[v].size() == 0) {
        dcc[++ cnt].push_back (v) ;
        return ;
    }
    int flag = 0 ;
    for (int i = 0; i < G[v].size(); i ++) {
        int to = G[v][i] ; ;
        if (!dfn[to]) {
            tarjan (to) ;
            low[v] = min (low[v], low[to]) ;
            if (low[to] >= dfn[v]) {
                flag ++ ;
                if (v != root || flag > 1) cut[v] = true ;
                cnt ++ ;
                int z ;
                do {
                    z = st[top --] ;
                    dcc[cnt].push_back (z) ;
                } while (z != to) ;
                dcc[cnt].push_back (v) ;
            }
        } else {
            low[v] = min (low[v], dfn[to]) ;
        }
    }
}
int new_id[maxn], c[maxn] ; //新编号， 点属于的v-DCC编号
vector<int> new_G[maxn] ;
int main() {
    int n, m ;
    scanf("%d%d", &n, &m) ;
    for (int i = 1; i <= m; i ++) {
        int u, v ;
        scanf("%d%d", &u, &v) ;
        addEdge (u, v) ;
    }
    for (int i = 1; i <= n; i ++)
        if (!dfn[i]) root = i, tarjan (i) ;

    num = cnt ;
    for (int i = 1; i <= n; i ++)
        if (cut[i]) new_id[i] = ++ num ;
    for (int i = 1; i <= cnt; i ++)
        for (int j = 0; j < dcc[i].size(); j ++) {
            int x = dcc[i][j] ;
            if (cut[x]) {
                new_G[i].push_back (new_id[x]) ;
                new_G[new_id[x]].push_back (i) ;
            } else {
                c[x] = i ;
            }
        }
    return 0 ;
}
