#include <bits/stdc++.h>
using namespace std;
const int maxn = 2010 ;
const double eps = 1e-8 ;
int cnt, fail[maxn] ;
double val[maxn], delta[maxn] ;
vector<double> ans[maxn] ;
int main() {
    int n ;
    scanf("%d", &n) ;
    for (int i = 1; i <= n; i ++) scanf("%lf", &val[i]) ;
    for (int i = 1; i <= n; i ++) {
        double tmp = val[i] ;
        for (int j = 0; j < ans[cnt].size(); j ++)
            tmp -= ans[cnt][j] * val[i - j - 1] ;
        delta[i] = tmp ;
        if (fabs (delta[i]) < eps) continue ;
        fail[cnt] = i ;
        if (cnt == 0) {
            ans[++ cnt].resize (i); continue ;
        }
        double mul = delta[i] / delta[fail[cnt - 1]] ;
        cnt ++; ans[cnt].resize (i - fail[cnt - 2] - 1) ;
        ans[cnt].push_back (mul) ;
        for (int j = 0; j < ans[cnt - 2].size(); j ++)
            ans[cnt].push_back (ans[cnt - 2][j] * -mul) ;
        if (ans[cnt].size() < ans[cnt - 1].size()) ans[cnt].resize (ans[cnt - 1].size()) ;
        for (int j = 0; j < ans[cnt - 1].size(); j ++)
            ans[cnt][j] += ans[cnt - 1][j] ;
    }
    for (int i = 0; i < ans[cnt].size(); i ++)
        printf("%lf ", ans[cnt][i]) ;
    printf("\n") ;
    return 0 ;
}
