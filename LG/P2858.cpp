#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL f[2055][2055], a[2055];
LL gt(int l, int r, int day) {
  if (l > r) return 0;
  if (l == r) return a[l] * day;
  if (f[l][r]) return f[l][r];
  return f[l][r] = max(gt(l+1, r, day+1) + a[l] * day, gt(l, r-1, day+1) + a[r] * day);
}

int main() {
  int n; scanf("%d", &n);
  for (int i=1; i<=n; ++i) scanf("%lld", &a[i]);
  printf("%lld\n", gt(1, n, 1));
  return 0;
}
