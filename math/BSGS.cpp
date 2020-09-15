#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<tr1/unordered_map>
using namespace std;
typedef long long ll;
bool Finish_read;
template<class T>inline void read(T &x){Finish_read=0;x=0;int f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;if(ch==EOF)return;ch=getchar();}while(isdigit(ch))x=x*10+ch-'0',ch=getchar();x*=f;Finish_read=1;}
template<class T>inline void print(T x){if(x/10!=0)print(x/10);putchar(x%10+'0');}
template<class T>inline void writeln(T x){if(x<0)putchar('-');x=abs(x);print(x);putchar('\n');}
template<class T>inline void write(T x){if(x<0)putchar('-');x=abs(x);print(x);}
/*================Header Template==============*/
map<ll,int>num;
ll g,a,b,p,A,B;
int T,n;
inline void exgcd(ll a,ll b,ll &d,ll &x,ll &y) {
    if(!b)
        d=a,x=1,y=0;
    else
        exgcd(b,a%b,d,y,x),y-=x*(a/b);
}
inline ll inv(ll x) {
    ll d,xx,y;
    exgcd(x,p,d,xx,y);
    return d==1?(xx+p)%p:-1;
}
inline ll pw(ll a,ll b) {
    ll res=1;
    while(b) {
        if(b&1)
            res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}
inline ll solve(ll x) {
    for(int i=0;i<=n;i++) {
        ll v=x*inv(pw(g,i*n))%p;
        if(num.count(v))
            return num[v]+i*n;
    }
    return -1;
}
int main() {
    read(g),read(p),read(T);
    n=ceil(sqrt(p));
    ll x=1;
    num[1]=0;
    for(int i=1;i<=n;i++) {
        x=x*g%p;
        if(!num[x])
            num[x]=i;
    }
    while(T--) {
        read(A),read(B);
        printf("%lld\n",pw(A,solve(B)));
    }
}

