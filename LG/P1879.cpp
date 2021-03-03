#include <bits/stdc++.h>
using namespace std;
// #define NDEBUG
// #pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
// #pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const int N = 13, STA = (1 << N + 1) + 5;
int n, m, a[N][N];
ll f[N][STA]; // rowId currentRow placedCount

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

inline int countOne(int x) {
  int res = 0;
  for (; x; x >>= 1) res += x & 1;
  return res;
}
inline bool motherfucking(int s, int e) {
  for (int i=1; i<=m; i++) {
    if (s & (1 << i-1)) {
      if (!a[e][i]) return true;
      if (s & (1 << i)) return true;
    }
  }
  return false;
}
inline bool canPlace(int ls, int cs) {
  for (int i=1; i<=m; i++) {
    if (cs & (1 << i-1) && ls & (1 << i-1)) {
      return false;
    }
  }
  return true;
}

int main() {
  n = R(); m = R();
  int S = 1 << m;
  f[0][0] = 1;
  for (int i=1; i<=n; i++) for (int j=1; j<=m; j++) a[i][j] = R();
  for (int row=1; row<=n+1; ++row) {
    for (int s=0; s<S; ++s) {
      if (motherfucking(s, row)) continue;

      ll &F = f[row][s];
      for (int l=0; l<S; ++l) {
        if (motherfucking(l, row-1)) continue;
        if (canPlace(l, s)) {
          (F += f[row - 1][l]) %= 100000000ll;
        }
      }
    }
  }
  cout << f[n+1][0] << endl;
  return 0;
}
