typedef long long ll ;
int ch[maxn][2] ;
struct node {
    ll val ;
    int sz ;
}t[maxn] ;
inline void update (int rt) {
    t[rt].sz = t[ch[rt][0]].sz + t[ch[rt][1]].sz + 1 ;
}
int merge (int a, int b) {
    if (!a || !b) return a + b ;
    if (a.val < b.val) swap (a, b) ;
    swap (ch[a][0], ch[a][1]) ;
    ch[a][1] = merge (ch[a][1], b) ;
    update (a) ;
    return a ;
}
