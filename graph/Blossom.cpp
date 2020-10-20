#include<bits/stdc++.h>
using namespace std;
inline int read() {
    int x=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=x*10+c-'0';
    return x*f;
}
const int maxn=505,maxm=250020;
int n,m,que[maxm],ql,qr,pre[maxn],tim=0,h[maxn],tot=0,T,match[maxn],f[maxn],tp[maxn],tic[maxn];
bool edge[maxn][maxn];
struct Edge {
    int v,nxt;
}e[maxm];
inline int find(int x) {
    return f[x]==x?f[x]:f[x]=find(f[x]);
}
inline void add(int u,int v) {
    e[++tot]=(Edge){v,h[u]};
    h[u]=tot;
}
inline int lca(int x,int y) {
    for(++tim;;swap(x,y))
		if(x) {
        	x=find(x);
    		if(tic[x]==tim)
				return x;
			else
				tic[x]=tim,x=pre[match[x]];
    	}
}
inline void blossom(int x,int y,int p) {
    while(find(x)!=p) {
        pre[x]=y;
		y=match[x];
        if(tp[y]==2) {
			tp[y]=1;
			que[++qr]=y;
		}
		if(find(x)==x)
			f[x]=p;
        if(find(y)==y)
			f[y]=p;
        x=pre[y];
    }
}
inline bool aug(int s) {
    for(int i=1;i<=n;++i)
		f[i]=i;
    memset(tp,0,sizeof tp);
	memset(pre,0,sizeof pre);
    tp[que[ql=qr=1]=s]=1;
    while(ql<=qr) {
        int x=que[ql++];
        for(int i=h[x],v=e[i].v;i;i=e[i].nxt,v=e[i].v) {
            if(find(v)==find(x)||tp[v]==2)
				continue; 
            if(!tp[v]) {
                tp[v]=2;
				pre[v]=x;
                if(!match[v]) {
                	for(int now=v,lst,tmp;now;now=lst) {
                        lst=match[tmp=pre[now]];
                        match[now]=tmp,match[tmp]=now;
                    }
                    return true;
                } 
                tp[match[v]]=1;
				que[++qr]=match[v];
            }
			else if(tp[v]==1) {
                int l=lca(x,v);
                blossom(x,v,l);
                blossom(v,x,l);
            }
        }
    }
    return false;
}
int main() {
    n=read(),m=read();
    for(int i=1;i<=m;++i) {
        int x=read(),y=read();
        add(x,y),add(y,x);
    }
    int ans=0;
    for(int i=1;i<=n;++i)
		ans+=(!match[i]&&aug(i));
    printf("%d\n",ans);
    for(int i=1;i<=n;++i)
		printf("%d ",match[i]);
    puts("");
    return 0;
}
