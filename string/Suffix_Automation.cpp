#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
const int maxn = 2e6 + 10 ;
int sz = 1, last = 1 ;
struct node {
    int len, link, nxt[26] ;
}st[maxn] ;
ll f[maxn] ;
inline void insert (int c) {
    int cur = ++ sz; f[cur] = 1 ;
    st[cur].len = st[last].len + 1 ;
    int p = last ;
    while (p && !st[p].nxt[c]) {
        st[p].nxt[c] = cur; p = st[p].link ;
    }
    if (!p) {
        st[cur].link = 1; last = cur; return ;
    }
    int q = st[p].nxt[c] ;
    if (st[p].len + 1 == st[q].len) {
        st[cur].link = q ;
    } else {
        int clone = ++ sz ;
        st[clone].len = st[p].len + 1 ;
        st[clone].link = st[q].link ;
        memcpy (st[clone].nxt, st[q].nxt, sizeof st[q].nxt) ;
        while (p && st[p].nxt[c] == q) {
            st[p].nxt[c] = clone; p = st[p].link ;
        }
        st[q].link = st[cur].link = clone ;
    }
    last = cur ;
}
char s[maxn] ;
int p[maxn], c[maxn] ;
int main() {
    scanf("%s", s + 1) ;
    int len = strlen (s + 1) ;
    for (int i = 1; i <= len; i ++) insert (s[i] - 'a') ;
    for (int i = 1; i <= sz; i ++) c[st[i].len] ++ ;
    for (int i = 1; i <= sz; i ++) c[i] += c[i - 1] ;
    for (int i = 1; i <= sz; i ++) p[c[st[i].len] --] = i ;
    for (int i = sz; i >= 1; i --) f[st[p[i]].link] += f[p[i]] ;
    ll ans = 0 ;
    for (int i = 1; i <= sz; i ++)
        if (f[i] != 1) ans = max (ans, f[i] * st[i].len) ;
    printf("%lld\n", ans) ;
    return 0 ;
}
