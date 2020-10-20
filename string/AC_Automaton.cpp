#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10 ;
struct node {
    int fail, nxt[26] ;
}tree[maxn] ;
int cnt, f[maxn] ;
char s[maxn] ;
inline void insert () {
    int len = strlen (s + 1), p = 0 ;
    for (int i = 1; i <= len; i ++) {
        int c = s[i] - 'a' ;
        if (!tree[p].nxt[c]) tree[p].nxt[c] = ++ cnt ;
        p = tree[p].nxt[c] ;
    }
    f[p] ++ ;
}
inline void build () {
    queue<int> que ;
    for (int i = 0; i < 26; i ++)
        if (tree[0].nxt[i]) {
            tree[tree[0].nxt[i]].fail = 0 ;
            que.push (tree[0].nxt[i]) ;
        }
    while (!que.empty()) {
        int v = que.front(); que.pop() ;
        for (int i = 0; i < 26; i ++) {
            if (tree[v].nxt[i]) {
                tree[tree[v].nxt[i]].fail = tree[tree[v].fail].nxt[i] ;
                que.push (tree[v].nxt[i]) ;
            } else
                tree[v].nxt[i] = tree[tree[v].fail].nxt[i] ;
        }
    }
}
int main() {
    int n ;
    scanf("%d", &n) ;
    for (int i = 1; i <= n; i ++) {
        scanf("%s", s + 1) ;
        insert () ;
    }
    build () ;
    scanf("%s", s + 1) ;
    int len = strlen (s + 1), p = 0, ans = 0 ;
    for (int i = 1; i <= len; i ++) {
        p = tree[p].nxt[s[i] - 'a'] ;
        for (int v = p; v && ~f[v]; v = tree[v].fail) ans += f[v], f[v] = -1 ;
    }
    printf("%d\n", ans) ;
    return 0 ;
}
