#include <bits/stdc++.h>

int main() {
  int t; scanf("%d", &t);
  while (t--) {
    static long long n;
    scanf("%lld", &n);
    printf("%lld\n", std::max(n + 1, 6ll) / 2 * 5);
  }
  return 0;
}
