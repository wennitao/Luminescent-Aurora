#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
inline int read() {
    int x = 0, f = 1; char c; c = getchar() ;
    while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar() ;
    return x * f ;
}
void print (int x) {
    if (x > 9) print (x / 10) ;
    putchar (x % 10 + '0') ;
}
inline void println (int x) {
    print (x); putchar('\n') ;
}
const int maxk = 64010, mod = 998244353;
int n, k ;
int f[maxk], a[maxk], now[maxk], res[maxk] ;
inline void mul (int x[], int y[]) {
    static int tmp[maxk] ;
    memset (tmp, 0, sizeof tmp) ;
    for (int i = 0; i < k; i ++)
        for (int j = 0; j < k; j ++)
            tmp[i + j] = (tmp[i + j] + 1ll * x[i] * y[j] % mod) % mod ;
    for (int i = 2 * k - 2; i >= k; i --) {
        for (int j = 1; j <= k; j ++)
            tmp[i - j] = (tmp[i - j] + 1ll * tmp[i] * a[j] % mod) % mod ;
        tmp[i] = 0 ;
    }
    for (int i = 0; i < k; i ++) x[i] = tmp[i] ;
}
int main() {
    freopen("1.in", "r", stdin) ;
    n = read(), k = read() ;
    for (int i = 1; i <= k; i ++) {
        f[i] = read() ;
        if (f[i] < 0) f[i] += mod ;
    }
    for (int i = 0; i < k; i ++) {
        a[i] = read() ;
        if (a[i] < 0) a[i] += mod ;
    }
    if (n <= k - 1) {
        printf("%d\n", a[n]); return 0 ;
    }
    n -= k - 1; res[0] = now[1] = 1 ;
    while (n) {
        if (n & 1) mul (res, now) ;
        mul (now, now); n >>= 1 ;
    }
    for (int i = k; i <= 2 * k - 2; i ++)
        for (int j = 1; j <= k; j ++)
            a[i] = (a[i] + 1ll * a[i - j] * f[j] % mod) % mod ;
    int ans = 0 ;
    for (int i = 0; i < k; i ++)
        ans = (ans + 1ll * a[k - 1 + i] * res[i] % mod) % mod ;
    printf("%d\n", ans) ;
    return 0 ;
}
