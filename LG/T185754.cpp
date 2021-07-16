#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const int N = 2e5 + 5;
const ll P = 998244353;
int n, a[N];
inline ll fpow(ll x, ll y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  if (y & 1) return fpow(x, y - 1) * x % P;
  ll z = fpow(x, y >> 1);
  return z * z % P;
}

int main() {
  n = R();
  bool flag_sub1 = 1;
  rep(i, 1, n) {
    a[i] = R();
    if (a[i] != 0) flag_sub1 = 0;
  }
  if (flag_sub1) {
    ll t = fpow(2, n + 1);
    t -= 2; t += P; t %= P;
    printf("%lld\n", t);
  }
  return 0;
}