#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
inline int read() {
    int x = 0, f = 1; char c; c = getchar() ;
    while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar() ;
    return x * f ;
}
template <typename T> void print (T x) {
    if (x > 9) print (x / 10) ;
    putchar (x % 10 + '0') ;
}
template <typename T> inline void println (T x) {
    print (x); putchar('\n') ;
}
const int maxn = 3e5 + 10 ;
int ch[maxn][2], s[maxn], val[maxn], st[maxn], f[maxn] ;
bool r[maxn] ;
inline bool nroot (int x) {
    return ch[f[x]][0] == x || ch[f[x]][1] == x ;
}
inline void pushup (int x) {
    s[x] = s[ch[x][0]] ^ s[ch[x][1]] ^ val[x] ;
}
inline void pushr (int x) {
    swap (ch[x][0], ch[x][1]); r[x] ^= 1 ;
}
inline void pushdown (int x) {
    if (r[x]) {
        if (ch[x][0]) pushr (ch[x][0]) ;
        if (ch[x][1]) pushr (ch[x][1]) ;
        r[x] = 0 ;
    }
}
inline void rotate (int x) {
    int y = f[x], z = f[y], k = ch[y][1] == x, w = ch[x][!k] ;
    if (nroot (y)) ch[z][ch[z][1] == y] = x ;
    ch[x][!k] = y; ch[y][k] = w ;
    if (w) f[w] = y ;
    f[y] = x; f[x] = z ;
    pushup (y) ;
}
inline void splay (int x) {
    int y = x, top = 0 ;
    st[++ top] = y ;
    while (nroot (y)) st[++ top] = y = f[y] ;
    while (top) pushdown (st[top --]) ;
    while (nroot (x)) {
        y = f[x]; int z = f[y] ;
        if (nroot (y)) rotate ((ch[y][0] == x) ^ (ch[z][0] == y) ? x : y) ;
        rotate (x) ;
    }
    pushup (x) ;
}
inline void access (int x) {
    for (int y = 0; x; x = f[y = x]) {
        splay (x); ch[x][1] = y; pushup (x) ;
    }
}
inline void makeroot (int x) {
    access (x); splay (x); pushr (x) ;
}
inline int findroot (int x) {
    access (x); splay (x) ;
    while (ch[x][0]) pushdown (x), x = ch[x][0] ;
    splay (x); return x ;
}
inline void split (int x, int y) {
    makeroot (x); access (y); splay (y) ;
}
inline void link (int x, int y) {
    makeroot (x) ;
    if (findroot (y) != x) f[x] = y ;
}
inline void cut (int x, int y) {
    makeroot (x) ;
    if (findroot (y) == x && f[y] == x && !ch[y][0])
        f[y] = ch[x][1] = 0, pushup (x) ;
}
int main() {
    int n = read(), m = read() ;
    for (int i = 1; i <= n; i ++) val[i] = read() ;
    while (m --) {
        int op = read(), x = read(), y = read() ;
        if (op == 0) split (x, y), println (s[y]) ;
        else if (op == 1) link (x, y) ;
        else if (op == 2) cut (x, y) ;
        else splay (x), val[x] = y ;
    }
    return 0 ;
}
