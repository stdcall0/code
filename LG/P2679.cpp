#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;
const int maxN = 1005;
const int maxM = 205;
const int P = 1e9 + 7;

int n, m, k;
char a[maxN], b[maxM];
int f[2][maxM][maxM][2];

int main() {
  scanf("%d%d%d", &n, &m, &k);
  scanf("%s%s", a + 1, b + 1);

  bool t = 0;
  f[0][0][0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    bool u = !t;
    memset(f[u], 0, sizeof(f[u]));
    f[u][0][0][0] = 1;
    for (int j = 1; j <= std::min(i, m); ++j)
      for (int k = 1; k <= j; ++k) {
        if (a[i] == b[j])
          f[u][j][k][1] = (1ll * f[t][j - 1][k][1] + f[t][j - 1][k - 1][0] + f[t][j - 1][k - 1][1]) % P;
        f[u][j][k][0] = (1ll * f[t][j][k][1] + f[t][j][k][0]) % P;
      }
    t = u;
  }

  printf("%lld\n", (1ll * f[t][m][k][1] + f[t][m][k][0]) % P);
  return 0;
}
