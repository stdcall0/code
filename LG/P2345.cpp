#include <bits/stdc++.h>
using namespace std;

int a[20005], b[20005];

int main() {
  int n; scanf("%d", &n);
  for (int i=1; i<=n; ++i) {
    scanf("%d%d",&a[i], &b[i]);
  }
  long long v=0;
  for (int i=1; i<n; ++i) for (int j=i+1; j<=n; ++j)
    v += max(a[i], a[j]) * abs(b[i] - b[j]);
  printf("%lld\n", v);
  return 0;
}