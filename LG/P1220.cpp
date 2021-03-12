#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
const int N = 55;

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

int n, c;
int f[N][N], g[N][N];
int a[N], b[N], s[N];

inline int r(int i, int j) {
  return s[i] + s[n] - s[j];
}
#define v(j, i) (a[j] - a[i])

int main() {
  n = R(), c = R();
  for (int i=1; i<=n; i++) {
    a[i] = R(), b[i] = R();
    s[i] = s[i-1] + b[i];
  }
  memset(f, 127, sizeof(f));
  memset(g, 127, sizeof(g));
  f[c][c] = g[c][c] = 0;
  for (int L=2; L<=n; ++L) {
    for (int i=1; i<=n-L+1; i++) {
      int j = i+L-1;
      f[i][j] = min(f[i+1][j] + v(i+1, i) * r(i, j), g[i+1][j] + v(j, i) * r(i, j));
      g[i][j] = min(f[i][j-1] + v(j, i) * r(i-1, j-1), g[i][j-1] + v(j, j-1) * r(i-1, j-1));
    }
  }
  printf("%d\n", min(f[1][n], g[1][n]));
  return 0;
}

