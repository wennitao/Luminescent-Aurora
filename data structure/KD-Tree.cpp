#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
bool Finish_read;
template<class T>inline void read(T &x){Finish_read=0;x=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;if(ch==EOF)return;ch=getchar();}while(isdigit(ch))x=x*10+ch-'0',ch=getchar();x*=f;Finish_read=1;}
template<class T>inline void print(T x){if(x/10!=0)print(x/10);putchar(x%10+'0');}
template<class T>inline void writeln(T x){if(x<0)putchar('-');x=abs(x);print(x);putchar('\n');}
template<class T>inline void write(T x){if(x<0)putchar('-');x=abs(x);print(x);}
/*================Header Template==============*/
const int maxn=1000006,inf=1e7;
int nty,n,ans,m,rt,tot;
struct Point {
	int x,y;
	Point(int x=0,int y=0):x(x),y(y){}
	inline void Read() {
		read(x),read(y);
	}
	inline bool operator < (const Point &rhs) const {
		return nty?(y==rhs.y?x<rhs.x:y<rhs.y):(x==rhs.x?y<rhs.y:x<rhs.x);
	}
	inline int Calc(const Point &rhs) {
		return abs(x-rhs.x)+abs(y-rhs.y);
	}
}p[maxn];
struct Data {
	int maxx,minx,maxy,miny;
	Data(int a=0,int b=0,int c=0,int d=0):maxx(a),minx(b),maxy(c),miny(d){}
	inline void Init() {
		maxx=maxy=-inf,minx=miny=inf;
	}
	inline void Update(const Point &rhs) {
		maxx=max(maxx,rhs.x),minx=min(minx,rhs.x),maxy=max(maxy,rhs.y),miny=min(miny,rhs.y);
	}
	inline int Calc(const Point &rhs) {
		return max(0,rhs.x-maxx)+max(0,minx-rhs.x)+max(0,rhs.y-maxy)+max(0,miny-rhs.y);
	}
	inline Data operator + (const Data &rhs) {
		return Data(max(maxx,rhs.maxx),min(minx,rhs.minx),max(maxy,rhs.maxy),min(miny,rhs.miny));
	}
};
struct Tnode {
	int ch[2],type;
	Point now;
	Data val;
	inline int& operator [] (const int &x) {
		return ch[x];
	}
}T[maxn];
inline void Update(int o) {
	if(T[o][0])
		T[o].val=T[o].val+T[T[o][0]].val;
	if(T[o][1])
		T[o].val=T[o].val+T[T[o][1]].val;
}
inline void Build(int &o,int l,int r) {
	if(l>r)
		return;
	if(!o)
		o=++tot;
	int mid=(l+r)>>1;
	nty=T[o].type=rand()&1,nth_element(p+l,p+mid,p+r+1),T[o].now=p[mid],T[o].val.Init(),T[o].val.Update(p[mid]),Build(T[o][0],l,mid-1),Build(T[o][1],mid+1,r),Update(o);
}
inline void Insert(int &o,int pos) {
	if(!o) {
		o=++tot,T[o].type=rand()&1,T[o].now=p[pos],T[o].val.Init(),T[o].val.Update(p[pos]);
		return;
	}
	nty=T[o].type;
	if(p[pos]<T[o].now)
		Insert(T[o][0],pos);
	else
		Insert(T[o][1],pos);
	Update(o);
}
inline void Query(int o,int pos) {
	int px=T[o].now.Calc(p[pos]),d[2]={T[T[o][0]].val.Calc(p[pos]),T[T[o][1]].val.Calc(p[pos])},fi=d[0]>=d[1];
	ans=min(px,ans);
	if(d[fi]<ans)
		Query(T[o][fi],pos),fi^=1;
	if(d[fi]<ans)
		Query(T[o][fi],pos);
}
int main() {
	read(n),read(m),T[0].val.Init(),srand(unsigned(time(NULL)));
	for(int i=1;i<=n;++i)
		p[i].Read();
	Build(rt,1,n);
	for(int i=1,ty;i<=m;++i) {
		read(ty),p[n+i].Read();
		if(ty==1)
			Insert(rt,n+i);
		else
			ans=inf,Query(rt,n+i),printf("%d\n",ans);
	}
}
