#include<algorithm>
#include<cstdio>
#include<cmath>
#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;
#define ll long long
const int N = 1<<18;
void fwt(ll *A,int n){
    for(int k=1;k<n;k<<=1){
        int len=k<<1;
        for(int j=0;j<n;j+=len){
            for(int i=0;i<k;i++){
                int x=A[i+j],y=A[i+j+k];
                A[i+j+k]=x+y; //or
            }
        }
    }
}
void ufwt(ll *A,int n){
    for(int k=1;k<n;k<<=1){
        int len=k<<1;
        for(int j=0;j<n;j+=len){
            for(int i=0;i<k;i++){
                int x=A[i+j],y=A[i+j+k];
                A[i+j+k]=y-x; // or
            }
        }
    }
}
ll A[N],B[N],ans[N];
char s[20];
int main() {
    ll a[8] = {1,2,3,4,5,6,7,8};
    fwt(ll a, 8);
//freopen("F.in","r",stdin);
//freopen("out.txt","w",stdout);

  int TAT, cas = 1; scanf("%d",&TAT);
  while (TAT--) {
    printf("Case #%d:\n",cas++);
    int n, m; scanf("%d%d",&n,&m);
    memset(A,0,sizeof(A));
    memset(B,0,sizeof(B));
    int tot = 1<<m;
    for (int i = 0; i < n; ++i) {
      scanf("%s",s);
      int x = 0;
      int len = strlen(s);
      for (int j = 0; j < len; ++j) x = x*2 + s[j] - '0';
      ++A[x];
    }
    for (int i = 0; i < n; ++i) {
      scanf("%s",s);
      int x = 0;
      int len = strlen(s);
      for (int j = 0; j < len; ++j) x = x*2 + s[j] - '0';
      ++B[x];
    }
//    memset(ans,0,sizeof(ans));
//    for (int i = 0; i < tot; ++i) {
//      for (int j = 0; j < tot; ++j) {
//        ans[i|j]+=A[i]*B[j];
//      }
//    }
    fwt(A, tot); fwt(B, tot);
    for (int i = 0; i < tot; ++i) A[i] = A[i]*B[i];
    ufwt(A, tot);
    int q; scanf("%d",&q);
    while (q--) {
      scanf("%s",s);
      int x = 0;
      int len = strlen(s);
      for (int j = 0; j < len; ++j) x = x*2 + s[j] - '0';
      printf("%lld\n", A[x]);
    }
  }
}
