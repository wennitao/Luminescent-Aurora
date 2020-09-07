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
const int maxn = 1e7 + 10 ;
int n, m ;
int prime[maxn], tot ;
bool vis[maxn] ;
void init () {
    vis[1] = 1 ;
    for (int i = 2; i <= n; i ++) {
        if (!vis[i]) prime[++ tot] = i ;
        for (int j = 1; j <= tot && i * prime[j] <= n; j ++) {
            vis[i * prime[j]] = 1 ;
            if (i % prime[j] == 0) break ;
        }
    }
}
int main () {
    n = read(), m = read() ;
    init () ;
    while (m --) printf("%s\n", vis[read()] ? "No" : "Yes") ;
    return 0 ;
}
