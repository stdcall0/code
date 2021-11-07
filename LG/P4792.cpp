#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxN = 2e5 + 5;

int n, k, m;
int s[maxN];
int cnt[maxN];

int main() {
  static int x = 1, c, l, ans = 0, y = 1;
  scanf("%d%d%d", &n, &k, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &s[i]);

  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &c, &l);
    cnt[c] -= l;
    while (x <= n && cnt[c] < 0)
      ++cnt[s[x++]];
    if (cnt[c] < 0)
      puts("impossible"),
      exit(0);
  }
  ans = x - 1;

  for (; x <= n + 1; ++x) {
    while (y < x && cnt[s[y]] > 0)
      --cnt[s[y++]];
    ans = std::min(ans, x - y);
    ++cnt[s[x]];
  }
  printf("%d\n", ans);
  return 0;
}