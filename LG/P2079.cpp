#include <cstdio>
#include <cstring>
#include <algorithm>

int n, v;
int c[105], w[105], vv[105];
int f[2][505][2][505];

int main() {
  scanf("%d%d", &n, &v);
  int _ = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%d%d%d", &c[i], &w[i], &vv[i]);
  memset(f, 128, sizeof(f));
  int ans = 0;
  f[0][0][0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    memset(f[!_], 128, sizeof(f[!_]));
    f[!_][0][0][0] = 0;
    for (int j = 0; j <= 500; ++j)
      for (int k = 0; k < 2; ++k)
        for (int l = c[i]; l <= v; ++l) {
          int nj = (k ? -j : j) - w[i];
          if (nj < -500 || nj > 500) continue;
          int nk = nj < 0;
          nj = nk ? -nj : nj;
          f[!_][j][k][l] = std::max(f[!_][j][k][l], f[_][nj][nk][l - c[i]] + vv[i]);
          if (k == 0) ans = std::max(ans, f[!_][j][0][l]);
        }
    _ = !_;
  }
  printf("%lld\n", ans);
  return 0;
}