#include <bits/stdc++.h>
using namespace std;
const int maxn = 11000000 + 10 ;
char s[maxn], str[maxn * 2] ;
int p[maxn * 2] ;
int main() {
    scanf("%s", s + 1) ;
    int len = strlen (s + 1) ;
    str[0] = '$' ;
    for (int i = 1; i <= len; i ++)
        str[i * 2 - 1] = '#', str[i * 2] = s[i] ;
    str[len * 2 + 1] = '#' ;
    for (int i = 1, mx = -1, id = 0; i <= len * 2 + 1; i ++) {
        if (mx > i) p[i] = min (p[2 * id - i], mx - i) ;
        else p[i] = 1 ;
        while (str[i + p[i]] == str[i - p[i]]) p[i] ++ ;
        if (i + p[i] > mx) {
            mx = i + p[i]; id = i ;
        }
    }
    int ans = 0 ;
    for (int i = 1; i <= 2 * len + 1; i ++) ans = max (ans, p[i]) ;
    printf("%d\n", ans - 1) ;
    return 0 ;
}
