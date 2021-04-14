/// @category 圆方树
#include <bits/stdc++.h>

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
inline ll R() {
  ll ret(0), c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-';
  ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0';
  return neg ? -ret : ret;
}

const int M = 4e5 + 5, N = 2e5 + 5;
std::vector<int> G[M], T[M * 2];
int n, m, gid;

int tick, top;
int dfn[N], low[N], stk[N];
int fa[21][N], dep[N], dis[N];

void tar(int x) {
  dfn[x] = low[x] = ++tick;
  stk[++top] = x;
  for (auto y : G[x]) {
    if (!dfn[y]) {
      tar(y);
      low[x] = std::min(low[x], low[y]);
      if (low[y] == dfn[x]) {
        ++gid;
        for (int u = 0; u != y; --top) {
          u = stk[top];
          T[u].push_back(gid);
          T[gid].push_back(u);
        }
        T[x].push_back(gid);
        T[gid].push_back(x);
      }
    } else low[x] = std::min(low[x], dfn[y]);
  }
}

void dfs(int x, int f) {
  dfn[x] = ++tick;
  dep[x] = dep[fa[0][x] = f] + 1;
  dis[x] = dis[fa[0][x]] + (x <= n);
  for (int i = 1; i <= 20; i++) {
    fa[i][x] = fa[i-1][fa[i-1][x]];
  }
  for (auto y : T[x]) if (y != f) dfs(y, x);
}

int lca(int x, int y) {
  if (dep[x] < dep[y]) std::swap(x, y);
  for (int det = dep[x] - dep[y], i = 0; i <= 20; ++i) {
    if (det & (1 << i)) x = fa[i][x];
  }
  if (x == y) return x;
  for (int i = 20; i >= 0; i--) {
    if (fa[i][x] != fa[i][y]) {
      x = fa[i][x];
      y = fa[i][y];
    }
  }
  return fa[0][x];
}

int S, s[N];

int main() {
  int data = R();
  while (data--) {
    n = R(), m = R();

    tick = top = 0; gid = n;
    for (int i = 1; i <= n; i++) {
      G[i].clear();
      dfn[i] = low[i] = 0;
    }
    for (int i = 1; i <= n * 2; i++) T[i].clear();

    for (int u,v, i = 1; i <= m; i++) {
      u = R(), v = R();
      G[u].push_back(v);
      G[v].push_back(u);
    }

    dis[1] = dep[1] = 0;
    tar(1), tick = 0, dfs(1, 0);

    for (int qs = R(); qs--; ) {
      S = R(); for (int i = 1; i <= S; ++i) {
        s[i] = R();
      }

      std::sort(Rn(s, S), [](int x, int y) { return dfn[x] < dfn[y]; });

      ll ans = -2ll * S;
      for (int i = 1; i <= S; ++i) {
        int u = s[i], v = s[i == S ? 1 : i + 1];
        ans += dis[u] + dis[v] - dis[lca(u, v)] * 2;
      }

      if (lca(s[1], s[S]) <= n) ans += 2;

      printf("%lld\n", ans / 2);
    }
  }
  return 0;
}
