#include <bits/stdc++.h>

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
inline ll R() {
  ll ret(0), c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-';
  ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0';
  return neg ? -ret : ret;
}

const int N = 2e5 + 5, M = 5e5 + 5;
int n, a[N], c[M] = {0};

int main() {
  n = R();
  for (int i = 1; i <= n; ++i) {
    ++c[a[i] = R()];
  }
  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = a[i]; j <= M; j += a[i]) {
      ans += j == a[i] ? c[j] - 1 : c[j];
    }
  }
  printf("%lld\n", ans);
  return 0;
}
