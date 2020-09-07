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
const int mod=998244353;
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
    inline int Half(const int &x) {
        return x&1?(x+mod)>>1:x>>1;
    }
}
int lim;
inline void FMT(vector<int>&x) {
    for(int i=1;i<lim;i<<=1)
        for(int j=0;j<lim;++j)
            if(j&i)
                x[j]=Add(x[j],x[j^i]);
}
inline void IFMT(vector<int>&x) {
    for(int i=1;i<lim;i<<=1)
        for(int j=0;j<lim;++j)
            if(j&i)
                x[j]=Sub(x[j],x[j^i]);
}
inline void FWTand(vector<int>&x) {
    for(int i=1;i<lim;i<<=1)
        for(int j=0;j<lim;j+=(i<<1))
            for(int k=0;k<i;++k)
                x[j+k]=Add(x[j+k],x[j+k+i]);
}
inline void IFWTand(vector<int>&x) {
    for(int i=1;i<lim;i<<=1)
        for(int j=0;j<lim;j+=(i<<1))
            for(int k=0;k<i;++k)
                x[j+k]=Sub(x[j+k],x[j+k+i]);
}
inline void FWTxor(vector<int>&x) {
    for(int i=1;i<lim;i<<=1)
        for(int j=0;j<lim;j+=(i<<1))
            for(int k=0;k<i;++k) {
                int y=x[j+k],z=x[j+k+i];
                x[j+k]=Add(y,z),x[j+k+i]=Sub(y,z);
            }
}
inline void IFWTxor(vector<int>&x) {
    for(int i=1;i<lim;i<<=1)
        for(int j=0;j<lim;j+=(i<<1))
            for(int k=0;k<i;++k) {
                int y=x[j+k],z=x[j+k+i];
                x[j+k]=Half(Add(y,z)),x[j+k+i]=Half(Sub(y,z));
            }
}
inline void Show(const vector<int>&x) {
    for(int i=0;i<lim;++i)
        printf("%d ",x[i]);
    puts("");
}
inline void Read(vector<int>&x) {
    x.resize(lim);
    for(int i=0;i<lim;++i)
        read(x[i]);
}
inline vector<int> operator * (const vector<int>&x,const vector<int>&y) {
    vector<int>res(lim,0);
    for(int i=0;i<lim;++i)
        res[i]=Mul(x[i],y[i]);
    return res;
}
vector<int>a,b,A,B,C;
int main() {
    read(lim),lim=1<<lim,Read(a),Read(b),A=a,B=b;
    FMT(A),FMT(B),C=A*B,IFMT(C),Show(C),A=a,B=b;
    FWTand(A),FWTand(B),C=A*B,IFWTand(C),Show(C),A=a,B=b; 
    FWTxor(A),FWTxor(B),C=A*B,IFWTxor(C),Show(C);
}
