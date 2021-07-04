#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

int a[205], s[205];
int f[205][205], g[205][205];

int main() {
  int n = R();
  rep(i, 1, n) {
    a[i] = a[i + n] = R();
  }
  rep(i, 1, n * 2) {
    s[i] = s[i - 1] + a[i];
  }
  rep(k, 1, n) {
    rep(i, 1, n * 2 - k) {
      int j = i + k - 1;
      if (k == 1) {
        f[i][j] = g[i][j] = 0;
        continue;
      }
      f[i][j] = 1e9 + 5;
      rep(l, i, j - 1) {
        f[i][j] = std::min(f[i][j], f[i][l] + f[l+1][j] + s[j] - s[i-1]);
        g[i][j] = std::max(g[i][j], g[i][l] + g[l+1][j] + s[j] - s[i-1]);
      }
    }
  }
  int mx = 0, mi = 1e9 + 5;
  rep(i, 1, n) {
    mx = std::max(mx, g[i][i+n-1]);
    mi = std::min(mi, f[i][i+n-1]);
  }
  printf("%d\n%d\n", mi, mx);
  return 0;
}
