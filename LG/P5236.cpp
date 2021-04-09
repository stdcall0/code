/// @category 圆方树
#include <bits/stdc++.h>
using namespace std;

// #define DBG(x) x
#define DBG(x)
#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
namespace U {
  inline ll retR() {
    ll ret(0), c(0); bool neg(0); while (!isdigit(c = getchar())) neg = c == '-';
    ret = c - '0'; while (isdigit(c = getchar())) ret *= 10ll, ret += c - '0';
    return neg ? -ret : ret;
  }
  template <typename IntVal>
  inline void refR(IntVal v) { v = retR(); }
}; // Utils
auto R = U::retR;


const int M = 4e5 + 5, N = 2e5 + 5;
int n, m, gid;
int sum[N], val[N], dep[N];
int dis2[N], dis[N];
int u[M], v[M], w[M];
struct graph {
  struct edge {
    int to, nxt, val;
  } edges[M * 2];
  int hed[N * 2], cntEdge = 0;
  inline void reset() { memset(hed, cntEdge = 0, sizeof(hed)); }
  graph() { reset(); }
  inline void _put(int x, int y, int z) {
    edges[++cntEdge] = (edge){y, hed[x], z};
    hed[x] = cntEdge;
  }
  inline void put(int from, int to, int weight) {
    _put(from, to, weight); _put(to, from, weight);
  }
} G, Gg;
namespace Tarjan {
  int tick = 0, top = 0;
  int dfn[N], low[N], stk[N];
  void tar(int x, int fa = 0) {
    dfn[x] = low[x] = ++tick; stk[++top] = x;
    for (int e = G.hed[x]; e; e = G.edges[e].nxt) {
      int y = G.edges[e].to;
      if (y == fa) continue;
      if (!dfn[y]) {
        val[y] = G.edges[e].val;
        dis[y] = dis[x] + val[y];
        tar(y, x);
        low[x] = min(low[x], low[y]);
        if (low[y] >= dfn[x]) {
          ++gid;
          sum[gid - n] = val[stk[top]] + dis[stk[top]] - dis[x];
          for (int u = 0; u != y; --top) {
            u = stk[top];
            ll p = dis[u] - dis[x];
            p = min(p, sum[gid - n] - p);
            Gg.put(u, gid, p);
            DBG(printf("%d in BCC #%d E=%lld.\n", u, gid - n, p);)
          }
          Gg.put(x, gid, 0);
          DBG(printf("%d in BCC #%d.\n", x, gid - n);)
        }
      } else if (dfn[y] < dfn[x]) {
        val[x] = G.edges[e].val;
        low[x] = min(low[x], dfn[y]);
      }
    }
  }
};
namespace RST { // also: LCA
  int fa[21][N];
  void init(int x, int f) {
    fa[0][x] = f;
    for (int i=1; i<=20; i++) {
      fa[i][x] = fa[i-1][fa[i-1][x]];
    }
    for (int e = Gg.hed[x]; e; e = Gg.edges[e].nxt) {
      auto &E = Gg.edges[e];
      if (E.to == f) continue;
      dep[E.to] = dep[x] + 1;
      dis2[E.to] = dis2[x] + E.val;
      init(E.to, x);
    }
  }
  inline int climb(int p, int x) {
    int det = dep[x] - dep[p] - 1;
    for (int i = 0; i <= 20; ++i) {
      if (det & (1 << i)) x = fa[i][x];
    }
    return x;
  }
  inline int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int det = dep[x] - dep[y], i = 0; i <= 20; ++i) {
      if (det & (1 << i)) x = fa[i][x];
    }
    if (x == y) return x;
    for (int i=20; i>=0; i--) {
      if (fa[i][x] != fa[i][y]) {
        x = fa[i][x];
        y = fa[i][y];
      }
    }
    return fa[0][x];
  }
  inline ll sv(int x, int y) {
    int p = lca(x, y);
    if (p <= n) return dis2[x] + dis2[y] - dis2[p] * 2;
    DBG(printf("SV: %d %d %d\n", p, x, y);)
    int u = climb(p, x), v = climb(p, y);
    ll mi = abs(dis[u] - dis[v]);
    mi = min(mi, sum[p - n] - mi);
    return mi + dis2[x] + dis2[y] - dis2[u] - dis2[v];
  }
};

int main() {
  n = R(), m = R();
  int q = R();
  for (int i=1; i<=m; i++) {
    u[i] = R(), v[i] = R(), w[i] = R();
    G.put(u[i], v[i], w[i]);
  }
  gid = n;
  Tarjan::tar(1);
  RST::init(1, 0);
  while (q--) {
    int x = R();
    int y = R();
    printf("%lld\n", RST::sv(x, y));
  }
  return 0;
}
