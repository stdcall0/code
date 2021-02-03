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
}(), n, Q, co[N], ans[N], cnt[N], Ans = 0;
bool vis[N], fil[N];

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
};
/// @namespace Solver
void calc(int o, int det) {
  using namespace Composer;
  cnt[co[o]] += det;
  if (cnt[co[o]] == 1 && det == 1) ++Ans;
  if (cnt[co[o]] == 0 && det == -1) --Ans;

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
  ans[o] = Ans;
  if (rollback) calc(o, -1);
}

int main() {
  I >> n;
  for (int x,y, i=1; i<n; i++) {
    I >> x >> y;
    Graph::Addedge(x, y);
  }
  for (int i=1; i<=n; i++) {
    I >> co[i];
  }
  Composer::B(n);
  dfu(1, 0);
  I >> Q; while (Q--) {
    int q; I >> q;
    O << ans[q] << NE;
  }
  return 0;
}
