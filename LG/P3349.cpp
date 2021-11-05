// 20 pts
#include <cstdio>
#include <algorithm>

typedef long long LL;

int n, m;
bool G[18][18];
int u[1145], v[1145];
int a[18];

int main() {
  scanf("%d%d", &n, &m);
  for (int x, y, i = 1; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    G[x][y] = G[y][x] = 1;
  }
  for (int i = 1; i < n; ++i) {
    scanf("%d%d", &u[i], &v[i]);
  }
  for (int i = 1; i <= n; ++i)
    a[i] = i;
  int ans = 0;
  do {
    bool ok = 1;
    for (int i = 1; i < n; ++i)
      if (!G[a[u[i]]][a[u[j]]]) {
        ok = false;
        break;
      }
    if (ok)
      ++ans;
  } while (std::next_permutation(a + 1, a + 1 + n));
  printf("%d\n", ans);
  return 0;
}
