#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 5;
const int ep = 19;

int n, m;
int a[maxN], Lg[maxN], f[ep][maxN];
int pw[ep];

void init() {
  pw[0] = 1;
  for (int i = 0, j = 1; j <= n; ++j) {
    if (j == pw[i] * 2)
      pw[++i] = j;

    Lg[j] = i;
    f[0][j] = a[j];
  }

  for (int k = 1; k < ep; ++k)
    for (int i = 1; i <= n; ++i) {
      f[k][i] = f[k - 1][i];
      if (i + pw[k - 1] <= n && f[k - 1][i + pw[k - 1]] > f[k][i])
        f[k][i] = f[k - 1][i + pw[k - 1]];
    }
}

int qry(int l, int r) {
  int p = Lg[r - l + 1];
  return std::max(f[p][l], f[p][r - pw[p] + 1]);
}

int main() {
  int x, y;

  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);

  init();

  while (m--) {
    scanf("%d%d", &x, &y);
    printf("%d\n", qry(x, y));
  }
  return 0;
}