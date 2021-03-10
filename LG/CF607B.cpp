#include <bits/stdc++.h>
using namespace std;
#define Rn(a, n) a + 1, a + n + 1

typedef long long ll;
const int N = 505;

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

int n, f[N][N], a[N];

inline bool checkRange(int l, int r) {
  for (int i=l; i<=r; i++) {
    int j = r - (i-l);
    if (i > j) return true;
    if (a[i] != a[j]) return false;
  }
  return true;
}

int main() {
  n = R();
  for (int i=1; i<=n; i++) {
    a[i] = R();
    f[i][i] = 1;
    if (i > 1) f[i-1][i] = a[i] == a[i-1] ? 1 : 2;
  }
  for (int L=3; L<=n; L++) {
    for (int i=1; i<=n-L+1; i++) {
      int j = i+L - 1;
      f[i][j] = 1e9;
      if (a[i] == a[j]) f[i][j] = f[i+1][j-1];
      for (int k=i; k<j; ++k) {
        f[i][j] = min(f[i][j], f[i][k] + f[k+1][j]);
      }
    }
  }
  printf("%d\n", f[1][n]);
  return 0;
}