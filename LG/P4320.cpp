#include <bits/stdc++.h>

#define Rn(a, n) a + 1, a + n + 1
#define Edge(T, x, y) T[x].push_back(y); T[y].push_back(x) //; printf("Edge #%s: %d - %d\n", #T, x, y)
typedef long long ll;
typedef unsigned long long ull;
inline ll Rl() { ll ret(0); int c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-'; ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0'; return neg ? -ret : ret; }
inline int R() { int ret(0), c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-'; ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0'; return neg ? -ret : ret; }

const int N = 5e5 + 5, M = 1e6 + 5;
int n, m;
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
  n = gc = R(), m = R();
  for (int u, v, i = 1; i <= m; ++i) {
    u = R(), v = R();
    Edge(G, u, v);
  }
  tar(1); dfs(1, 1); make_lca();

  int q = R();
  while (q--) {
    int x, y;
    x = R(), y = R();
    int lca = getlca(x, y);
    printf("%d\n", (dep[x] + dep[y] - dep[lca] * 2) / 2 + 1);
  }
  return 0;
}
