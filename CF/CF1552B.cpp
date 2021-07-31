#include <cstdio>

int n, r[5][50005];
inline bool le(int x, int y) {
  int c = 0;
  for (int i = 0; i < 5; ++i) c += r[i][x] < r[i][y];
  return c >= 3;
}

int main() {
  int t = 0; scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      for (int j = 0; j < 5; ++j)
        scanf("%d", &r[j][i]);
    int ans = 1;
    for (int i = 2; i <= n; ++i)
      if (le(i, ans)) ans = i;
    for (int i = 1; i <= n; ++i)
      if (le(i, ans)) {
        ans = -1;
        break;
      }
    printf("%d\n", ans);
  }
  return 0;
}