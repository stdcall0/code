#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int n, k;
int t[1005], x[1005], y[1005];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= k; ++i) {
    scanf("%d%d%d", &t[i], &x[i], &y[i]);
  }
  LL ans = -1;

  for (int i = 1; i < k; ++i)
    for (int j = i + 1; j <= k; ++j) {
      LL _ = 1LL * t[i] / __gcd(t[i], t[j]) * t[j];
      //printf("i %d j %d: _ %lld\n", i,j,_);
      LL k1 = _ / t[i], k2 = _ / t[j];
      LL left = k1 * y[i] - k2 * y[j], right = 1LL * x[j] - x[i] + y[i] - y[j];
      right %= n; right += n; right %= n;
      if (left % n == 0 && right % n == 0) continue;
      for (int mul = 1; mul <= 40; ++mul)
      if (left*mul % n != right % n) {
        if (ans == -1) ans = _*mul;
        else ans = min(ans, _*mul);
        break;
      }
    }
  if (ans == -1) puts("Mystia will cook forever...");
  else printf("%lld\n", ans - 1);
  return 0;
}
