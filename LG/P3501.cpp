#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
const int N = 5e5 + 5;
const ll P = 1e9 + 7;

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

int n;
char s[N];
ll h1[N], h2[N], pw[N];

int main() {
  n = R();
  gets(s + 1);
  pw[0] = 1;
  for (int i=1; i<=n; i++) {
    int j = n-i + 1;
    h2[j] = h2[j+1] * 3 + !(s[j] - '0');
    h2[j] %= P;
    h1[i] = h1[i-1] * 3 + s[i] - '0';
    h1[i] %= P; pw[i] = pw[i-1] * 3 % P;
  }
  auto gh = [](ll h[], int x, int y) {
    ll v = h[y] - h[x] * pw[abs(y - x)] % P + P;
    return v % P;
  };
  ll ans = 0;
  for (int c=1; c<n; ++c) {
    int L = 0, R = min(c, n-c), res = 0;
    while (L <= R) {
      int mid = L + R >> 1;
      // printf("Compare: Center %d Length %d Hash1 %lld Hash2 %lld\n", c,mid,gh(h1, c-mid, c), gh(h2, c+1, c+1+mid));
      if (gh(h1, c-mid, c) == gh(h2, c+1+mid, c+1)) {
        res = mid; L = mid + 1;
      } else R = mid - 1;
    }
    if (res) ans += res;
  }
  printf("%lld\n", ans);
  return 0;
}
