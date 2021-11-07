#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int n, m;
int a[100055];
LL f[100055];

inline int read(){
  int x=0,f=1;
  char ch=getchar();
  while(ch<'0'||ch>'9'){
    if(ch=='-')
        f=-1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9'){
    x=(x<<1)+(x<<3)+(ch^48);
    ch=getchar();
  }
  return x*f;
}

int main() {
  n = read(), m = read();
  for (register int i=1; i<=n; ++i) a[i] = read();
  for (register int i=1; i<=n; ++i) {
    f[i] = 1919810114514ll;
    register int mx = a[i]; register LL sum = a[i];
    for (register int j=i-1; j>=0; --j) {
      if (sum > m) break;
      f[i] = min(f[i], f[j] + mx);
      sum += a[j]; mx = max(mx, a[j]);
    }
  }
  printf("%lld\n", f[n]);
  return 0;
}
