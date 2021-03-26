#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 5e3 + 5;

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

int n, w, s, a[N];
ll f[2][N];
deque<int> q;

int main() {
  n = R(); w = R(); s = R();
  for (int i=1; i<=n; i++) {
    a[i] = R();
  }
  int T = 0;
  memset(f[T^1], 0x80, sizeof(f[T^1]));
  for (int i=1; i<=n; i++) {
    T ^= 1;
    memset(f[T], 0x80, sizeof(f[T]));
    q.clear();
    int lim = min(i-1, w);
    for (int j=0; j<=min(lim, s-1); j++) {
      while (!q.empty() && f[T^1][q.back()] <= f[T^1][j]) q.pop_back();
      q.push_back(j);
    }
    for (int j=1; j<=w; j++) {
      while (!q.empty() && q.front() < j-1) q.pop_front();
      if (s+j-1 > 0 && s+j-1 <= lim) {
        while (!q.empty() && f[T^1][q.back()] <= f[T^1][s+j-1]) q.pop_back();
        q.push_back(s+j-1);
      }
      if (!q.empty()) {
        // printf("%d %lld\n", i, f[T^1][q.front()]);
        f[T][j] = f[T^1][q.front()] + 1ll * j * a[i];
      }
    }
  }
  printf("%lld\n", *max_element(f[T], f[T] + w + 1));
  return 0;
}
