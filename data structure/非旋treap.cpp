#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
inline int read() {
    int x = 0, f = 1; char c; c = getchar() ;
    while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar() ;
    return x * f ;
}
const int maxn = 1e5 + 10 ;
struct node {
    int val, rand, sz ;
}tree[maxn] ;
int ch[maxn][2], tot = 0, rt ;
inline void pushup (int rt) {
    tree[rt].sz = tree[ch[rt][0]].sz + tree[ch[rt][1]].sz + 1 ;
}
inline int newnode (int val) {
    tree[++ tot].val = val; tree[tot].rand = rand(); tree[tot].sz = 1 ;
    return tot ;
}
void split (int rt, int val, int &x, int &y) {
    if (!rt) {x = y = 0; return;}
    if (tree[rt].val <= val) x = rt, split (ch[x][1], val, ch[x][1], y) ;
    else y = rt, split (ch[y][0], val, x, ch[y][0]) ;
    pushup (rt) ;
}
int merge (int x, int y) {
    if (!x || !y) return x + y ;
    if (tree[x].rand < tree[y].rand) {ch[x][1] = merge (ch[x][1], y), pushup (x); return x;}
    else {ch[y][0] = merge (x, ch[y][0]), pushup (y); return y;}
}
inline void insert (int val) {
    int x, y, z ;
    split (rt, val, x, y) ;
    z = newnode (val) ;
    rt = merge (merge (x, z), y) ;
}
inline void del (int val) {
    int x, y, z ;
    split (rt, val, x, y) ;
    split (x, val - 1, x, z) ;
    z = merge (ch[z][0], ch[z][1]) ;
    rt = merge (merge (x, z), y) ;
}
inline int getRank (int val) {
    int x, y, z ;
    split (rt, val - 1, x, y) ;
    int res = tree[x].sz + 1 ;
    rt = merge (x, y) ;
    return res ;
}
int getVal (int rt, int k) {
    if (tree[ch[rt][0]].sz >= k) return getVal (ch[rt][0], k) ;
    if (tree[ch[rt][0]].sz + 1 == k) return tree[rt].val ;
    return getVal (ch[rt][1], k - tree[ch[rt][0]].sz - 1) ;
}
inline int getPre (int val) {
    int x, y, z ;
    split (rt, val - 1, x, y) ;
    int k = tree[x].sz ;
    int res = getVal (x, k) ;
    rt = merge (x, y) ;
    return res ;
}
inline int getNext (int val) {
    int x, y, z ;
    split (rt, val, x, y) ;
    int res = getVal (y, 1) ;
    rt = merge (x, y) ;
    return res ;
}
int main() {
    int n = read() ;
    while (n --) {
        int op = read(), x = read() ;
        if (op == 1) insert (x) ;
        else if (op == 2) del (x) ;
        else if (op == 3) printf ("%d\n", getRank (x)) ;
        else if (op == 4) printf ("%d\n", getVal (rt, x)) ;
        else if (op == 5) printf ("%d\n", getPre (x)) ;
        else printf ("%d\n", getNext (x)) ;
    }
    return 0 ;
}
