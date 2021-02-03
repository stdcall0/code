#include <bits/stdc++.h>
using namespace std;

typedef long long  ll;
const int    N = 1e5 + 15;
const auto  NE = "\n";
auto&       I  = cin ;
auto&       O  = cout;

int _eval_value_ = [](){
  ios :: sync_with_stdio(0);
  I.tie(0);                                                                                                                                                                                                                                                                                                                                                                                               
  return 0;
}(), n, Q, ans[N], cnt[N], faU[21][N];
bool vis[N];
struct Query {
  int dep, Qid;
};
vector<Query> qry[N];

namespace Graph {
  int hed[N], gcnt = 0;
  struct edge { int to, nxt; } E[N * 2];
  auto _add = [](int x, int y) {
    E[++gcnt] = (edge){y, hed[x]}; hed[x] = gcnt;
  };
  inline void Addedge(int x, int y) {
    _add(x, y); _add(y, x);
  }
};
namespace Composer {
  int fa[N], dep[N], siz[N], son[N], top[N], dfn[N], tim = 0;
  using namespace Graph;
  void _ba(int o) {
    son[o] = -1; siz[o] = 1;
    for (int e=hed[o]; e; e=E[e].nxt) {
      int x = E[e].to;
      if (!dep[x]) {
        dep[x] = dep[o] + 1;
        fa[x] = o; _ba(x);
        siz[o] += siz[x];
        if (son[o] == -1 || siz[x] > siz[son[o]]) son[o] = x;
      }
    }
  }
  void _bb(int o, int t) {
    top[o] = t; dfn[o] = ++tim;
    if (son[o] == -1) return;
    _bb(son[o], t);
    for (int e=hed[o]; e; e=E[e].nxt) {
      int x = E[e].to;
      if (x != fa[o] && x != son[o]) {
        _bb(x, x);
      }
    }
  }
  inline void B(int n, int R=1) { dep[R] = 1; fa[R] = 0; _ba(R); _bb(R, R); }
  inline int lca(int x, int y) {
    while (top[x] ^ top[y]) {
      if (dep[top[x]] < dep[top[y]]) swap(x, y);
      x = fa[top[x]];
    }
    if (dep[x] > dep[y]) return y;
    return x;
  }
};
/// @namespace Solver
inline void LCAinit() {
  for (int i=1; i<=n; i++) faU[0][i] = Composer::fa[i];
  for (int i=1; i<=20; i++) {
    for (int j=1; j<=n; j++)
      faU[i][j] = faU[i-1][faU[i-1][j]];
  }
}
inline int qry_k(int x, int k) {
  for (int i=20; i>=0; i--) if (k & (1 << i)) x = faU[i][x];
  return x;
}
void calc(int o, int det) {
  using namespace Composer;
  cnt[dep[o]] += det;

  for (int e=hed[o]; e; e=E[e].nxt) {
    int x = E[e].to;
    if (x != fa[o] && !vis[x]) {
      calc(x, det);
    }
  }
}
void dfu(int o, bool rollback) {
  using namespace Composer;
  for (int e=hed[o]; e; e=E[e].nxt) {
    int x = E[e].to;
    if (x != fa[o] && x != son[o]) {
      dfu(x, true);
    }
  }
  if (son[o] != -1) dfu(son[o], false), vis[son[o]] = 1;
  calc(o, 1);
  vis[son[o]] = 0;
  for (Query& q : qry[o]) {
    int Ddep = dep[o] + q.dep;
    ans[q.Qid] = cnt[Ddep] - 1;
  }
  if (rollback) calc(o, -1);
}

int main() {
  I >> n; ++n;
  for (int fa, i=1; i<n; i++) {
    I >> fa;
    if (fa == 0) Graph::Addedge(n, i);
    else Graph::Addedge(i, fa);
  }
  Composer::B(n, n);
  LCAinit();
  I >> Q; for (int x,y,i=1; i<=Q; i++) {
    I >> x >> y;
    int dbg = qry_k(x, y);
    if (dbg == n || dbg == 0);
    else qry[dbg].push_back({y, i});
  }
  dfu(n, 0);
  O << ans[1];
  for (int i=2; i<=Q; i++) {
    O << ' ' << ans[i];
  }
  O << NE;
  return 0;
}
