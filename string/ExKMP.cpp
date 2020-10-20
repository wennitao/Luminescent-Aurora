#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e7 + 10 ;
int nxt[maxn], extend[maxn], fail[maxn] ;
void get_next (char *s, int len) {
    fail[1] = 0 ;
    int p = 0 ;
    memset (nxt, 0, (len + 2) << 2) ;
    for (int i = 2; i <= len; i ++) {
        while (p && s[p + 1] != s[i]) p = fail[p] ;
        if (s[p + 1] == s[i]) p ++ ;
        fail[i] = p ;
        if (p > 0) nxt[i - p + 1] = max (nxt[i - p + 1], p) ;
    }
}
void get_extend (char *s, int lens, char *t, int lent) {
    get_next (t, lent) ;
    int a = 1, p = 0 ;
    for (int i = 1; i <= lens; i ++) {
        if (i + nxt[i - a + 1] - 1 >= p) {
            p = max (p, i - 1) ;
            while (p < lens && p - i + 1 < lent && s[p + 1] == t[p - i + 2]) ++ p ;
            a = i ;
            extend[i] = p - i + 1 ;
        } else {
            extend[i] = nxt[i - a + 1] ;
        }
    }
}
char s[maxn], t[maxn] ;
int main() {
    scanf("%s%s", s + 1, t + 1) ;
    int lens = strlen (s + 1), lent = strlen (t + 1) ;
    get_extend (s, lens, t, lent) ;
    return 0 ;
}
