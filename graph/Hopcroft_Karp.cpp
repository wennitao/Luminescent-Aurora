const int maxn = 1e5 + 10 ;
int dx[maxn], dy[maxn] ;
int matx[maxn], maty[maxn] ;
int bfs () {
    int flag = 0 ;
    for (int i = 1; i <= n; i ++) dy[i] = 0 ;
    queue<int> que ;
    for (int i = 1; i <= n; i ++) {
        dx[i] = 0 ;
        if (!matx[i]) que.push (l) ;
    }
    while (!que.empty()) {
        int x = que.front(); que.pop() ;
        for (int i = 0; i < G[x].size(); i ++) {
            int y = G[x][i] ;
            if (!dy[y]) {
                dy[y] = dx[x] + 1 ;
                if (!maty[y]) flag = 1 ;
                else {
                    dx[maty[y]] = dx[x] + 2 ;
                    que.push (maty[y]) ;
                }
            }
        }
    }
    return flag ;
}
int dfs (int x) {
    for (int i = 0; i < G[x].size(); i ++) {
        int y = G[x][i] ;
        if (dy[y] == dx[x] + 1) {
            dy[y] = 0 ;
            if (!maty[y] || dfs (maty[y])) {
                matx[x] = y, maty[y] = x ;
                return 1 ;
            }
        }
    }
    return 0 ;
}
void hopcroft () {
    for (int i = 1; i <= n; i ++)
        matx[i] = maty[i] = 0 ;
    while (bfs ()) {
        for (int i = 1; i <= n; i ++)
            if (!matx[i]) dfs (i) ;
    }
}
