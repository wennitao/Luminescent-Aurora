#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<class T>inline void read(T &x) {
	x=0;T f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())x=x*10+ch-'0';
	x*=f;
}
const int maxn=2005,mod=998244353;
inline int Add(int x,int y) {
	return (x+=y)>=mod?x-mod:x;
}
inline int Sub(int x,int y) {
	return (x-=y)<0?x+mod:x;
}
inline int Mul(int x,int y) {
	return 1ll*x*y%mod;
}
inline int Pow(int x,int y=mod-2) {
	int res=1;
	for(;y;x=Mul(x,x),y>>=1)
		if(y&1)
			res=Mul(res,x);
	return res;
}
int n,k,x[maxn],y[maxn];
int main() {
	read(n),read(k);
	for(int i=1;i<=n;++i) {
		read(x[i]),read(y[i]);
		if(k==x[i])
			return 0*printf("%d\n",y[i]);
	}
	int ans=0;
	for(int i=1;i<=n;++i) {
		int fz=1,fm=1;
		for(int j=1;j<=n;++j)
			if(i!=j)
				fz=Mul(fz,Sub(k,x[j])),fm=Mul(fm,Sub(x[i],x[j]));
		ans=Add(ans,Mul(y[i],Mul(fz,Pow(fm))));
	}
	printf("%d\n",ans);
}
// 给定这 n 个点，请你确定这个多项式，并求出 f(k) mod 998244353 的值; 
