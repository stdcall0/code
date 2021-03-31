#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 19;

namespace U {
  inline ll retR() {
    ll ret(0), c(0); bool neg(0); while (!isdigit(c = getchar())) neg = c == '-';
    ret = c - '0'; while (isdigit(c = getchar())) ret *= 10ll, ret += c - '0';
    return neg ? -ret : ret;
  }
  template <typename IntVal>
  inline void refR(IntVal v) { v = retR(); }
}; // Utils

int n;
ll f[N + 5];
ll pw[N + 5]; // 10 ^ i
ll ans[10];
const ll P = (1e9 + 7);

int split(ll x) {
  for (int bit = N; bit >= 0; --bit) {
    if (x / pw[bit]) return bit + 1;
  }
  return 1;
}

void cntFor(ll X, ll M, int L=-1) { // M for Modifier
  if (L == -1) L = split(X);
  if (L == 0) return;
  ll x = X / pw[L - 1], y = X % pw[L - 1];
  (ans[0] -= pw[L - 1] * M) %= P;
  for (int u=0; u<=9; ++u) {
    (ans[u] += x * f[L - 1] % P * M) %= P;
    if (u < x) (ans[u] += pw[L - 1] * M) %= P;
  }
  (ans[x] += (y + 1) * M % P) %= P;
  cntFor(y, M, L-1);
}

int main() {
int T = U::retR();

  pw[0] = 1; for (int i=1; i<=20; ++i) {
    pw[i] = pw[i-1] * 10ll;
    (f[i] = f[i-1] * 10ll + pw[i - 1]) %= P;
  }

while (T--) {
  memset(ans, 0, sizeof(ans));
  ll l, r;
  l = U::retR(), r = U::retR();
  cntFor(r, 1); cntFor(l-1, -1);
  ll res = 0;
  for (ll i=0; i<=9; i++) {
    (res += (ans[i]%P+P)%P * i % P) %= P;
  }
  printf("%lld\n", res);
}
  return 0;
}
