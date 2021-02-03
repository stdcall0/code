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
}(), n, Q;

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
namespace SegmentTree {
  #define child(x) Segment &l = a[(x).l], &r = a[(x).r]
  #define apply(act) l act; r act
  #define apply2(pr, act) pr l act; pr r act
  struct Segment {
    int L, R, mid;
    int l, r;
    int v, tag;
    inline int len() { return R - L + 1; }
    inline void vi(int c) { v = len() * c, tag = c+1; }
    void down();
    void up();
  } a[N * 4];
  int cnt;
  void Segment::down() {
    if (tag) {
      if (L != R) {
        child(*this);
        apply(.vi(tag - 1));
      }
      tag = 0;
    }
  }
  void Segment::up() {
    if (L != R) {
      child(*this);
      v = l.v + r.v;
    }
  }
  void _b(Segment &x, int L, int R) {
    x.mid = L + R >> 1;
    if (L == R) return;
    _b(a[x.l = ++cnt] = {L, x.mid}, L, x.mid);
    _b(a[x.r = ++cnt] = {x.mid+1, R}, x.mid+1, R);
    x.up();
  }
  inline void B(int n) { _b(a[cnt = 1] = {1, n}, 1, n); }
  int _q(Segment &x, int L, int R) {
    if (R < x.L || L > x.R) return 0;
    // O << 'Q' << x.L << ' ' << x.R << ' ' << L << ' ' << R << ' ' << x.v << endl;
    if (L <= x.L && x.R <= R) return x.v;
    x.down(); child(x);
    int o = _q(l, L, R) + _q(r, L, R);
    x.up(); return o;
  }
  inline int Q(int L, int R) { return _q(a[1], L, R); }
  void _m(Segment &x, int L, int R, int v) {
    if (R < x.L || L > x.R) return;
    if (L <= x.L && x.R <= R) return x.vi(v);
    x.down(); child(x);
    _m(l, L, R, v); _m(r, L, R, v);
    x.up();
  }
  inline void M(int L, int R, int v) { _m(a[1], L, R, v); }
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
namespace Solver {
  using namespace Composer;
  int Q(int L, int R) {
    int o = 0; while (top[L] != top[R]) {
      if (dep[top[L]] < dep[top[R]]) swap(L, R);
      o += SegmentTree::Q(dfn[top[L]], dfn[L]);
      L = fa[top[L]];
    }
    if (dep[L] > dep[R]) swap(L, R);
    return o += SegmentTree::Q(dfn[L], dfn[R]);
  }
  inline int Qt(int x) {
    return SegmentTree::Q(dfn[x], dfn[x] + siz[x] - 1);
  }
  void M(int L, int R, int v) {
    while (top[L] != top[R]) {
      if (dep[top[L]] < dep[top[R]]) swap(L, R);
      SegmentTree::M(dfn[top[L]], dfn[L], v);
      L = fa[top[L]];
    }
    if (dep[L] > dep[R]) swap(L, R);
    SegmentTree::M(dfn[L], dfn[R], v);
  }
  inline void Mt(int x, int v) {
    return SegmentTree::M(dfn[x], dfn[x] + siz[x] - 1, v);
  }
};

int main() {
  I >> n;
  for (int x, i=1; i<n; i++) {
    I >> x;
    Graph::Addedge(i + 1, x + 1);
  }
  SegmentTree::B(n);
  Composer::B(n);
  I >> Q;
  char o[10]; for (int x,i=1; i<=Q; ++i) {
    I >> o >> x; ++x;
    if (o[0] == 'i') {
      int bef = SegmentTree::a[1].v;
      Solver::M(1, x, 1);
      O << abs(SegmentTree::a[1].v - bef) << NE;
    } else {
      int bef = SegmentTree::a[1].v;
      Solver::Mt(x, 0);
      O << abs(SegmentTree::a[1].v - bef) << NE;
    }
  }
  return 0;
}
