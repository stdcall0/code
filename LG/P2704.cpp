#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 105, M = 11;
const int STA = (1 << M - 1) + 5;

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

int n, m;
int f[2][STA][STA], mp[N], cnt[STA];
//  rowId lastRow currRow
char buf[M];

auto check1 = [](int x, int r) {
  return x & (x >> 1) || x & (x >> 2) || x & (r <= 0 ? 0 : mp[r]);
};

int main() {
  n = R(), m = R();
  for (int i=1; i<=n; i++) {
    scanf("%s", buf);
    for (int j=0; j<m; j++) {
      (mp[i] <<= 1) |= buf[j] == 'H';
    }
  }
  int S = 1 << m;
  for (int i=0; i<S; ++i) cnt[i] = __builtin_popcount(i);
  int T = 0;
  for (int r=1; r<=n; r++) { // line no.
    T ^= 1;
    for (int i=0; i<S; ++i) {
      if (check1(i, r-1)) continue;
      for (int j=0; j<S; ++j) {
        if (i & j || check1(j, r)) continue;
        for (int k=0; k<S; ++k) {
          if (j & k || i & k || check1(k, r-2)) continue;
          f[T][i][j] = max(f[T][i][j], f[!T][k][i] + cnt[j]);
        }
      }
    }
  }
  int ans = 0;
  for (int i=0; i<S; ++i) {
    ans = max(ans, *max_element(f[T][i], f[T][i] + S));
  }
  printf("%d\n", ans);
  return 0;
}
