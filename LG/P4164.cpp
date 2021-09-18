// Warning: Corrupted Code, fucked up.

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int n;
struct Range {
  int l, r, p; LL v;
  static bool o114(const Range& a, const Range& b) { return a.r - a.l > b.r - b.l; }
  static bool o514(const Range& a, const Range& b) { return a.r != b.r ? a.r < b.r : a.l < b.l; }
  static LL cost(int L, int R) {
    int D = (L + R) & 1;
    return 1LL * (R - L + 2 + D) * (R - L + 2 + D) / 4;
  }
  static Range g114514(int x, int y, int p) {
    int det = -1 - y;
    return Range {x - det, x + det, p, (LL)p - cost(x - det, x + det)};
  }
  bool include(const Range& _) { return l <= _.l && _.r <= r; }
  bool intersect(const Range& _) { return !(r < _.l || l > _.r); }
} a[1005];
LL f[1005], ans = 0;

int main() {
  scanf("%d", &n);
  for (int x,y,p,i=1; i<=n; ++i) {
    scanf("%d%d%d", &x,&y,&p);
    a[i] = Range::g114514(x, y, p);
    // printf("Range: %d %d %d %lld\n", a[i].l, a[i].r, a[i].p, a[i].v);
  }
  // sort(a + 1, a + 1 + n, Range::o114);
  for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j)
    if (a[i].include(a[j])) a[i].v += a[j].p;
  sort(a + 1, a + 1 + n, Range::o514);
  for (int i=1; i<=n; ++i) {
    f[i] = a[i].v;
    int v = 0, P = 0;
    for (int j=1; j<i; ++j) {
      if (!a[i].include(a[j])) { if (a[i].intersect(a[j])) {
        while (P <= i && a[P].r <= a[j].r) {
          if (a[P].l >= a[i].l) v += a[P].p; ++P;
        }
        f[i] = max(f[i], f[j] + a[i].v + Range::cost(a[i].l, a[j].r) - v);
      } else f[i] = max(f[i], a[i].v + f[j]); }
    }
    // printf("F[%d] <- %lld\n", i, f[i]);
    ans = max(ans, f[i]);
  }
  printf("%lld\n", ans);
  return 0;
}
