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
int val[N];
struct graph {
  struct edge {
    int to, nxt;
  } edges[M * 2];
  int hed[N * 2], cntEdge = 0;
  inline void reset() { memset(hed, cntEdge = 0, sizeof(hed)); }
  graph() { reset(); }
  inline void _put(int x, int y) {
    edges[++cntEdge] = (edge){y, hed[x]};
    hed[x] = cntEdge;
  }
  inline void put(int from, int to) {
    _put(from, to); _put(to, from);
  }
} G, Gg;
namespace Tarjan {
  int tick = 0, top = 0;
  int dfn[N], low[N], stk[N];
  void tar(int x) {
    dfn[x] = low[x] = ++tick; stk[++top] = x;
    for (int e = G.hed[x]; e; e = G.edges[e].nxt) {
      int y = G.edges[e].to;
      if (!dfn[y]) {
        tar(y);
        low[x] = min(low[x], low[y]);
        if (low[y] == dfn[x]) {
          ++gid; val[gid] = 1;
          for (int u = 0; u != y; --top) {
            u = stk[top];
            Gg.put(u, gid); ++val[gid];
          }
          Gg.put(x, gid);
        }
      } else low[x] = min(low[x], dfn[y]);
    }
  }
};

bool vis[N];
int siz[N];
ll ans = 0;
void solve(int x, int fa = 0) {
  vis[x] = 1;
  siz[x] = x <= n;
  for (int e = Gg.hed[x]; e; e = Gg.edges[e].nxt) {
    int y = Gg.edges[e].to;
    if (y == fa) continue;
    solve(y, x);
    ans += 2ll * siz[x] * siz[y] * val[x];
    siz[x] += siz[y];
  }
  ans += 2ll * (Tarjan::tick - siz[x]) * siz[x] * val[x];
}

int main() {
  n = R(), m = R();
  for (int i=1; i<=n; i++) val[i] = -1;
  for (int u,v, i=1; i<=m; i++) {
    u = R(), v = R();
    G.put(u, v);
  }
  gid = n;
  for (int i=1; i<=n; i++) if (!Tarjan::dfn[i]) {
    Tarjan::tar(i); --Tarjan::top;
    solve(i); Tarjan::tick = 0;
  }
  printf("%lld\n", ans);
  return 0;
}
