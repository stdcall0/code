#include <bits/stdc++.h>
using namespace std;

typedef long long  ll;
const int    N = 4e5 + 15;
const auto  NE = "\n";
auto&       I  = cin ;
auto&       O  = cout;

int _eval_value_ = [](){
  ios :: sync_with_stdio(0);
  I.tie(0);
  return 0;
}(), n, Q, v[N], vR[N];

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
inline int M(int R, int L, int c1, int c2) { return c1 + c2 - (R == L); }
namespace Val {
  int Lc, Rc;
};
namespace SegmentTree {
  #define child(x) Segment &l = a[(x).l], &r = a[(x).r]
  #define SegX Segment &x
  #define Lg(x) x.L, x.mid
  #define Rg(x) (x.mid+1), x.R
  #define apply(act) l act; r act
  struct Segment {
    int L, R, mid;
    int l, r;
    int vL, vR, c; // left color; right color; segment count
    int tag;       // change to
    inline void vi(int to) {
      tag = vL = vR = to;
      c = 1;
    }
    void down();
    void up();
  } a[N * 4];
  int c = 0;
  void Segment::up() {
    if (L != R) {
      child(*this);
      vL = l.vL, vR = r.vR;
      c = l.c + r.c;
      if (l.vR == r.vL) --c;
    }
  }
  void Segment::down() {
    if (L != R) {
      if (tag) {
        child(*this);
        apply(.vi(tag));
      }
      tag = 0;
    }
  }
  struct T { // Funcs, for convince
    static void _b(SegX, int L, int R) {
      x.mid = x.L + x.R >> 1;
      if (x.L == x.R) return x.vi(vR[x.L]);
      _b(a[x.l = ++c] = {Lg(x)}, Lg(x));
      _b(a[x.r = ++c] = {Rg(x)}, Rg(x));
      x.up();
    }
    static inline void B(int n) { _b(a[c = 1] = {1, n}, 1, n); }
    static int _q(SegX, int L, int R) {
      if (R < x.L || L > x.R) return 0;
      if (x.L == L) Val::Lc = x.vL;
      if (x.R == R) Val::Rc = x.vR;
      if (L <= x.L && x.R <= R) {
        return x.c;
      }
      x.down(); child(x);
      int c1 = _q(l, L, R), c2 = _q(r, L, R), o;
      if (L <= x.mid && R > x.mid) o = c1 + c2 - (l.vR == r.vL);
      else o = c1 + c2;
      x.up(); return o;
    }
    static inline int Q(int L, int R) { return _q(a[1], L, R); }
    static void _m(Segment &x, int L, int R, int v) {
      if (L < x.L || L > x.R) return;
      if (L <= x.L && x.R <= R) return x.vi(v);
      x.down(); child(x);
      _m(l, L, R, v); _m(r, L, R, v);
      x.up();
    }
    static inline void M(int L, int R, int v) { _m(a[1], L, R, v); }
  };
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
    top[o] = t; dfn[o] = ++tim; vR[dfn[o]] = v[o];
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
namespace Solver {
  using namespace Composer;
  using SegmentTree :: T;
  int Q(int L, int R) {
    int o = 0, col1 = -1, col2 = -1;
    while (top[L] != top[R]) {
      if (dep[top[L]] < dep[top[R]]) swap(L, R), swap(col1, col2);
      o += T::Q(dfn[top[L]], dfn[L]);
      if (Val::Rc == col1) --o;
      col1 = Val::Lc; L = fa[top[L]];
    }
    if (dep[L] > dep[R]) swap(L, R), swap(col1, col2);
    o += T::Q(dfn[L], dfn[R]);
    return o - (Val::Rc == col2) - (Val::Lc == col1);
  }
  void M(int L, int R, int v) {
    while (top[L] != top[R]) {
      if (dep[top[L]] < dep[top[R]]) swap(L, R);
      T::M(dfn[top[L]], dfn[L], v);
      L = fa[top[L]];
    }
    if (dep[L] > dep[R]) swap(L, R);
    T::M(dfn[L], dfn[R], v);
  }
};

int main() {
  I >> n >> Q;
  for (int i=1; i<=n; i++) I >> v[i];
  for (int x,y, i=1; i<n; i++) {
    I >> x >> y;
    Graph::Addedge(x, y);
  }
  Composer::B(n);
  SegmentTree::T::B(n);
  char o[5]; for (int x,y,z,i=1; i<=Q; ++i) {
    I >> o >> x >> y;
    if (o[0] == 'C') {
      I >> z;
      Solver::M(x, y, z);
    } else {
      O << Solver::Q(x, y) << NE;
    }
  }
  return 0;
}
