#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353,inv2=(mod+1)>>1,mrt=31596;
namespace {
    inline int Add(const int &x,const int &y) {
        int res=x+y;
        if(res>=mod)
            res-=mod;
        return res;
    }
    inline int Sub(const int &x,const int &y) {
        int res=x-y;
        if(res<0)
            res+=mod;
        return res;
    }
    inline int Mul(const int &x,const int &y) {
        return 1ll*x*y%mod;
    }
    inline int Pow(int x,int y=mod-2) {
        int res=1;
        while(y) {
            if(y&1)
                res=1ll*res*x%mod;
            x=1ll*x*x%mod;
            y>>=1;
        }
        return res;
    }
}
const int fmaxn=21,Fmaxn=(1<<fmaxn)+5,G=3;
int nxtl[Fmaxn],nxtlim[Fmaxn],inv[Fmaxn];
namespace Solve {
    map<int,int>ins;
    #define random(a,b) (rand()%(b-a+1)+a)
    ll w;
    bool ok;
    struct QuadraticField {
        ll x,y;
        inline QuadraticField operator*(QuadraticField T) {
            QuadraticField ans;
            ans.x=(this->x*T.x%mod+this->y*T.y%mod*w%mod)%mod,ans.y=(this->x*T.y%mod+this->y*T.x%mod)%mod;
            return ans;
        }
        inline QuadraticField operator^(ll b) {
            QuadraticField ans,a=*this;
            ans.x=1,ans.y=0;
            for(;b;b>>=1,a=a*a)
                if(b&1)
                    ans=ans*a;
            return ans;
        }
    };
    inline ll Legender(ll a) {
        ll ans=Pow(a,(mod-1)/2);
        return ans+1==mod?-1:ans;
    }
    inline ll Getw(ll n,ll a) {
        return ((a*a-n)%mod+mod)%mod;
    }
    inline ll Solve(ll n) {
        ll a;
        if(mod==2)
            return n;
        if(Legender(n)==-1)
            ok=false;
        srand((unsigned)time(NULL));
        while(1) {
            a=random(0,mod-1),w=Getw(n,a);
            if(Legender(w)==-1)
                break;
        }
        QuadraticField ans,res;
        res.x=a,res.y=1;
        ans=res^((mod+1)/2);
        return ans.x;
    }
    inline int Solve2(int p) {
        static int j,res;
        if(p==0)
            return 0;
        j=1;
        for(int i=0;i<mrt;++i)
            ins[j]=i,j=Mul(j,G);
        res=0,j=Pow(j);
        for(int i=0;i<=mrt;++i) {
            if(ins.count(p)) {
                res=(res+ins[p])%(mod-1);
                if(res&1)
                    return -1;
                res=Pow(G,res/2);
                if(mod-res<res)
                    res=mod-res;
                return res;
            }
            p=Mul(p,j),res=(res+mrt)%(mod-1);
        }
        return -1;
    }
}
namespace Poly {
    static int tot,root[Fmaxn<<1],beg[fmaxn],mx,rev[Fmaxn];
    inline void Rev(int l) {
        rev[0]=0;
        for(int i=1;i<(1<<l);++i)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
    }
    inline void DFT(vector<int>&a,int bit) {
        for(;mx<bit;++mx) {
            int len=1<<mx,w0=Pow(G,(mod-1)/(len<<1)),w=1;
            beg[mx]=tot;
            for(int j=0;j<len;++j)
                root[tot++]=w,w=Mul(w,w0);
        }
        for(int i=1;i<1<<bit;++i)
            if(i<rev[i])
                swap(a[i],a[rev[i]]);
        for(int i=0,len=1;i<bit;++i,len<<=1)
            for(int j=0;j<(1<<bit);j+=(len<<1))
                for(int k=0;k<len;++k) {
                    int x=a[j+k],y=Mul(a[j+k+len],root[beg[i]+k]);
                    a[j+k]=Add(x,y),a[j+k+len]=Sub(x,y);
                }
    }
    inline void IDFT(vector<int>&a,int bit) {
        int len=(1<<bit),inv=Pow(len);
        reverse(a.begin()+1,a.end());
        DFT(a,bit);
        for(int i=0;i<len;++i)
            a[i]=Mul(a[i],inv);
    }
    inline void FFT(vector<int>a,vector<int>b,vector<int>&c) {
        c.clear();
        int la=a.size(),lb=b.size(),lc=la+lb-1,l=nxtl[lc],lim=nxtlim[lc];
        a.resize(lim),b.resize(lim),c.resize(lim);
        Rev(l),DFT(a,l),DFT(b,l);
        for(int i=0;i<lim;++i)
            c[i]=Mul(a[i],b[i]);
        IDFT(c,l);
        c.resize(lc);
    }
    inline void AddPoly(vector<int>a,vector<int>b,vector<int>&c) {
        c.clear();
        int la=a.size(),lb=b.size(),lc=max(la,lb);
        c.resize(lc);
        for(int i=0;i<lc;++i) {
            if(i<la)
                c[i]=Add(c[i],a[i]);
            if(i<lb)
                c[i]=Add(c[i],b[i]);
        }
    }
    inline void SubPoly(vector<int>a,vector<int>b,vector<int>&c) {
        c.clear();
        int la=a.size(),lb=b.size(),lc=max(la,lb);
        c.resize(lc);
        for(int i=0;i<lc;++i) {
            if(i<la)
                c[i]=Add(c[i],a[i]);
            if(i<lb)
                c[i]=Sub(c[i],b[i]);
        }
    }
    inline void Inv(vector<int>f,vector<int>&g,int len) {
        g.clear();
        int lim=nxtlim[len];
        f.resize(lim),g.resize(lim);
        g[0]=Pow(f[0]);
        for(int i=2,p=1;i<=lim;i<<=1,++p) {
            vector<int>h(i<<1),l(i<<1),o(i<<1);
            for(int j=0;j<i;++j)
                h[j]=f[j];
            for(int j=0;j<i>>1;++j)
                l[j]=g[j];
            Rev(p+1),DFT(h,p+1),DFT(l,p+1);
            for(int j=0;j<i<<1;++j)
                o[j]=Mul(h[j],Mul(l[j],l[j]));
            IDFT(o,p+1);
            for(int j=0;j<i;++j)
                g[j]=Sub(Mul(2,g[j]),o[j]);
        }
        g.resize(len);
    }
    inline void Ln(vector<int>f,vector<int>&g,int len) {
        g.clear();
        vector<int>h(len,0);
        for(int i=1;i<len;++i)
            h[i-1]=Mul(f[i],i);
        h[len-1]=0;
        Inv(f,g,len);
        FFT(g,h,g);
        for(int i=len-1;i;--i)
            g[i]=Mul(g[i-1],::inv[i]);
        g[0]=0;
        g.resize(len);
    }
    inline void Exp(vector<int>f,vector<int>&g,int len,int init) {
        int lim=nxtlim[len];
        if(init)
           g.clear(),g.push_back(1);
        f.resize(lim),g.resize(lim);
        for(int i=2,p=1;i<=lim;i<<=1,++p) {
            vector<int>h(i<<1),l,o(i<<1,0);
            for(int j=0;j<i>>1;++j)
                h[j]=g[j];
            Ln(h,l,i);
            for(int j=0;j<i;++j)
                l[j]=Sub(f[j]+(!j),l[j]),l.push_back(0);
            Rev(p+1),DFT(h,p+1),DFT(l,p+1);
            for(int j=0;j<i<<1;++j)
                o[j]=Mul(h[j],l[j]);
            IDFT(o,p+1);
            for(int j=0;j<i;++j)
                g[j]=o[j];
        }
        g.resize(len);
    }
    inline void Pow(vector<int>f,vector<int>&g,int len,ll k) {
        g.clear();
        vector<int>h;
        Ln(f,h,len);
        int o=k%mod;
        for(int i=0;i<len;++i)
            h[i]=Mul(h[i],o);
        g.push_back(::Pow(f[0],(int)(k%(mod-1))));
        Exp(h,g,len,0);
    }
    inline void Sqrt(vector<int>f,vector<int>&g,int len) {
        g.clear();
        g.push_back(Solve::Solve2(f[0]));
        int lim=nxtlim[len];
        for(int i=2,p=1;i<=lim;i<<=1,++p) {
            vector<int>h(i),l,o(i<<1,0);
            g.resize(i<<1);
            for(int j=0;j<i;++j)
                h[j]=g[j];
            Inv(h,l,i);
            l.resize(i<<1);
            for(int j=0;j<min(i,(int)f.size());++j)
                o[j]=f[j];
            Rev(p+1),DFT(g,p+1),DFT(l,p+1),DFT(o,p+1);
            for(int j=0;j<i<<1;++j)
                o[j]=Mul(Add(g[j],Mul(l[j],o[j])),inv2);
            IDFT(o,p+1);
            for(int j=0;j<i;++j)
                g[j]=o[j];
            g.resize(i);
        }
        g.resize(len);
    }
}
vector<int>a,b,c,d;
int n;
ll m;
char s[100005];
int main() {
    nxtl[1]=0,nxtlim[1]=1,inv[1]=1;
    for(int i=1;i<Fmaxn-1;++i) {
        nxtl[i+1]=nxtl[i],nxtlim[i+1]=nxtlim[i];
        if(i==(i&-i))
            ++nxtl[i+1],nxtlim[i+1]<<=1;
    }
    for(int i=2;i<Fmaxn;++i)
        inv[i]=Mul(inv[mod%i],(mod-mod/i));
    read(n),a.resize(n);
    scanf("%s",s+1);
    // printf("String = %s\n",s+1);
    int len=strlen(s+1);
    for(int i=1;i<=len;++i)
        m=(1ll*m*10+s[i]-'0')%mod;
    // cout<<m<<endl;
    for(int i=0;i<n;++i)
        read(a[i]);
    Poly::Pow(a,b,n,m);
    for(int i=0;i<(int)b.size();++i)
        printf("%d ",b[i]);
    puts("");
}
