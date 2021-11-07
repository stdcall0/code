#include <bits/stdc++.h>
using namespace std;

int h[5000005];
bool b[5000005], ha[5000005];

int main() {
  int n, m, t;
  scanf("%d%d%d", &n, &m, &t);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &h[i]);
  }
  for (int x,i = 1; i <= m; ++i)
    scanf("%d", &x), ha[x] = 1;
  int lp = 1;
  for (int i = 1; i <= n; ++i) {
    if (lp <= i - h[i]) lp = i - h[i] + 1;
    if (h[i] > t) {
      // lp to i is ok
      for (int j = lp; j <= i; ++j)
        b[j] = 1;
      lp = i + 1;
    }
  }
  lp = n;
  for (int i = n; i >= 1; --i) {
    if (i + h[i] <= lp) lp = i + h[i] - 1;
    if (h[i] > t) {
      for (int j = i; j <= lp; ++j)
        b[j] = 1;
      lp = i - 1;
    }
  }
  int ans = 0;
  b[0] = 1;
  bool flag = 0;
  for (int i = 1; i <= n; ++i) {
    if (!b[i] && b[i - 1]) flag = 1;
    if (b[i]) flag = 0;
    if (flag && ha[i]) {
      ++ans; flag = 0;
    }
  }
    
  printf("%d\n", ans == 0 ? 0 : ans + 1);
  return 0;
}