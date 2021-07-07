#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

std::vector<int> p;
const int maxN = 5e6 + 5;
const ll P = 998244353ll;
int T, k, N;
ll ans[maxN]; bool flag[maxN];
inline void getFuckingPrimes() {
  for (int i = 2; i <= N; ++i) {
    if (!flag[i]) p.push_back(i);
    for (int j = i + i; j <= N; j += i)
      flag[j] = 1;
  }
}
inline ll fpw(ll x, ll y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  if (y & 1) return fpw(x, y - 1) * x % P;
  ll w = fpw(x, y >> 1ll);
  return w * w % P;
}
/*
void recuv(int x = 1, ll v = 0, int mp = 0) {
  ans[x] = v;
  ll w;
  rep(i, mp, p.size() - 1) {
    if (x * p[i] > N) break;
    flag[p[i]] = !flag[p[i]];
    w = v + fpw(p[i], k) * (flag[p[i]] ? 1 : -1);
    w = (w % P + P) % P;
    printf("%d from %d: w = %d from %d\n", x * p[i], x,  w, v);
    recuv(x * p[i], w, i);
    flag[p[i]] = !flag[p[i]];
  }
}*/

int main() {
  T = R(), k = R(), N = R();
  getFuckingPrimes();
  /*memset(flag, 0, sizeof(flag));
  recuv();*/
  while (T--) {
    // printf("%lld\n", ans[R()]);
    int x = R(); ll ans = 0;
    rep(i, 0, p.size() - 1) {
      if (p[i] > x) break;
      int cnt = 0 ;
      for (int y = x; y; cnt += y /= p[i]);
      if (cnt & 1) (ans += fpw(p[i], k)) %= P;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
