#include <bits/stdc++.h>
#define lson l, m, t[rt].l
#define rson m + 1, r, t[rt].r
using namespace std;
const int maxn = 2e5 + 10 ;
struct node {
    int l, r, fa, dep ;
}t[maxn * 30] ;
int root[maxn * 30], tot, n ;
void build (int l, int r, int &rt) {
    rt = ++ tot ;
    if (l == r) {
        t[rt].fa = l; return ;
    }
    int m = (l + r) >> 1 ;
    build (lson); build (rson) ;
}
void merge (int last, int pos, int fa, int l, int r, int &rt) {
    rt = ++ tot; t[rt].l = t[last].l; t[rt].r = t[last].r ;
    if (l == r) {
        t[rt].fa = fa; t[rt].dep = t[last].dep ;
        return ;
    }
    int m = (l + r) >> 1 ;
    if (pos <= m) merge (t[last].l, pos, fa, lson) ;
    else merge (t[last].r, pos, fa, rson) ;
}
void update (int pos, int l, int r, int rt) {
    if (l == r) {
        t[rt].dep ++; return ;
    }
    int m = (l + r) >> 1 ;
    if (pos <= m) update (pos, lson) ;
    else update (pos, rson) ;
}
int query (int pos, int l, int r, int rt) {
    if (l == r) return rt ;
    int m = (l + r) >> 1 ;
    if (pos <= m) return query (pos, lson) ;
    else return query (pos, rson) ;
}
int find (int pos, int rt) {
    int now = query (pos, 1, n, rt) ;
    if (t[now].fa == pos) return now ;
    return find (t[now].fa, rt) ;
}
int main() {
    int m ;
    scanf("%d%d", &n, &m) ;
    build (1, n, root[0]) ;
    for (int i = 1; i <= m; i ++) {
        int op, a, b ;
        scanf("%d", &op) ;
        if (op == 1) {
            scanf("%d%d", &a, &b) ;
            root[i] = root[i - 1] ;
            int posx = find (a, root[i]), posy = find (b, root[i]) ;
            if (t[posx].fa == t[posy].fa) continue ;
            if (t[posx].dep > t[posy].dep) swap (posx, posy) ;
            merge (root[i - 1], t[posx].fa, t[posy].fa, 1, n, root[i]) ;
            if (t[posx].dep == t[posy].dep) update (t[posy].fa, 1, n, root[i]) ;
            posx = find (a, root[i]), posy = find (b, root[i]) ;
        } else if (op == 2) {
            scanf("%d", &a) ;
            root[i] = root[a] ;
        } else {
            scanf("%d%d", &a, &b) ;
            root[i] = root[i - 1] ;
            int posx = find (a, root[i]), posy = find (b, root[i]) ;
            printf("%d\n", t[posx].fa == t[posy].fa ? 1 : 0) ;
        }
    }
    return 0 ;
}
