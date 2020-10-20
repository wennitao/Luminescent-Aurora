const int maxn=200001;
struct point{
    double x,y;
}p[maxn],a[maxn],b[maxn];
inline bool cmpx(point A,point B){if(A.x==B.x)return A.y<B.y;return A.x<B.x;}
inline bool cmpy(point A,point B){if(A.y==B.y)return A.x<B.x;return A.y<B.y;}
inline double sqr(double x){return x*x;}
inline double dis(point a,point b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}
inline double solve(int l,int r) {
    if(l+1==r)
        return dis(a[l],a[r]);
    if(l+2==r)
        return min(dis(a[l],a[r]),min(dis(a[l],a[l+1]),dis(a[l+1],a[r])));
    int mid=(l+r)>>1;
    double ans=min(solve(l,mid),solve(mid,r));
    int cnt=0;
    for(int i=l;i<=r;i++)
        if(a[i].x>=a[mid].x-ans&&a[i].x<=a[mid].x+ans)
            b[++cnt]=a[i];
    sort(b+1,b+cnt+1,cmpy);
    for(int i=1;i<=cnt;i++) {
        for(int j=i+1;j<=cnt&&j-i<10;j++) {
            if(b[j].y-b[i].y>=ans)
                break;
            ans=min(ans,dis(b[i],b[j]));
        }
    }
    return ans;
}
int main() {
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%lf%lf",&p[i].x,&p[i].y);
        a[i]=p[i];
    }
    sort(a+1,a+n+1,cmpx);
    printf("%.4lf\n",solve(1,n));
    return 0;
}
