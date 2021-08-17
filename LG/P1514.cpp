#include <cstdio>
#include <cassert>
#include <algorithm>

int n, m;
int h[505][505];
int L[505][505], R[505][505];

void dfs(int x, int y) {
  if (L[x][y] != -1) return;
  int &l = L[x][y], &r = R[x][y];
  if (x == n) return (void)(l = r = y);
  static const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
  for (int d = 0; d < 4; ++d) {
    int p = x + dx[d], q = y + dy[d];
    if (p < 1 || q < 1 || p > n || q > m) continue;
    if (h[p][q] >= h[x][y]) continue;
    dfs(p, q);
    if (L[p][q] != -1)
      l = std::min(L[p][q], l == -1 ? 1145141919 : l), r = std::max(R[p][q], r);
  }
}

int main() {
  scanf("%d%d", &n,&m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &h[i][j]);
      L[i][j] = R[i][j] = -1;
    }
  }
  for (int i = 1; i <= m; ++i) dfs(1, i);
  int cnt = 0;
  for (int i = 1; i <= m; ++i)
    cnt += L[n][i] == -1;
  if (cnt) return printf("0\n%d\n", cnt), 0;
  for (int i = 1; i <= m; ++i, ++cnt) {
    int x = -1;
    for (int j = 1; j <= m; ++j)
      if (L[1][j] <= i && R[1][j] > x)
        x = R[1][j];
    assert(x > i);
    i = x;
  }
  printf("1\n%d\n", cnt);
  return 0;
}
