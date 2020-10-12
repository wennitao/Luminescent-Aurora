#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10 ;
char s1[maxn], s2[maxn] ;
int nxt[maxn] ;
int main() {
	scanf("%s%s", s1, s2) ;
	nxt[0] = -1 ;
    int k = -1 ;
	for (int i = 1; i < s2.length(); i ++) {
		while (k > -1 && s2[i] != s2[k + 1]) k = nxt[k] ;
		if (s2[i] == s2[k + 1]) k ++ ;
		nxt[i] = k ;
	}
	k = -1 ;
	for (int i = 0; i < s1.length(); i ++) {
		while (k > -1 && s1[i] != s2[k + 1]) k = nxt[k] ;
		if (s1[i] == s2[k + 1]) k ++ ;
		if (k == s2.length() - 1) {
			printf("%d\n", i - s2.length() + 2) ;
			k = nxt[k] ;
		}
	}
	return 0 ;
}
