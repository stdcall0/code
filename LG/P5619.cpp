#include <cstdio>

typedef long long LL;
const int maxN = 2e6 + 5;
const LL P = 19260817;

struct Edge {
  int to, nxt;
};

int n, sz[maxN], cnt = 0;
LL v[maxN], pw[maxN];
int hed[maxN];
Edge e[maxN * 2];

inline void addEdge(int x, int y) {
  e[++cnt] = {y, hed[x]},
  hed[x] = cnt;
  e[++cnt] = {x, hed[y]},
  hed[y] = cnt;
}
inline LL fpw(LL x, int y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  LL r = fpw(x, y >> 1);
  r = r * r % P;
  if (y & 1)
    r = r * x % P;
  return r;
}
inline LL inv(LL x) {
  return fpw(x, P - 2);
}
void solve(int x, int fa = 0) {
  sz[x] = 1;
  LL va = 1;
  for (int i = hed[x]; i; i = e[i].nxt) {
    int y = e[i].to;
    if (y == fa)
      continue;

    solve(y, x);
    (va *= v[y] + 1) %= P;
    sz[x] += sz[y];
  }
  if (sz[x] > 1)
    v[x] = (v[x] + 1) * va % P,
    v[x] = (v[x] + P - 1) % P;
}

int main() {
  static int q, u, w;
  static LL ans = 0;
  scanf("%d%d", &n, &q);
  pw[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pw[i] = pw[i - 1] * 2 % P;
    scanf("%d", &v[i]);
  }
  for (int i = 1; i < n; ++i) {
    scanf("%d%d", &u, &w);
    addEdge(u, w);
  }
  solve(1);
  while (q--) {
    scanf("%d", &u);
    (ans += v[u] * inv(pw[sz[u]])) %= P;
  }
  printf("%lld\n", ans);
  return 0;
}
