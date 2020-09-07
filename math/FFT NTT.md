###前言

FFT(Fast Fourier Transfromation)，快速傅里叶变换，用于加速多项式乘法。

朴素乘法：$O(n^2)$。FFT：$O(nlogn)$

---

### 多项式的系数表示法与点值表示法

####系数表示法

一个$n-1$次$n$项多项式$f(x)$可以表示为$f(x) = \sum _{i = 0} ^{n - 1} a_i x^i$，也可以用每一项的系数来表示：

$f(x) = {a_0, a_1, \cdots, a_{n - 1}}$

#### 点值表示法

将多项式看成函数，把$n$个不同的$x$代入，得到$n$个$y$，在坐标系内就是$n$个不同的点。

由这$n$个点可以**唯一确定**该多项式，$n$个方程解$n$个未知数。

用$f(x) = \{(x_0, f (x_0)), (x_1, f(x_1)), \cdots, (x_{n - 1}, f(x _{n - 1}))\}$表示即为点值表示法。



两个点值表示的多项式相乘，只需要$O(n)$。

$f(x) \cdot g(x) = \{(x_0, f(x_0) \cdot g(x_0)), (x_1, f(x_1) \cdot g(x_1)), \cdots, (x_{n - 1}, f (x_ {n - 1}) \cdot g(x_ {n - 1}))\}$

朴素的系数转点值的算法叫DFT(离散傅里叶变换)，朴素的点值转系数的算法叫IDFT(离散傅里叶逆变换)

---

### DFT

(从这开始的$n$都为2的整数幂次：$n = 2 ^ k$)

系数转点值可以随意选择$x$的值代入，但是暴力计算$f(x)$当然是$O(n^2)$的时间。

因此因选择特殊的$x$值代入，如0、1、-1等。

考虑代入一系列复数：$w_n ^k = cos \frac k n 2\pi + i sin \frac k n 2\pi$

其中$w _n ^1$称为$n$次单位根。$w _n ^k = (w _n ^1) ^k$

#### 单位根的一些性质

1. $w _n ^k = w _{2n} ^{2k}$
2. $w _n ^{k + \frac 2 n} = - w_n ^k$
3. $w_n ^0 = w _n ^ n$

---

### FFT

代入$w$的DFT可以通过分治减小复杂度，这就是FFT(快速傅里叶变换)。

设一个多项式$A(x)$

$A(x) = \sum  _{i = 0} ^{n - 1} a_i x^i = a_0 + a_1 x + a_2 x^2 + \cdots + a_{n - 1} x^{n - 1}$

将系数下标按照奇偶数分开：

$\begin {align} A(x) &= (a_0 + a_2 x^2 + \cdots + a_{n - 2} x^{n - 2}) + (a_1x + a_3x^3 + \cdots + a_{n - 1} x^{n - 1}) \\ &= (a_0 + a_2 x^2 + \cdots + a_{n - 2} x^{n - 2}) + x(a_1 + a_3x^2 + \cdots + a_{n - 1} x^{n - 2}) \end {align}$ 

设$A_1(x) = a_0 + a_2x + a_4x^2 + \cdots + a_{n - 2} x^{\frac n 2 -1}$，$A_2 (x) = a_1 + a_3x + a_5x^2 + \cdots + a_{n - 1} x^{\frac n 2 - 1}$

则$A(x) = A_1(x^2) + xA_2 (x^2)$

设$k \lt \frac n 2$，把$w _n ^k$代入：

$\begin {align} A(w_n ^k) &= A_1((w_n^k)^2) + w_n^k A_2((w_n ^k) ^2) \\ \\ &= A_1(w_n ^{2k}) + w_n^k A_2(w_n ^{2k}) \\ \\ &= A_1(w_{\frac n 2} ^k) + w_n^k A_2 (w_{\frac n 2} ^k) \end {align}$

对于$A(w_n ^{k + \frac n 2})$：

$\begin {align} A(w_n ^{k + \frac n 2}) &= A_1((w_n ^{k + \frac n 2})^2) + w_n ^{k + \frac n 2} A_2((w_n ^{k + \frac n 2}) ^2) \\ \\ &= A_1(w_n ^{2k + n}) - w_n ^k A_2(w_n ^{2k + n}) \\ \\ &= A_1 (w_n^{2k}) - w_n^k A_2(w_n ^{2k}) \\ \\ &= A_1(w_ {\frac n 2} ^k) - w_n^k A_2(w_{\frac n 2} ^k) \end {align}$

发现$A(w_n ^k)$和$A(w_n ^{k + \frac n 2})$只有后面一个式子的符号不同。

因此，如果已经算出$A_1(w_ \frac n 2 ^k)$和$A_2 (w_ \frac n 2 ^k)$的值，即可算出$A(w_n ^k)$和$A(w_n ^{k + \frac n 2})$。于是就可以分治辣！

---

### IFFT

对两个多项式分别用FFT求出点值表示后，将两个点值表达式相乘得到乘积多项式的点值表达。

如何在$O(nlogn)$的时间将点值转换为系数？

一个结论：**一个多项式在分治的过程中乘上单位根的共轭复数，分治完每一项系数除以$n$即为原多项式的系数**

---

### 板子

~~~cpp
void fft (cp a[], int n, int f) {
    for (int i = 0, j = 0; i < n; i ++) {
        if (i > j) swap (a[i], a[j]) ;
        for (int t = n >> 1; (j ^= t) < t; t >>= 1) ;
    }
    static cp w[maxn] ;
    for (int i = 0; i <= n; i ++)
        w[i] = cp (cos (2 * PI * i / n), sin (2 * PI * i / n)) ;
    for (int i = 2; i <= n; i <<= 1)
        for (int j = 0; j < n; j += i)
            for (int k = 0; k < (i >> 1); k ++) {
                cp A = a[j + k], B = w[f ? n - n / i * k : n / i * k] * a[j + k + (i >> 1)] ;
                a[j + k] = A + B; a[j + k + (i >> 1)] = A - B ;
            }
}
int main() {
		fft (a, n, 0); fft (b, n, 0) ;
  	for (int i = 0; i < n; i ++) a[i] = a[i] * b[i] ;
  	fft (a, n, 1) ;
  	for (int i = 0; i < n; i ++) ans[i] = (int)round (a[i].real() / n) ;
  	return 0 ;
}
~~~

其中魔幻的一部分：

~~~cpp
for (int i = 0, j = 0; i < n; i ++) {
		if (i > j) swap (a[i], a[j]) ;
    for (int t = n >> 1; (j ^= t) < t; t >>= 1) ;
}
~~~

因为每次递归开栈速度很慢，因此可以先将原序列顺序变换好，按次序向上合并即可。

---

### NTT

NTT，快速数论变换，可以**取模**。

#### 原根

对于$g, p \in Z$，如果$g^i$ mod $p$ $1 \le i \le p - 1$的值各不相同，$g$称为$p$的原根。

常见模数：998244353、1004535809、469762049，它们的原根都是3。

#### NTT

在NTT中，用原根代替FFT中的单位根。共轭复数变为逆的幂次。最后除以$n$变为乘以$n$的逆元。

$w_n = g^\frac {k \cdot (p - 1)} {n}$

####板子

~~~cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
const int maxn = 1 << 20, mod = 998244353, g = 3 ;
ll ginv ;
ll a[maxn], b[maxn] ;
ll power (ll x, ll y) {
    ll res = 1 ;
    while (y) {
        if (y & 1) res = res * x % mod ;
        x = x * x % mod; y >>= 1 ;
    }
    return res ;
}
void ntt (ll a[], int n, int f) {
    for (int i = 0, j = 0; i < n; i ++) {
        if (i > j) swap (a[i], a[j]) ;
        for (int t = n >> 1; (j ^= t) < t; t >>= 1) ;
    }
    for (int i = 2; i <= n; i <<= 1) {
        ll wn = power (f ? ginv : g, (mod - 1) / i) ;
        for (int j = 0; j < n; j += i) {
            ll w = 1 ;
            for (int k = 0; k < (i >> 1); k ++, w = (w * wn) % mod) {
                ll A = a[j + k], B = w * a[j + k + (i >> 1)] % mod ;
                a[j + k] = (A + B) % mod; a[j + k + (i >> 1)] = (A - B + mod) % mod ;
            }
        }
    }
    if (f) {
        ll inv = power (n, mod - 2) ;
        for (int i = 0; i < n; i ++) a[i] = a[i] * inv % mod ;
    }
}
int c[maxn] ;
char s[maxn] ;
int main() {
    ginv = power (3, mod - 2) ;
    int n ;
    scanf("%d", &n) ;
    scanf("%s", s) ;
    for (int i = 0; i < n; i ++) a[i] = s[n - i - 1] - '0' ;
    scanf("%s", s) ;
    for (int i = 0; i < n; i ++) b[i] = s[n - i - 1] - '0' ;
    int m = n * 2 ;
    for (n = 1; n <= m; n <<= 1) ;
    ntt (a, n, 0); ntt (b, n, 0) ;
    for (int i = 0; i < n; i ++) a[i] = a[i] * b[i] % mod ;
    ntt (a, n, 1) ;
    for (int i = 0; i < n; i ++) c[i] = a[i] ;
    for (int i = 0; i < n; i ++) c[i + 1] += c[i] / 10, c[i] %= 10 ;
    while (!c[n - 1]) n -- ;
    for (int i = n - 1; i >= 0; i --) printf("%d", c[i]) ;
    printf("\n") ;
    return 0 ;
}
~~~



---

### 例题

####Luogu 1919 【模板】A*B Problem升级版（FFT快速傅里叶）

**题意：**计算两个$n$位10进制整数$a$和$b$的乘积。$n \le 60000$

**题解：**把每一位数字作为系数，做FFT。注意在数组中存储应从低位到高位。最后判断进位。

~~~cpp
#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cp ;
const double PI = acos (-1.) ;
const int maxn = 1 << 22 ;
cp A[maxn], B[maxn] ;
void fft (cp a[], int n, int f) {
    for (int i = 0, j = 0; i < n; i ++) {
        if (i > j) swap (a[i], a[j]) ;
        for (int t = n >> 1; (j ^= t) < t; t >>= 1) ;
    }
    static cp w[maxn] ;
    for (int i = 0; i <= n; i ++)
        w[i] = cp (cos (2 * PI * i / n), sin (2 * PI * i / n)) ;
    for (int i = 2; i <= n; i <<= 1)
        for (int j = 0; j < n; j += i)
            for (int k = 0; k < (i >> 1); k ++) {
                cp A = a[j + k], B = w[f ? n - n / i * k : n / i * k] * a[j + k + (i >> 1)] ;
                a[j + k] = A + B; a[j + k + (i >> 1)] = A - B ;
            }
}
int num[maxn] ;
char s[maxn] ;
int main() {
    int n ;
    cin >> n ;
    scanf("%s", s) ;
    for (int i = 0; i < n; i ++) A[i] = s[n - 1 - i] - '0' ;
    scanf("%s", s) ;
    for (int i = 0; i < n; i ++) B[i] = s[n - 1 - i] - '0' ;
    int m = n + n ;
    for (n = 1; n <= m; n <<= 1) ;
    fft (A, n, 0); fft (B, n, 0) ;
    for (int i = 0; i < n; i ++) A[i] = A[i] * B[i] ;
    fft (A, n, 1) ;
    for (int i = 0; i < n; i ++) num[i] = (int)round (A[i].real() / n) ;
    for (int i = 0; i < n; i ++) num[i + 1] += num[i] / 10, num[i] %= 10 ;
    while (!num[n - 1]) n -- ;
    for (int i = n - 1; i >= 0; i --) printf("%d", num[i]) ;
    printf("\n") ;
    return 0 ;
}
~~~

---

####bzoj4827 Hnoi2017 礼物

**题意：**给定两个环，每个位置上有个值。可以对第一个环上的每个值加$c$，并旋转第二个环(变换两个环之间位置的对应关系)，求两个环每个位置对应值的差的平方的最小值。$n \le 50000$，$c \le 100$

**题解：**即求$\sum _{i=1} ^n (x_i - y_{i + k} + c) ^2$

展开后得：$\sum _{i = 1} ^n x_i^2 + \sum _{i = 1} ^n y_{i + k} ^2 + nc^2 - 2\sum _{i=1} ^n x_iy_{i + k} + 2c\sum _{i = 1} ^ n x_i - 2c \sum _{i=1} ^n y_{i + k}$

除了$- 2\sum _{i=1} ^n x_iy_{i + k}$外，其余都为常数。($c$的范围很小，暴力枚举即可)

因此任务是如何快速计算$- 2\sum _{i=1} ^n x_iy_{i + k}$

发现将$y$翻转后得到$-2 \sum _{i=1} ^n x_i y_{n - i + 1 + k}$，即为以$x$和$y$作为系数的两个多项式乘积$x^{n + k + 1}$的系数。

于是将$y$翻转并接一份复制在最后，FFT后枚举$c$即可。

~~~cpp
#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cp ;
const double PI = acos (-1.) ;
const int maxn = 2e6 + 10 ;
cp a[maxn], b[maxn] ;
void fft (cp a[], int n, int f) {
    for (int i = 0, j = 0; i < n; i ++) {
        if (i > j) swap (a[i], a[j]) ;
        for (int t = n >> 1; (j ^= t) < t; t >>= 1) ;
    }
    static cp w[maxn] ;
    for (int i = 0; i <= n; i ++)
        w[i] = cp (cos (2 * PI * i / n), sin (2 * PI * i / n)) ;
    for (int i = 2; i <= n; i <<= 1)
        for (int j = 0; j < n; j += i)
            for (int k = 0; k < (i >> 1); k ++) {
                cp A = a[j + k], B = w[f ? n - n / i * k : n / i * k] * a[j + k + (i >> 1)] ;
                a[j + k] = A + B; a[j + k + (i >> 1)] = A - B ;
            }
}
int n, m ;
int s1[maxn], s2[maxn], s[maxn] ;
void pre () {
    int N = n - 1, M = n + n - 1 ;
    for (int i = 0; i <= N; i ++) a[i] = s1[i + 1] ;
    for (int i = 0; i <= N; i ++) b[i] = s2[n - i] ;
    for (int i = 0; i < n; i ++) b[i + n] = b[i] ;
    M += N ;
    for (N = 1; N <= M; N <<= 1) ;
    fft (a, N, 0); fft (b, N, 0) ;
    for (int i = 0; i < N; i ++) a[i] = a[i] * b[i] ;
    fft (a, N, 1) ;
    for (int i = 0; i <= M; i ++) s[i] = (int)round (a[i].real () / N) ;
}
int main() {
    scanf("%d%d", &n, &m) ;
    for (int i = 1; i <= n; i ++) scanf("%d", &s1[i]) ;
    for (int i = 1; i <= n; i ++) scanf("%d", &s2[i]) ;
    pre () ;
    int ssum1 = 0, ssum2 = 0, sum1 = 0, sum2 = 0, mx = -1e9 ;
    for (int i = 1; i <= n; i ++) {
        ssum1 += s1[i] * s1[i] ;
        ssum2 += s2[i] * s2[i] ;
        sum1 += s1[i]; sum2 += s2[i] ;
    }
    for (int i = n - 1; i < n + n; i ++) mx = max (mx, s[i]) ;
    int ans = 1e9 ;
    for (int c = -m; c <= m; c ++) {
        ans = min (ans, ssum1 + ssum2 + n * c * c + 2 * c * (sum1 - sum2) - 2 * mx) ;
    }
    cout << ans << endl ;
    return 0 ;
}
~~~

---

####bzoj 3527 力

**题意：**给定$n$个数$q_i$，$F_j = \sum _{i < j} \frac {q_iq_j} {(i-j)^2} - \sum _{i > j} \frac {q_iq_j} {(i-j)^2}$。令$E_i = F_i / q_i$，求$E_i$。

**题解：**$E_i = \sum _{j < i} \frac {q_j} {(i-j)^2} - \sum _{j > i} \frac {q_j} {(i-j)^2}$

前半部分用$q_1, q_2, \cdots, q_n$和$\frac 1 {1^2}, \frac 1 {2 ^2}, \cdots, \frac 1 {n^2}$做卷积。

后半部分用$q_n, q_{n-1}, \cdots, q_1$和$\frac 1 {1^2}, \frac 1 {2 ^2}, \cdots, \frac 1 {n^2}$做卷积。

相减即可。

~~~cpp
#include <bits/stdc++.h>
using namespace std;
typedef complex<double> cp ;
const double PI = acos (-1.) ;
const int maxn = 5e5 + 10 ;
cp a[maxn], b[maxn] ;
inline double sqr (double x) {return x * x ;}
void fft (cp a[], int n, int f) {
    for (int i = 0, j = 0; i < n; i ++) {
        if (i > j) swap (a[i], a[j]) ;
        for (int t = n >> 1; (j ^= t) < t; t >>= 1) ;
    }
    static cp w[maxn] ;
    for (int i = 0; i <= n; i ++)
        w[i] = cp (cos (2 * PI * i / n), sin (2 * PI * i / n)) ;
    for (int i = 2; i <= n; i <<= 1)
        for (int j = 0; j < n; j += i)
            for (int k = 0; k < (i >> 1); k ++) {
                cp A = a[j + k], B = w[f ? n - n / i * k : n / i * k] * a[j + k + (i >> 1)] ;
                a[j + k] = A + B; a[j + k + (i >> 1)] = A - B ;
            }
}
double q[maxn], ans[maxn] ;
int main() {
    int n ;
    scanf("%d", &n) ;
    for (int i = 1; i <= n; i ++) scanf("%lf", &q[i]) ;
    for (int i = 0; i < n; i ++) a[i] = q[i + 1] ;
    for (int i = 0; i < n; i ++) b[i] = (double)1.0 / sqr (i + 1) ;
    int N, M = 2 * n - 2 ;
    for (N = 1; N <= M; N <<= 1) ;
    fft (a, N, 0); fft (b, N, 0) ;
    for (int i = 0; i <= N; i ++) a[i] = a[i] * b[i] ;
    fft (a, N, 1) ;
    for (int i = 0; i < n; i ++) ans[i + 2] = a[i].real() / N ;
    for (int i = 0; i <= N; i ++) a[i] = cp (0, 0), b[i] = cp (0, 0) ;
    for (int i = 0; i < n; i ++) a[i] = q[n - i], b[i] = 1.0 / sqr (i + 1) ;
    fft (a, N, 0); fft (b, N, 0) ;
    for (int i = 0; i <= N; i ++) a[i] = a[i] * b[i] ;
    fft (a, N, 1) ;
    for (int i = 0; i < n; i ++) ans[n - i - 1] -= a[i].real() / N ;
    for (int i = 1; i <= n; i ++) printf("%.5lf\n", ans[i]) ;
    return 0 ;
}
~~~

---

#### bzoj3992 SDOI2015 序列统计

**题意**：求长度为$n$的数列，数列中每个数字属于集合$S$，所有数的乘积mod M等于$x$的数列数量。$n \le 10^9$，$M \le 8000$，且$M$为素数。

**题解**：首先列出$dp$方程：$f[i][j]$表示$i$个数字，mod M等于$j$的方案数。

$f[i - 1][k] \to f[i][k * s]$，$s \in S$

转移利用快速幂的思想，复杂度为$O(logn * M^2)$

关键在于如何优化转移$O(M^2)$

现在的转移：$f[i] * f[j] \to f[i * j]$

根据原根的性质：$g^i$对应$M$以内的每个数

因此将$dp$中的$f[i]$定义为mod M等于$g^i$的方案数

两个幂次相乘指数相加：$f[i] * f[j] \to f[i + j]$

于是就可以愉快地NTT优化辣！

~~~cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;
const int maxn = 1e5 + 10, mod = 1004535809 ;
int n, N, M, T, g = 3, ginv ;
int mp[maxn] ;
int a[maxn], b[maxn], f[maxn], s[maxn] ;
ll power (ll x, int y, int mod) {
    ll res = 1 ;
    while (y) {
        if (y & 1) res = res * x % mod ;
        x = x * x % mod; y >>= 1 ;
    }
    return res ;
}
int getg (int n) {
    int tmp = n - 1 ;
    vector<int> v ;
    for (int i = 2; i * i <= tmp; i ++) {
        if (tmp % i == 0) {
            v.push_back (i) ;
            while (tmp % i == 0) tmp /= i ;
        }
    }
    if (tmp > 1) v.push_back (tmp) ;
    for (int i = 2; i <= n - 1; i ++) {
        bool flag = 1 ;
        for (int j = 0; j < v.size(); j ++)
            if (power (i, (n - 1) / v[j], n) == 1) {
                flag = 0; break ;
            }
        if (flag) return i ;
    }
    return -1 ;
}
void init () {
    int prm = getg (M) ;
    for (int i = 0; i < M - 1; i ++)
        mp[power (prm, i, M)] = i ;
    ginv = power (g, mod - 2, mod) ;
}
void ntt (int *a, int n, int f) {
    for (int i = 0, j = 0; i < n; i ++) {
        if (i > j) swap (a[i], a[j]) ;
        for (int t = n >> 1; (j ^= t) < t; t >>= 1) ;
    }
    for (int i = 2; i <= n; i <<= 1) {
        int wn = power (f ? ginv : g, (mod - 1) / i, mod) ;
        for (int j = 0; j < n; j += i) {
            int w = 1 ;
            for (int k = 0; k < (i >> 1); k ++, w = 1ll * w * wn % mod) {
                int A = a[j + k], B = 1ll * w * a[j + k + (i >> 1)] % mod ;
                a[j + k] = (A + B) % mod; a[j + k + (i >> 1)] = (A - B + mod) % mod ;
            }
        }
    }
    if (f) {
        int inv = power (n, mod - 2, mod) ;
        for (int i = 0; i < n; i ++)
            a[i] = 1ll * a[i] * inv % mod ;
    }
}
void cal (int *a1, int *a2, int *res) {
    memset (a, 0, sizeof a) ;
    memset (b, 0, sizeof b) ;
    for (int i = 0; i < M - 1; i ++) a[i] = a1[i] ;
    for (int i = 0; i < M - 1; i ++) b[i] = a2[i] ;
    ntt (a, N, 0); ntt (b, N, 0) ;
    for (int i = 0; i < N; i ++) a[i] = 1ll * a[i] * b[i] % mod ;
    ntt (a, N, 1) ;
    for (int i = 0; i < M - 1; i ++) res[i] = (a[i] + a[i + M - 1]) % mod ;
}
int main() {
    int x ;
    scanf("%d%d%d%d", &n, &M, &x, &T) ;
    init () ;
    for (int i = 1; i <= T; i ++) {
        int val ;
        scanf("%d", &val); val %= M ;
        if (val) f[mp[val]] ++ ;
    }
    s[mp[1]] = 1 ;
    int m = 2 * (M - 2) ;
    for (N = 1; N <= m; N <<= 1) ;
    while (n) {
        if (n & 1) cal (s, f, s) ;
        cal (f, f, f); n >>= 1 ;
    }
    printf("%d\n", s[mp[x]]) ;
    return 0 ;
}
~~~

