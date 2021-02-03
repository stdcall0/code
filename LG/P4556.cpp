#include <bits/stdc++.h>
using namespace std;

typedef long long  ll;
const int    N = 1e5 + 15;
const int   Mn = 1e5 + 15;
const auto  NE = "\n";
auto&       I  = cin ;
auto&       O  = cout;

int _eval_value_ = [](){
  ios :: sync_with_stdio(0);
  I.tie(0);
  return 0;
}(), n, m, ans[N];

namespace Graph {
  int hed[N], gcnt = 0;
  struct edge { int to, nxt; } E[N * 4];
  auto _add = [](int x, int y) {
    E[++gcnt] = (edge){y, hed[x]}; hed[x] = gcnt;
  };
  inline void Addedge(int x, int y) {
    _add(x, y); _add(y, x);
  }
};
namespace Query {
  int hed[N], gcnt = 0;
  struct edge { int to, nxt; } E[N * 21];
  auto Addedge = [](int x, int y) {
    E[++gcnt] = (edge){y, hed[x]}; hed[x] = gcnt;
  };
};
namespace Composer {
  int fa[N], dep[N], siz[N], son[N], top[N], dfn[N], rev[N], tim = 0;
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
    top[o] = t; dfn[o] = ++tim; rev[dfn[o]] = o;
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
namespace SegmentTree {
  #define child(x) Segment &l = a[(x).l], &r = a[(x).r]
  #define Lg(x) x.L, x.mid
  #define Rg(x) (x.mid+1), x.R
  #define apply(act) l act; r act
  struct Segment {
    int L, R, mid;
    int l, r;
    int v, vT;
    void up();
  } a[Mn * 4];
  int c = 0;
  void Segment::up() {
    if (L != R) {
      child(*this);
      if (l.v >= r.v) vT = l.vT, v = l.v;
      else vT = r.vT, v = r.v;
    }
  }
  struct T { // Funcs, for convince
    static void _b(Segment &x) {
      x.mid = x.L + x.R >> 1;
      if (x.L == x.R) return void((x.v = 0, x.vT = x.L));
      _b(a[x.l = ++c] = {Lg(x)});
      _b(a[x.r = ++c] = {Rg(x)});
      x.up();
    }
    static inline void B(int n) { _b(a[c = 1] = {1, Mn}); }
    static void _m(Segment &x, int L, int v) {
      if (L < x.L || L > x.R) return;
      if (!x.l) return void(x.v += v);
      child(x); _m(l, L, v); _m(r, L, v);
      x.up();
    }
    static inline void M(int L, int v) { _m(a[1], L, v); }
  };
};
namespace Solver {
  using namespace Composer;
  using SegmentTree :: T;
  
  void M(int L, int R, int v) {
    while (top[L] != top[R]) {
      if (dep[top[L]] < dep[top[R]]) swap(L, R);
      Query::Addedge(dfn[top[L]], v);
      Query::Addedge(dfn[L]+1, -v);
      L = fa[top[L]];
    }
    if (dep[L] > dep[R]) swap(L, R);
    Query::Addedge(dfn[L], v);
    Query::Addedge(dfn[R]+1, -v);
  }

  inline void FuckIt() {
    T::B(100000);
    for (int i=1; i<=n; i++) {
      for (int e=Query::hed[i]; e; e=Query::E[e].nxt) {
        int x = Query::E[e].to;
        T::M(abs(x), x > 0 ? 1 : -1);
      }
      ans[rev[i]] = SegmentTree::a[1].vT;
      if (SegmentTree::a[1].v); else ans[rev[i]] = 0;
    }
  }
};

int main() {
  I >> n >> m;
  for (int X,Y,i=1; i<n; i++) {
    I >> X >> Y;
    Graph::Addedge(X, Y);
  }
  Composer::B(n);
  for (int Src,Dest,Typ,i=1; i<=m; i++) {
    I >> Src >> Dest >> Typ;
    Solver::M(Src, Dest, Typ);
  }
  Solver::FuckIt();
  for (int i=1; i<=n; i++) O << ans[i] << NE;
  return 0;
}
