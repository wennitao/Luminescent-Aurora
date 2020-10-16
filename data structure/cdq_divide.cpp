const int maxn = 1e5 + 10 ;
struct query {
    int x, y, id, opt, ans ;
}t[maxn], q[maxn] ;
void cdq (int l, int r) {
    if (l == r) return ;
    int m = (l + r) >> 1 ;
    cdq (l, m); cdq (m + 1, r) ;
    ++ now ;
    for (int i = l, j = m + 1; j <= r; j ++) {
        for (; i <= m && q[i].x <= q[j].x; i ++)
            if (!q[i].opt)
                update (); //前一半的操作对后一半答案的影响
        if (q[j].opt) q[j].ans = query (q[j].y) ;
    }
    int i, j, k = 0 ;
    for (i = l, j = m + 1; i <= m && j <= r; ) {
        if (q[i].x <= q[j].x) t[k ++] = q[i ++] ;
        else t[k ++] = q[j ++] ;
    }
    while (i <= m) t[k ++] = q[i ++] ;
    while (j <= r) t[k ++] = q[j ++] ;
    for (int i = 0; i < k; i ++)
        q[l + i] = t[i] ;
}
