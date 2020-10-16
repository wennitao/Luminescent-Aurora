#include <bits/stdc++.h>
#define lson l, m, rt * 2
#define rson m + 1, r, rt * 2 + 1
using namespace std;
const int maxn = 1e5 + 10 ;
const double eps = 1e-7 ;
int n = 1e5 ;
struct node {
    bool fl ;
    int id;
    double k, b ;
    void update (int _id, double _k, double _b) {id = _id, k = _k, b = _b;}
}t[maxn * 4] ;
inline double cal (double k, double b, int x) {
    return k * x + b ;
}
void modify (int id, double k, double b, int l, int r, int rt) {
    if (!t[rt].fl) {
        t[rt].fl = 1; t[rt].update (id, k, b); return ;
    }
    int m = (l + r) >> 1 ;
    double l1 = cal (t[rt].k, t[rt].b, l), r1 = cal (t[rt].k, t[rt].b, r) ;
    double l2 = cal (k, b, l), r2 = cal (k, b, r) ;
    if (l1 >= l2 && r1 >= r2) return ;
    if (l2 > l1 && r2 > r1) {
        t[rt].update (id, k, b); return ;
    }
    double x = (t[rt].b - b) / (k - t[rt].k) ;
    if (x <= m) {
        if (l1 > l2) modify (t[rt].id, t[rt].k, t[rt].b, lson), t[rt].update (id, k, b) ;
        else modify (id, k, b, lson) ;
    } else {
        if (l1 > l2) modify (id, k, b, rson) ;
        else modify (t[rt].id, t[rt].k, t[rt].b, rson), t[rt].update (id, k, b) ;
    }
}
void modify (int id, double k, double b, int L, int R, int l, int r, int rt) {
    if (L <= l && R >= r) {
        modify (id, k, b, l, r, rt); return ;
    }
    int m = (l + r) >> 1 ;
    if (L <= m) modify (id, k, b, L, R, lson) ;
    if (R > m) modify (id, k, b, L, R, rson) ;
}
double K[maxn], B[maxn] ;
void chkmax (int &a, int b, int x) {
    double ya = K[a] * x + B[a], yb = K[b] * x + B[b] ;
    if (ya < yb || (fabs (ya - yb) < eps && a > b)) a = b ;
}
int query (int x, int l, int r, int rt) {
    if (l == r) return t[rt].id ;
    int m = (l + r) >> 1, res = t[rt].id ;
    if (x <= m) chkmax (res, query (x, lson), x) ;
    else chkmax (res, query (x, rson), x) ;
    return res ;
}
int main() {
    int q, lastans = 0, tot = 0 ;
    scanf("%d", &q) ;
    while (q --) {
        int op ;
        scanf("%d", &op) ;
        if (op == 1) {
            int x0, y0, x1, y1 ;
            scanf("%d%d%d%d", &x0, &y0, &x1, &y1) ;
            x0 = (x0 + lastans - 1) % 39989 + 1 ;
            x1 = (x1 + lastans - 1) % 39989 + 1 ;
            y0 = (y0 + lastans - 1) % 1000000000 + 1 ;
            y1 = (y1 + lastans - 1) % 1000000000 + 1 ;
            if (x0 > x1) swap (x0, x1), swap (y0, y1) ;
            K[++ tot] = 1.0 * (y0 - y1) / (x0 - x1); B[tot] = y0 - K[tot] * x0 ;
            modify (tot, K[tot], B[tot], x0, x1, 1, n, 1) ;
        } else {
            int x ;
            scanf("%d", &x) ;
            x = (x + lastans - 1) % 39989 + 1 ;
            lastans = query (x, 1, n, 1) ;
            printf("%d\n", lastans) ;
        }
    }
    return 0 ;
}
