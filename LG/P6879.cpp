#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define down(x, y) x = min(x, y)
typedef long long LL;
const LL msk = 0x3f3f3f3f3f3f3f3fLL;
int n, L;
LL x[205], t[205];
LL dp[205][205][205][2];

int main() {
  scanf("%d%d", &n, &L);
  rep(i, 1, n) scanf("%lld", &x[i]); rep(i, 1, n) scanf("%lld", &t[i]);
  x[n + 1] = L; memset(dp, 0x3f, sizeof(dp));
  dp[0][0][0][0] = dp[0][0][0][1] = 0;
  rep(l, 0, n-1) rep(i, 0, l) rep(k, 0, l) rep(_, 0, 1) {
    int j = l - i; if (dp[i][j][k][_] == msk) continue;
    LL di = L - x[n-j+1] + x[i];
    LL ti = dp[i][j][k][_] + x[i+1] - x[i] + (_ ? 0 : di);
    int vi = k + (ti <= t[i+1]);
    down(dp[i+1][j][vi][1], ti); ti += di + x[i+1] - x[i]; down(dp[i+1][j][vi][0], ti);
    
    ti = dp[i][j][k][_] + x[n-j+1] - x[n-j] + (_ ? di : 0);
    vi = k + (ti <= t[n-j]);
    down(dp[i][j+1][vi][0], ti); ti += di + x[n-j+1] - x[n-j]; down(dp[i][j+1][vi][1], ti);
  }
  for (int k=n; k>=0; --k) rep(i, 0, n) rep(j, 0, n-i) rep(_, 0, 1)
    if (dp[i][j][k][_] != msk) { printf("%d\n", k); return 0; }
  return -1;
}
