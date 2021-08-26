#include <bits/stdc++.h>
using namespace std;

typedef long long LL; typedef long double LD;
int n, m;
LL f[105][105], g[105][105];
LL inf = 0x3f3f3f3f3f3f3f3fLL;

inline void upd(int x, int y, LL v, LL vc) {
  if (v < f[x][y]) {
    f[x][y] = v; g[x][y] = vc;
  } else if (v == f[x][y]) {
    g[x][y] += vc;
  }
}

int main() {
  scanf("%d%d",&n,&m);
  memset(f, 0x3f, sizeof(f));
  for (int i = 1; i <= m; ++i) {
    static int x, y, z;
    scanf("%d%d%d", &x,&y,&z);
    upd(x, y, z, 1); upd(y, x, z, 1);
  }
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        if (f[i][k] != inf && f[k][j] != inf)
          upd(i, j, f[i][k] + f[k][j], g[i][k] * g[k][j]);
  for (int i = 1; i <= n; ++i) {
    LD ans = 0;
    for (int s = 1; s <= n; ++s)
      for (int t = 1; t <= n; ++t)
        if (s != i && t != i && s != t && f[s][i] != inf && f[i][t] != inf && f[s][i] + f[i][t] == f[s][t]) {
          // printf("%d %d %d %lld %lld %lld\n", i, s, t, g[s][i], g[i][t], g[s][t]);
          ans += (LD)(g[s][i] * g[i][t]) / g[s][t];
        }
    printf("%.3lf\n", (double)ans);
  }
  return 0;
}
