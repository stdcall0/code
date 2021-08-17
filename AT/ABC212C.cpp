#include <bits/stdc++.h>

std::vector<int> a, b;

int ans = -1;
inline void _(int aIdx, int bIdx) {
  if (bIdx >= 0 && bIdx < b.size()) {
    int t = std::abs(a[aIdx] - b[bIdx]);
    if (ans == -1) ans = t;
    else ans = std::min(ans, t);
  }
}

int main() {
  int n, m; scanf("%d%d", &n, &m);
  for (int i=1; i<=n; ++i) {
    static int x; scanf("%d", &x);
    a.push_back(x);
  }
  for (int i=1; i<=m; ++i) {
    static int x; scanf("%d", &x);
    b.push_back(x);
  }
  std::sort(b.begin(), b.end());
  for (int i=1; i<=n; ++i) {
    size_t pos = std::lower_bound(b.begin(), b.end(), a[i - 1]) - b.begin();
    _(i - 1, pos); _(i - 1, pos - 1); _(i - 1, pos + 1);
  }
  printf("%d\n", ans);
  return 0;
}