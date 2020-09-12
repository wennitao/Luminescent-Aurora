#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10 ;
struct node {
    int val, rand, sz ;
}tree[maxn * 50] ;
int ch[maxn * 50][2], rt[maxn], tot = 0 ;
inline void pushup (int rt) {
    tree[rt].sz = tree[ch[rt][0]].sz + tree[ch[rt][1]].sz + 1 ;
}
inline int newnode (int val) {
    tree[++ tot].val = val; tree[tot].rand = rand() ;
    tree[tot].sz = 1 ;
    return tot ;
}
inline int copynode (int rt) {
    int x = newnode (0) ;
    tree[x] = tree[rt]; ch[x][0] = ch[rt][0]; ch[x][1] = ch[rt][1] ;
    return x ;
}
inline void split (int rt, int val, int &x, int &y) {
    if (!rt) {x = y = 0; return;}
    if (tree[rt].val <= val) x = copynode (rt), split (ch[x][1], val, ch[x][1], y), pushup (x);
    else y = copynode (rt), split (ch[y][0], val, x, ch[y][0]), pushup (y);
}
inline int merge (int x, int y) {
    if (!x || !y) return x + y ;
    if (tree[x].rand < tree[y].rand) {int p = copynode (x); ch[p][1] = merge (ch[p][1], y), pushup (p); return p ;}
    else {int p = copynode (y); ch[p][0] = merge (x, ch[p][0]), pushup (p); return p ;}
}
inline void del (int &rt, int val) {
    int x, y, z ;
    split (rt, val, x, y) ;
    split (x, val - 1, x, z) ;
    z = merge (ch[z][0], ch[z][1]) ;
    rt = merge (merge (x, z), y) ;
}
inline void insert (int &rt, int val) {
    int x, y, z ;
    split (rt, val, x, y) ;
    z = newnode (val) ;
    rt = merge (merge (x, z), y) ;
}
inline int getRank (int &rt, int val) {
    int x, y, z ;
    split (rt, val - 1, x, y) ;
    int res = tree[x].sz + 1 ;
    rt = merge (x, y) ;
    return res ;
}
inline int getVal (int &rt, int k) {
    if (tree[ch[rt][0]].sz + 1 == k) return tree[rt].val ;
    if (tree[ch[rt][0]].sz >= k) return getVal (ch[rt][0], k) ;
    else return getVal (ch[rt][1], k - tree[ch[rt][0]].sz - 1) ;
}
inline int getPre (int &rt, int val) {
    int x, y, z, res ;
    split (rt, val - 1, x, y) ;
    int k = tree[x].sz ;
    res = getVal (x, k) ;
    rt = merge (x, y) ;
    return res ;
}
inline int getNxt (int &rt, int val) {
    int x, y, z, res ;
    split (rt, val, x, y) ;
    res = getVal (y, 1) ;
    rt = merge (x, y) ;
    return res ;
}
int main() {
    int n ;
    cin >> n ;
    for (int i = 1; i <= n; i ++) {
        int v, opt, x ;
        scanf("%d%d%d", &v, &opt, &x) ;
        rt[i] = rt[v] ;
        if (opt == 1) insert (rt[i], x) ;
        if (opt == 2) del (rt[i], x) ;
        if (opt == 3) printf("%d\n", getRank (rt[i], x)) ;
        if (opt == 4) printf("%d\n", getVal (rt[i], x)) ;
        if (opt == 5) printf("%d\n", getPre (rt[i], x)) ;
        if (opt == 6) printf("%d\n", getNxt (rt[i], x)) ;
    }
    return 0 ;
}
