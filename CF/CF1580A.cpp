#include <bits/stdc++.h>
using namespace std;

int a[405][405],v[405][405], L[405][405], C[405][405];
inline int sjynmsl(int x, int y, int p, int q) {
  return a[p][q] + a[x-1][y-1] - a[x-1][q] - a[p][y-1];
}
inline int calcans(int x, int y, int p, int q) {
  int v = (q-y-1)*2 + (p-x-1)*2;
  v -= C[p][q-1]-C[p][y] + L[p-1][q]-L[x][q] + C[x][q-1]-C[x][y] + L[p-1][y]-L[x][y];
  assert(v>=0);
  v += sjynmsl(x+1,y+1,p-1,q-1);
  return v;
}
char buf[455];
void solve() {
  int n, m;
  scanf("%d%d", &n,&m);
  for (int i=1; i<=n; ++i) {
    scanf("%s", buf+1);
    for (int j=1; j<=m; ++j) {
      a[i][j] = v[i][j] = buf[j] - '0';
      a[i][j] += a[i][j-1] + a[i-1][j] - a[i-1][j-1];
      L[i][j] = L[i-1][j] + v[i][j];
      C[i][j] = C[i][j-1] + v[i][j];
    }
  }
  int ans = 114515114;
  for (int i=1; i<=n; ++i) {
    for (int w=5; i+w-1<=n; ++w) {
      int j=i+w-1;
      int p=1, q=4;
      for (; q<=m; ++q) {
        if (calcans(i,q-3,j,q)<calcans(i,p,j,q)) p=q-3;
        ans=min(ans,calcans(i,p,j,q));
      }
    }
  }
  printf("%d\n", ans);
}

int main() {
  int t; scanf("%d", &t);
  while (t--) solve();
  return 0;
}
