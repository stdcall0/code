#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 505;
int n, m;
ll t[N], su[N], f[N];

int main() {
  n = R(), m = R();
  rep(i, 1, n) {
    t[i] = R();
  }
  std::sort(Rn(t, n));
  rep(i, 1, n) {
    su[i] = su[i - 1] + t[i];
  }

  rep(i, 1, n) {
    f[i] = t[i] * i - su[i];
    rep(j, 1, i - 1) { 
      if (t[i] - t[j] < m) break;
      ll lw = f[j] + t[i] * (i - j) - su[i] + su[j];
      f[i] = std::min(f[i], lw);
    }
  }

  printf("%lld\n", f[n]);

  return 0;
}