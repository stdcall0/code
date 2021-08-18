#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 300005;
const LL P = 998244353;
int n; vector<int> G[N];

inline LL pw(LL x, LL k) {
  if (k == 0) return 1; if (k == 1) return x % P;
  if (k & 1) return pw(x, k ^ 1) * x % P;
  LL _ = pw(x, k >> 1); return _ * _ % P;
}
int dep[N], fa[20][N]; LL f[51][N];

void dfs(int x, int fa = 1) {
  ::fa[0][x] = fa;
  for (int i = 1; i <= 50; ++i)
    f[i][x] = (pw(dep[x], i) + f[i][fa]) % P;
  for (int y : G[x]) {
    if (y == fa) continue;
    dep[y] = dep[x] + 1;
    dfs(y, x);
  }
}
void makelca() {
  for (int i = 1; i < 20; ++i)
    for (int j = 1; j <= n; ++j)
      fa[i][j] = fa[i-1][fa[i-1][j]];
}
inline int getlca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  for (int det = dep[x] - dep[y], i = 0; i < 20; ++i)
    if (det & 1 << i) x = fa[i][x];
  if (x == y) return x;
  for (int i = 19; i >= 0; --i) {
    if (fa[i][x] != fa[i][y]) {
      x = fa[i][x];
      y = fa[i][y];
    }
  }
  return fa[0][x];
}
inline int answer(int x, int y, int k) {
  int lca = getlca(x, y);
  LL ret = f[k][x] + f[k][y] - f[k][fa[0][lca]] - f[k][lca];
  ret %= P; ret += P; ret %= P;
  return static_cast<int>(ret);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int x, y; scanf("%d%d", &x, &y);
    G[x].push_back(y); G[y].push_back(x);
  }
  dfs(1); makelca();
  int m; scanf("%d", &m);
  while (m--) {
    int i,j,k; scanf("%d%d%d", &i,&j,&k);
    printf("%d\n", answer(i,j,k));
  }
  return 0;
}
