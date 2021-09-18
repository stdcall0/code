#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)
typedef long long LL;

int n, c[1000005], p[1000005], l[1000005];
inline void exgcd(int &x, int &y, int a, int b) {
  if (!b) return (void)(x = 1, y = 0);
  exgcd(x, y, b, a % b);
  int t = x; x = y; y = t - a / b * y;
}

int main() {
  scanf("%d", &n);
  int ms = 1;
  rep(i, 1, n) {
    scanf("%d%d%d", &c[i], &p[i], &l[i]);
    ms = max(ms, c[i]);
  }
  rep(M, ms, 1000000) {
    bool nmsl = 1;
    rep(i, 1, n) { if (!nmsl) break; rep(j, i+1, n) {
      int left = p[i] - p[j];
      int right = c[j] - c[i];
      int x, y, G = __gcd(left, M);
      if (right % G) continue;
      exgcd(x, y, left, M);
      int _ = M; left /= G; right /= G; _ /= G;
      if (_ < 0) _ = -_;
      x = (x * right % _ + _) % _;
      if (x <= min(l[i], l[j])) {
        nmsl = 0;
        break;
      }
    } }
    if (nmsl) {
      printf("%d\n", M);
      break;
    }
  }
  return 0;
}
