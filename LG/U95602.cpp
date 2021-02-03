#include <bits/stdc++.h>
using namespace std;

typedef long long  ll;
typedef unsigned long long ull;
const int    N = 2e5 + 15;
const auto  NE = "\n";
auto&       I  = cin ;
auto&       O  = cout;

int _eval_value_ = [](){
  ios :: sync_with_stdio(0);
  I.tie(0);                                                                                                                                                                                                                                                                                                                                                                                               
  return 0;
}(), n, Q, L[N], R[N],
  a[N], co[N], ra[N];

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

int main() {
  I >> n;
  for (int fa, i=2; i<=n; i++) {
    I >> fa; Graph::Addedge(fa, i);
  }
  Composer::B(n, n);
  for (int i=1; i<=n; i++) {
    I >> a[i];
    ra[a[i]] = i;
  }
  for (int i=1; i<=n; i++) I >> co[i];
  using Composer::lca;
  for (int i=1; i<=n; i++) {
    int &l = L[i]; l = i;
    while (l > 1 && lca(ra[l-1], ra[i]) == ra[i]) l = L[l-1];
  }
  for (int i=n; i>=1; i--) {
    int &r = R[i]; r = i;
    while (r < n && lca(ra[r+1], ra[i]) == ra[i]) r = R[r+1];
  }
  ull ans = 0;
  for (int i=1; i<=n; i++) {
    // printf("Point %d: [%d, %d] VAL %d OCC %d\n", i, L[i], R[i], co[a[i]], (i - L[i] + 1) * (R[i] - i + 1));
    ans += 1ull * (1ull * (i - L[i]) * (R[i] - i + 1) + 1ull * (i - L[i] + 1) * (R[i] - i) + 1) * co[a[i]];
  }
  O << ans << NE;
  return 0;
}
