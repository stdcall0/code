#include <bits/stdc++.h>
using namespace std;

int f[1005][1005];
int main() {
  int n, k; scanf("%d%d", &n,&k);
  f[1][0] = 1;
  for (int i=2; i<=n; ++i) {
    f[i][0] = 1;
    for (int j=1; j<=i; ++j)
      f[i][j] = ((j+1) * f[i-1][j] + (i-j) * f[i-1][j-1]) % 2015;
  }
  printf("%d\n", f[n][k]);
  return 0;
}
