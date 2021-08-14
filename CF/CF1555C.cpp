#include <bits/stdc++.h>

typedef long long ll;
int n, a[2][100005];
ll s1[100005], s2[100005];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < 2; ++i)
      for (int j = 1; j <= n; ++j)
        scanf("%d", &a[i][j]);
    s1[0] = s2[n + 1] = 0;
    for (int i = 1, j = n; i <= n; ++i, --j) {
      s1[i] = s1[i-1] + a[0][i];
      s2[j] = s2[j+1] + a[1][j];
    }
    ll ans = 1145141141919810ll;
    auto spawn = [](int p) { return std::max(s1[n] - s1[p], s2[1] - s2[p]); };
    for (int i = 1; i <= n; ++i)
      ans = std::min(ans, spawn(i));
    printf("%lld\n", ans);
  }
  return 0;
}
