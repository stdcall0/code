#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; scanf("%d", &n);
  int L; scanf("%d", &L);
  long long ans = 0;
  for (int i = 1; i < n; ++i) {
    int R; scanf("%d", &R);
    ans += max(L, R);
    L = R;
  }
  printf("%lld\n", ans);
  return 0;
}
