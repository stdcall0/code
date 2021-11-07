#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int v[205][205], f[2][205][2]; // f[k] have k bullets
bool w[205][205];
inline void nms(int &v, int x, int y) {
  if(x != -1) v = x+y;
}
inline void nmsl(int &v, int x, int y) {
  if(x != -1) v = max(v, x+y);
}

int main() {
  scanf("%d%d%d", &n,&m,&k); --k;
  for (int i=1; i<=n; ++i) {
    for (int j=1; j<=m; ++j) {
      static char b[5];
      scanf("%d%s", &v[i][j], b);
      w[i][j] = b[0] == 'N';
    }
  }
  for (int l=0; l<=k; ++l) f[0][l][0] = f[0][l][1] = -1;
  f[0][k][0] = f[0][k][1] = 0;
  bool c=0;
  for (int i=1; i<=m; ++i) {
    int nmss = 0;
    for (int j=n; j>=1; --j) {
      nmss += w[j][i];
      c = !c;
      for (int l=0; l<=k; ++l) {
        f[c][l][0] = max(f[!c][l][0], f[!c][l][1]);
        f[c][l][1] = -1;
        if (l+w[j][i] <= k) nms(f[c][l][1],f[!c][l+w[j][i]][1],v[j][i]);
        else f[c][l][1] = -1;
        if (j==n && l+w[j][i] <= k) nmsl(f[c][l][1], f[!c][l+w[j][i]][0],v[j][i]);
        printf("col %d lin %d [%d, %d]\n", i,j, f[c][l][0], f[c][l][1]);
      }
    }
  }
  printf("%d\n", max(f[c][0][0], f[c][0][1]) + 1);
  return 0;
}
