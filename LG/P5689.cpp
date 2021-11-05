#include <cstdio>

typedef long long LL;
const int maxN = 3e5 + 5;
const int P = 1e9 + 7;

int n, fac[maxN], ans[maxN];
int sz[maxN], fa[maxN];

inline void init() {
  fac[0] = 1;
  for (int i = 1; i <= n + 1; ++i)
    fac[i] = (LL)fac[i - 1] * i % P;
  for (int i = 1; i <= n; ++i)
    sz[i] = 1,
    ans[i] = 1,
    fa[i] = i;
}

inline int fpw(int x, int y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  int r = fpw(x, y >> 1);
  r = (LL)r * r % P;
  if (y & 1)
    r = (LL)r * x % P;
  return r;
}
inline int inv(int x) {
  return fpw(x, P - 2);
}
inline int C(int n, int m) {
  if (m == 0) return 1;
  return (LL)fac[n] * inv(fac[n - m]) % (LL)P * inv(fac[m]) % P;
}
inline int find(int x) {
  if (x == fa[x])
    return x;
  return fa[x] = find(fa[x]);
}
inline void merge(int x, int y) {
  x = find(x),
  y = find(y);
  fa[x] = y;
  ans[y] = (LL)ans[x] * ans[y] % (LL)P * C(sz[x] + sz[y] - 1, sz[y] - 1) % P;
  sz[y] += sz[x];
}

int main() {
  static int q, la = 0, x, y, op;
  scanf("%d%d", &n, &q);
  init();
  while (q--) {
    scanf("%d%d", &op, &x);
    x = (x + la) % n + 1;
    if (op == 1) {
      scanf("%d", &y);
      y = (y + la) % n + 1;
      merge(x, y);
    } else {
      printf("%d\n", la = ans[find(x)]);
    }
  }
  return 0;
}