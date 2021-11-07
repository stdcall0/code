#include <cstdio>
#include <cmath>

const int maxN = 1e5 + 5;

int n, a[maxN];

int main() {
  scanf("%d", &n);
  long long ans = 0;
  scanf("%lld", &ans);
  for (int x, i = 2; i <= n; ++i) {
    scanf("%d", &x);
    ans += abs(x);
  }
  printf("%lld\n", ans);
  return 0;
}
