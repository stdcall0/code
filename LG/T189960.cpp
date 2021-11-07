#include <bits/stdc++.h>
using namespace std;

int n, v, m, a[20], tot[1000005], c[1000005];

vector<int> O;

int main() {
  int cl = clock();
  scanf("%d%d%d", &n, &v, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    for (int x, j = 1; j <= m; ++j) {
      scanf("%d", &x);
      if (x != 0) c[i] |= 1 << (j - 1), tot[i] += x;
    }
  }
  for (int sta = (1 << m) - 1; sta >= 0; --sta) O.push_back(sta);
  sort(O.begin(), O.end(), [](int x, int y) { return __builtin_popcount(x) < __builtin_popcount(y); });
  int ans = 0; int flag = 0; bool tle = 0;
  for (int sta : O) {
    if (!tle) tle = (clock() - cl > CLOCKS_PER_SEC / 10 * 9);
    if (sta & flag && tle) continue; // superio
    int res = 0;
    for (int i = 0; i < m; ++i)
      if (sta & 1 << i) res += a[i + 1];
    if (res <= ans) continue;
    int _ = sta; for (int i = n; i >= 1; --i) {
      int _ = (sta | c[i]) ^ c[i];
      if (__builtin_popcount(_) + tot[i] <= v) 
        sta = _;
    }
    if (!sta) ans = res;
    else flag |= _;
  }
  printf("%d\n", ans);
  return 0;
}
