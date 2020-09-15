#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
bool Finish_read;
template<class T>inline void read(T &x){Finish_read=0;x=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;if(ch==EOF)return;ch=getchar();}while(isdigit(ch))x=x*10+ch-'0',ch=getchar();x*=f;Finish_read=1;}
template<class T>inline void print(T x){if(x/10!=0)print(x/10);putchar(x%10+'0');}
template<class T>inline void writeln(T x){if(x<0)putchar('-');x=abs(x);print(x);putchar('\n');}
template<class T>inline void write(T x){if(x<0)putchar('-');x=abs(x);print(x);}
/*================Header Template==============*/
const int fmaxn=18,Fmaxn=(1<<fmaxn)+1;
const double pi=acos(-1);
struct Complex {
	double Real,Image;
	#define x Real
	#define y Image
	Complex(double x=0,double y=0):x(x),y(y){}
	inline Complex operator + (const Complex &a) const {
		return Complex(x+a.x,y+a.y);
	}
	inline Complex operator - (const Complex &a) const {
		return Complex(x-a.x,y-a.y);
	}
	inline Complex operator * (const Complex &a) const {
		return Complex(x*a.x-y*a.y,x*a.y+y*a.x);
	}
	inline Complex operator * (const double &a) const {
		return Complex(x*a,y*a);
	}
	inline Complex operator / (const double &a) const {
		return Complex(x/a,y/a);
	}
};
namespace Transform {
	Complex root[fmaxn][Fmaxn],a[Fmaxn],b[Fmaxn];
	int rev[Fmaxn],mx;
	inline void DFT(Complex *a,int n) {
		if(mx<n) {
			for(int i=mx;i<n;++i) {
				int len=1<<i; 
				for(int j=0;j<len;++j)
					root[i][j]=Complex(cos(pi/len*j),sin(pi/len*j));
			}
			mx=n;
		}
		rev[0]=0;
		for(int i=0;i<(1<<n);++i) {
			rev[i]=i&1?rev[i^1]|(1<<(n-1)):rev[i>>1]>>1;
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		}
		for(int l=0;l<n;++l) {
			int len=(1<<l);
			for(int i=0;i<(1<<n);i+=(len<<1))
				for(int j=0;j<len;++j) {
					Complex x=a[i+j+len]*root[l][j];
					a[i+j+len]=a[i+j]-x,a[i+j]=a[i+j]+x;
				} 
		}
	}
	inline void IDFT(Complex *a,int n) {
		int len=1<<n;
		reverse(a+1,a+len);
		DFT(a,n);
		for(int i=0;i<len;++i)
			a[i]=a[i]/len;
	}
	inline void FFT(double *A,double *B,int lena,int lenb) { // [0,lena],[0,lenb],[0,lena+lenb] 
		int lim=0,l=1;
		while(l<lena+lenb+1)
			lim++,l<<=1;
		for(int i=0;i<=lena;++i)
			a[i]=Complex(A[i],0);
		for(int i=0;i<=lenb;++i)
			b[i]=Complex(B[i],0);
		for(int i=lena+1;i<l;++i)
			a[i]=Complex();
		for(int i=lenb+1;i<l;++i)
			b[i]=Complex();
		DFT(a,lim),DFT(b,lim);
		for(int i=0;i<l;++i)
			a[i]=a[i]*b[i];
		IDFT(a,lim);
		for(int i=0;i<=lena+lenb;++i)
			A[i]=a[i].x;
	}
}
int n,m;
double p[Fmaxn],q[Fmaxn];
int main() {
	read(n),read(m);
	for(int i=0;i<=n;++i)
		scanf("%lf",&p[i]);
	for(int i=0;i<=m;++i)
		scanf("%lf",&q[i]);
	Transform::FFT(p,q,n,m);
	for(int i=0;i<=n+m;++i)
		printf("%d ",int(p[i]+0.5));
}
