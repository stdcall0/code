#include <bits/stdc++.h>
using namespace std;
// #define NDEBUG
// #pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
// #pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const int N = 19, M = 2e5 + 5;
int n, a[N], f[1 << N], g[1 << N];

namespace U {
  inline ll retR() {
    ll ret(0), c(0); bool neg(0); while (!isdigit(c = getchar())) neg = c == '-';
    ret = c - '0'; while (isdigit(c = getchar())) ret *= 10ll, ret += c - '0';
    return neg ? -ret : ret;
  }
  template <typename IntVal>
  inline void refR(IntVal v) { v = retR(); }
}; // Utils
auto R = U::retR;

int main() {
  n = R(); int W = R();
  int _ = (1 << n);

  for (int i=1; i<=n; i++) a[i] = R();

  fill(Rn(f, _), n + 1);
  fill(Rn(g, _), W + 1);
  f[0] = 1; g[0] = 0;

  for (int i=0; i<_; ++i) {
    for (int j=1; j<=n; j++) {
      if (i & (1 << j - 1)) continue;
      int nxt = i | (1 << j - 1);
      if (g[i] + a[j] <= W) {
        if (f[i] < f[nxt]) f[nxt] = f[i], g[nxt] = g[i] + a[j];
        else if (f[i] == f[nxt]) g[nxt] = min(g[nxt], g[i] + a[j]);
      } else {
        if (f[i] + 1 < f[nxt]) f[nxt] = f[i] + 1, g[nxt] = a[j];
        else if (f[i] + 1 == f[nxt]) g[nxt] = min(g[nxt], a[j]);
      }
    }
  }

  printf("%d\n", f[_ - 1]);
  return 0;
}
