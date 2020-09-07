#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10 ;
char s[maxn] ;
int n, m ;
int sa[maxn], rak[maxn], x[maxn], y[maxn], c[maxn] ;
inline void sa_init () {
    n = strlen (s + 1), m = 256 ;
    for (int i = 1; i <= n; i ++) c[x[i] = s[i]] ++ ;
    for (int i = 1; i <= m; i ++) c[i] += c[i - 1] ;
    for (int i = n; i; i --) sa[c[x[i]] --] = i ;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0 ;
        for (int i = n - k + 1; i <= n; i ++) y[++ num] = i ;
        for (int i = 1; i <= n; i ++)
            if (sa[i] > k) y[++ num] = sa[i] - k ;
        memset (c, 0, sizeof c) ;
        for (int i = 1; i <= n; i ++) c[x[i]] ++ ;
        for (int i = 1; i <= m; i ++) c[i] += c[i - 1] ;
        for (int i = n; i; i --) sa[c[x[y[i]]] --] = y[i], y[i] = 0 ;
        swap (x, y) ;
        x[sa[1]] = 1; num = 1 ;
        for (int i = 2; i <= n; i ++)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? num : ++ num) ;
        if (num == n) break; m = num ;
    }
    for (int i = 1; i <= n; i ++) rak[sa[i]] = i ;
}
int main() {
    scanf("%s", s + 1) ;
    sa_init () ;
    for (int i = 1; i <= n; i ++) printf("%d ", sa[i]) ;
    printf("\n") ;
    return 0 ;
}
