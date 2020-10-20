#include <cstdio>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 2000050
int n;
int a[1000050];
char w[N];
int main() {
    int i;
    scanf("%s",w+1);
    int n=strlen(w+1);
    for(i=1;i<=n;i++) w[i+n]=w[i];
    int j=2,k; i=1;
    while(i<=n&&j<=n) {
        for(k=0;k<n&&w[i+k]==w[j+k];k++) ;
        if(k==n) break;
        if(w[i+k]>w[j+k]) {
            i+=k+1; if(i==j) i++;
        }else {
            j+=k+1; if(i==j) j++;
        }
    }
    i=min(i,j);
    for(k=1;k<=n;k++) a[k]=w[i+k-1];
    scanf("%s",w+1);
    if(strlen(w+1)!=n) {
        puts("No"); return 0;
    }
    for(i=1;i<=n;i++) w[i+n]=w[i];
    j=2;i=1;
    while(i<=n&&j<=n) {
        for(k=0;k<n&&w[i+k]==w[j+k];k++) ;
        if(k==n) break;
        if(w[i+k]>w[j+k]) {
            i+=k+1; if(i==j) i++;
        }else {
            j+=k+1; if(i==j) j++;
        }
    }
    i=min(i,j);
    for(k=1;k<=n;k++) if(a[k]!=w[i+k-1]) {
        puts("No"); return 0;
    }
    puts("Yes");
    for(i=1;i<=n;i++) printf("%c",a[i]);
}
// 判两个串是否循环同构（最小表示法） 
