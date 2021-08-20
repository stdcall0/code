#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)
typedef long long LL;
int n, k, a[100005], b[100005], c[100005];

LL solve(int l, int r) {
  if (l > r) return 0;
  if (l == r) return a[l] >= 0;
  int mid = l + r >> 1;
  LL bas = solve(l, mid) + solve(mid + 1, r);
  rep(i, l, mid) c[i] = b[i - 1] - b[mid];
  sort(c+l, c+mid+1);
  rep(i, mid+1, r) bas += upper_bound(c+l, c+mid+1, b[i]-b[mid])-c-l;
  return bas;
}
int main() {
  scanf("%d%d", &n,&k);
  rep(i, 1, n) {
    scanf("%d", &a[i]);
    a[i] -= k; b[i] = b[i-1] + a[i];
  }
  printf("%lld\n", solve(1, n));
  return 0;
}