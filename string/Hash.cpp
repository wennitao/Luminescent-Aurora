typedef pair<int,int> pii;
#define fi first
#define se second
namespace Has {
    const int bas[2]={37,31},mod[2]={1000000007,998244353};
    int has[2][maxn][maxl],pw[2][maxl],ipw[2][maxl],le[maxn];
    inline int Add(int x,int y,int p) {
        return (x+=y)>=p?x-p:x;
    }
    inline int Sub(int x,int y,int p) {
        return (x-=y)<0?x+p:x;
    }
    inline int Mul(int x,int y,int p) {
        return 1ll*x*y%p;
    }
    inline int Pow(int x,int y,int p) {
        int res=1;
        for(;y;x=Mul(x,x,p),y>>=1)
            if(y&1)
                res=Mul(res,x,p);
        return res;
    }
    inline int Get(int i,int l,int r,int id) {
        return Mul(Sub(has[id][i][l],has[id][i][r+1],mod[id]),ipw[id][le[i]-r+1],mod[id]);
    }
    inline pii Val(int i,int l,int r) {
        return pii(Get(i,l,r,0),Get(i,l,r,1));
    }
    inline void Init() {
        for(int id=0;id<2;++id) {
            pw[id][0]=1;
            for(int i=1;i<maxl;++i)
                pw[id][i]=Mul(pw[id][i-1],bas[id],mod[id]);
            ipw[id][maxl-1]=Pow(pw[id][maxl-1],mod[id]-2,mod[id]);
            for(int i=maxl-2;~i;--i)
                ipw[id][i]=Mul(ipw[id][i+1],bas[id],mod[id]);
            for(int i=0;i<all;++i) {
                le[i]=s[i].length();//,has[id][i]=new int[le[i]+1];
                for(int j=le[i]-1;~j;--j) {
                    has[id][i][j]=Add(has[id][i][j+1] ;
                    Mul(pw[id][le[i]-j+1],s[i][j]-'a'+1,mod[id]),mod[id]);
                }
            }
        }
    }
}
