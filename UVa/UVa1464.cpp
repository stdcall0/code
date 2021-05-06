#include <bits/stdc++.h>

#define Rn(a, n) a + 1, a + n + 1
#define Edge(T, x, y) T[x].push_back(y); T[y].push_back(x) //; printf("Edge #%s: %d - %d\n", #T, x, y)
typedef long long ll;
typedef unsigned long long ull;
inline ll Rl() { ll ret(0); int c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-'; ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0'; return neg ? -ret : ret; }
inline int R() { int ret(0), c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-'; ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0'; return neg ? -ret : ret; }

const int N = 1e4 + 5, M = 1e5 + 5;
int n, m; int frm[M], to[M];
std::vector<int> G[N], T[N * 2];

int dfn[N], low[N], tick = 0;
int stk[N], top, gc;

void tar(int x) {
  low[x] = dfn[x] = ++tick;
  stk[++top] = x;
  for (int y : G[x]) {
    if (!dfn[y]) {
      tar(y);
      low[x] = std::min(low[x], low[y]);
      if (low[y] == dfn[x]) {
        ++gc;
        for (int u = 0; u != y; --top) {
          u = stk[top];
          Edge(T, gc, u);
        }
        Edge(T, gc, x);
      }
    }
    else
      low[x] = std::min(low[x], dfn[y]);
  }
}

int dep[N * 2], fa[21][N * 2];

void dfs(int x, int fa) {
  ::fa[0][x] = fa;
  dep[x] = dep[fa] + 1;
  for (int y : T[x]) {
    if (y != fa)
      dfs(y, x);
  }
}
void make_lca() {
  for (int i = 1; i <= 20; ++i) {
    for (int j = 1; j <= gc; ++j) {
      fa[i][j] = fa[i-1][fa[i-1][j]];
    }
  }
}
inline int getlca(int x, int y) {
  if (dep[x] > dep[y]) std::swap(x, y);
  for (int det = dep[y] - dep[x], i = 0;
    det;
    det >>= 1, ++i) {
      if (det & 1)
        y = fa[i][y];
  }
  if (x == y) return x;
  for (int i = 20; i >= 0; --i) {
    if (fa[i][x] == fa[i][y])
      continue;
    x = fa[i][x];
    y = fa[i][y];
  }
  return fa[0][x];
}

int main() {
while (scanf("%d%d", &n, &m) == 2 && (n || m)) {
  gc = n;
  for (int i = 1; i <= n; ++i) G[i].clear();
  for (int i = 1; i <= n * 2; ++i) T[i].clear();
#define EMP(a) memset(a, 0, sizeof(a))
  EMP(dfn); EMP(low); EMP(fa); EMP(dep);
  tick = 0;
  for (int i = 1; i <= m; ++i) {
    frm[i] = R(), to[i] = R();
    Edge(G, frm[i], to[i]);
  }

  for (int i = 1; i <= n; ++i)
    if (!dfn[i])
      top = 0, tar(i);
  for (int i = 1; i <= gc; ++i)
    if (!fa[0][i])
      dfs(i, i);

  make_lca();

  int q = R();
  while (q--) {
    int x, y;
    auto getans = [](int x, int y) {
      int lca = getlca(x, y);
      return (dep[x] + dep[y] - dep[lca] * 2) / 2 - 1;
    };
    x = R(), y = R();
    int ans = n;
#define UPD(a, b) ans = std::min(ans, getans(a[x], b[y]))
    UPD(frm, frm);
    UPD(frm, to);
    UPD(to, frm);
    UPD(to, to);
    printf("%d\n", ans);
  }
}
  return 0;
}
