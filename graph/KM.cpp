#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10 ;
const int INF = 0x3f3f3f3f ;
long long w[maxn][maxn] ;
long long lx[maxn], ly[maxn], lk[maxn] ;
long long vy[maxn], slk[maxn], pre[maxn] ;
long long KM (int n) {
	long long ans = 0 ;
	int x, py, p ;
	long long d ;
	for(int i = 1; i <= n; i++)
		lx[i] = ly[i] = 0, lk[i] = -1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			lx[i] = max (lx[i], w[i][j]) ;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++)
			slk[j] = INF, vy[j] = 0 ;
	    for (lk[py = 0] = i; lk[py] >= 0; py = p) {
            vy[py] = 1; d = INF; x = lk[py];
		    for (int y = 1; y <= n; y ++)
			    if (!vy[y]) {
				    if (lx[x] + ly[y] - w[x][y] < slk[y])
					    slk[y] = lx[x] + ly[y] - w[x][y], pre[y] = py ;
				    if (slk[y] < d) d = slk[y], p = y ;
			    }
            for (int y = 0; y <= n; y ++)
		        if (vy[y]) lx[lk[y]] -= d, ly[y] += d ;
			    else slk[y] -= d ;
        }
	   for (; py; py = pre[py]) lk[py] = lk[pre[py]] ;
    }
	for (int i = 1; i <= n; i ++)
		ans += lx[i] + ly[i] ;
	return ans ;
}
int main() {
    int n = 2 ;
    cout << KM (n) << endl ;
    return 0 ;
}
