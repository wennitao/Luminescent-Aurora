int sz ;
struct query {
    int l, r, id ;
    inline bool operator < const (const query &a) const {
        return l / sz != a.l / sz ? l < a.l : ((l / sz) & 1 ? r < a.r : r > a.r) ;
    }
}q[maxn] ;
int main() {
    sz = (int) sqrt (1.0 * n) ;
    sort (q + 1, q + m + 1) ;
    int l = 1, r = 0 ;
    for (int i = 1; i <= m; i ++) {
        while (r < q[i].r) add (++ r) ;
        while (r > q[i].r) del (r --) ;
        while (l < q[i].l) del (l ++) ;
        while (l > q[i].l) add (-- l) ;
    }
    return 0 ;
}
