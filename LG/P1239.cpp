#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 12;

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

int split(ll x) {
  for (int bit = N; bit >= 0; --bit) {
    if (x / pw[bit]) return bit + 1;
  }
  return 1;
}

void cntFor(ll X, int M, int L=-1) { // M for Modifier
  if (L == -1) L = split(X);
  if (L == 0) return;
  ll x = X / pw[L - 1], y = X % pw[L - 1];
  ans[0] -= pw[L - 1] * M;
  for (int u=0; u<=9; ++u) {
    ans[u] += x * f[L - 1] * M;
    if (u < x) ans[u] += pw[L - 1] * M;
  }
  ans[x] += (y + 1) * M;
  cntFor(y, M, L-1);
}

int main() {
  ll r;
  r = U::retR();
  pw[0] = 1; for (int i=1; i<=12; ++i) {
    pw[i] = pw[i-1] * 10ll;
    f[i] = f[i-1] * 10ll + pw[i - 1];
  }
  cntFor(r, 1); cntFor(0, -1);
  for (int i=0; i<=9; i++) printf("%lld\n", ans[i]);
  return 0;
}
