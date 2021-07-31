#include<bits/stdc++.h>
#define Rn(a,n)a+1,a+n+1
#define Edge(T,x,y)T[x].push_back(y);T[y].push_back(x)
#define rep(i,l,r)for(int i=(l),_r_R=(r);i<=_r_R;++i)
typedef long long ll;typedef long double ld;typedef unsigned long long ull;inline ll Rl(){ll ret(0);int c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}inline int R(){int ret(0),c(0);bool neg(0);while(!isdigit(c=std::getchar()))neg=c=='-';ret=c-'0';while(isdigit(c=std::getchar()))ret*=10ll,ret+=c-'0';return neg?-ret:ret;}

const ll P = 998244353ll;
int n;

std::vector<ll> mul;

int main() {
  n = R();
  ll neg = 0, pos = 0;
  mul.clear();
  rep(i, 1, n) {
    static char op[5]; scanf("%s", op);
    if (op[0] == '+') { ll x = Rl(); x < 0 ? (neg += x) %= P : (pos += x) %= P; }
    else mul.push_back(Rl());
  }
  std::sort(mul.begin(), mul.end());
  int ni = 0;
  ll posm = 1, negm = 1;
  for ( ; ni < mul.size(); ++ni) {
    if (mul[ni] > 0) break;
  }
  std::reverse(mul.begin(), mul.begin() + ni);
  for (int i = 2; i < ni; ++i) (negm *= mul[i]) %= P;
  for (int i = ni; i < mul.size(); ++i) (posm *= mul[i]) %= P;
  // printf("NI: %d Size: %d Neg: %lld Pos: %lld NxxegM: %lld PosM: %lld\n", ni,mul.size(), neg,pos, negm,posm);
  if (ni == 0) {
    ll ans = ((neg + pos * posm) % P + P) % P;
    printf("%lld\n", ans);
    return 0;
  }
  if (ni == 1) {
    ll ans = (neg * mul[0] % P + pos) * posm % P;
    printf("%lld\n", ans);
    return 0;
  }
  ll z;
  if (negm > 0) {
    z = (neg + pos * mul[0] % P) % P * mul[1] % P;
  } else {
    z = (neg * mul[0] % P + pos) % P * mul[1] % P;
  }
  (z *= negm * posm % P) %= P;
  // assert(z >= 0);
  z += P; z %= P;
  
  printf("%lld\n", z);
  return 0;
}