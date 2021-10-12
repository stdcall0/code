#include <cstdio>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ULL;
inline ULL r() { ULL x; scanf("%llu", &x); return x; }

int main() {
  int n, m, c, k; scanf("%d%d%d%d", &n,&m,&c,&k); ULL x, sta = 0, stb = -1;
  for (int i=1; i<=n; ++i) sta |= r(); sta = ~sta;
  for (int i=1; i<=m; ++i) {
    x = r();
    if (sta >> x & 1ull)
      if (stb >> x & 1ull) --k, stb ^= 1ull << x;
    r();
  }
  if (k == 64 && n == 0) puts("18446744073709551616");
  else printf("%llu\n", (1ull << k) - (ULL)n);
  return 0;
}
