#include <bits/stdc++.h>
using namespace std;

typedef long long  ll;
const int    N = 3e4 + 15;
const auto  NE = "\n";
auto&       I  = cin;
auto&       O  = cout;

int _eval_value_ = [](){
  ios :: sync_with_stdio(0);
  I.tie(0);
  return 0;
}(), n, R, Q;
ll P, iv[N];

namespace Graph {
  int cnt(0), hed[N] = {0};
  struct edge {
    int to, nxt;
  } edges[N * 2];
  auto _addedge = [](int x, int y) {
    edges[++cnt] = {
      y,      // to
      hed[x]  // nxt
    };
    hed[x] = cnt;
  };
  void AddEdge(int x, int y) {
    _addedge(x, y);
    _addedge(y, x);
  }
}; using namespace Graph;
namespace Composer {
  int fa[N], dep[N], siz[N], son[N], top[N], dfn[N], tim = 0;
  void _build1(int o) {
    son[o] = -1; siz[o] = 1;
    for (int j = hed[o]; j; j = edges[j].nxt) {
      int y = edges[j].to;
      if (!dep[y]) {
        dep[y] = dep[o] + 1;
        fa[y] = o; _build1(y);
        siz[o] += siz[y];
        if (son[o] == -1 || siz[y] > siz[son[o]]) son[o] = y;
      }
    }
  }
  void _build2(int o, int t) {
    top[o] = t; dfn[o] = ++tim;
    if (son[o] == -1) return;
    _build2(son[o], t);
    for (int j = hed[o]; j; j = edges[j].nxt) {
      int y = edges[j].to;
      if (y != son[o] && y != fa[o]) _build2(y, y);
    }
  }
  inline void Build() {
    dep[R] = 1; fa[R] = 0;
    _build1(R); _build2(R, R);
  }
};
namespace SegmentTree {
#define extra(x) node &l = a[(x).l], &r = a[(x).r]
#define apply(sent) l sent; r sent
  struct node {
    int L, R, mid; // range
    int l, r;      // left node & right node
    ll  v, tag, vm;// value & tag
    inline int len() const { return R - L + 1; }
    inline void vi(ll tg) { tag = tg, v = tg * len(), vm = tag; }
    inline node& md() { v ; tag ; return *this; }
    inline void down();
    inline void up();
  } a[N * 16];
  inline void node::down() {
      if (tag) {
        if (L != R) {
          extra(*this);
          apply(.vi(tag));
        }
        tag = 0; md();
      }
  }
  inline void node::up() {
      extra(*this); v = l.v + r.v; vm = max(l.vm, r.vm); md();
  }
  int m = 0;
  void _build(node & x, int L, int R) {
    x.mid = x.L + x.R >> 1;
    if (x.L == x.R) return (void)(x.v = x.vm = iv[x.L], x.tag = x.l = x.r = 0);
    _build(a[x.l = ++m] = {x.L, x.mid}, L, R);
    _build(a[x.r = ++m] = {x.mid+1, x.R}, L, R);
    x.up(); x.tag = 0;
  }
  inline void Build(int n) { _build(a[m = 1] = {1, n}, 1, n); }
  ll _qry(node & x, int L, int R) {
    if (x.R < L || x.L > R) return 0;
    //cout << 'Q' << L << ' ' << R << " ; " << x.L << ' ' << x.R << endl;
    if (L <= x.L && x.R <= R) return x.v;
    extra(x); x.down();
    ll o = _qry(l, L, R) + _qry(r, L, R);
    x.up(); return o;
  }
  inline ll Qry(int L, int R) { return _qry(a[1], L, R); }
  ll _qrymx(node & x, int L, int R) {
    if (x.R < L || x.L > R) return -1e9;
    //cout << 'M' << L << ' ' << R << " ; " << x.L << ' ' << x.R << endl;
    if (L <= x.L && x.R <= R) return x.vm;
    extra(x); x.down();
    ll o = max(_qrymx(l, L, R), _qrymx(r, L, R));
    x.up(); return o;
  }
  inline ll QryMX(int L, int R) { return _qrymx(a[1], L, R); }
  void _modify(node & x, int L, int R, ll v) {
    if (x.R < L || x.L > R) return;
    //cout << 'C' << L << ' ' << R << " ; " << x.L << ' ' << x.R << endl;
    if (L <= x.L && x.R <= R) return x.vi(v);
    extra(x); x.down();
    _modify(l, L, R, v); _modify(r, L, R, v);
    x.up();
  }
  inline void Modify(int L, ll v) { _modify(a[1], L, L, v); } 
};
namespace Solver {
  using namespace Composer;
  inline ll Qry(int L, int R) {
    ll o = 0;
    while (top[L] != top[R]) {
      if (dep[top[L]] < dep[top[R]]) swap(L, R);
      (o += SegmentTree::Qry(dfn[top[L]], dfn[L])) ;
      L = fa[top[L]];
    }
    if (dep[L] > dep[R]) swap(L, R);
    return (o + SegmentTree::Qry(dfn[L], dfn[R])) ;
  }
  inline ll QryMX(int L, int R) {
    ll o = -1e9;
    //  cout << L << ' ' << R << ' ' <<  top[L] << ' '<< top[R] << endl;
    while (top[L] != top[R]) {
      if (dep[top[L]] < dep[top[R]]) swap(L, R);
      o = max(o, SegmentTree::QryMX(dfn[top[L]], dfn[L]));
      L = fa[top[L]];
    }
    if (dep[L] > dep[R]) swap(L, R);
    return max(o, SegmentTree::QryMX(dfn[L], dfn[R]));
  }
  inline void Modify(int L, int v) { SegmentTree::Modify(dfn[L], v); }
};

int main() {
  I >> n; P = 1e16; R = 1;
  for (int x, y, i=1; i<n; i++) {
    I >> x >> y;
    AddEdge(x, y);
  }
  Composer::Build();
  for (int i=1; i<=n; i++) {
    I >> iv[Composer::dfn[i]];
  }
  SegmentTree::Build(n);
  I >> Q; char opt[5]; int X, Y;
  while (Q--) {
    I >> opt >> X >> Y;
    if (opt[0]=='C') {
      Solver::Modify(X, Y);
    } else if (opt[1]=='M') {
      O << Solver::QryMX(X, Y) << NE;
    } else if (opt[1]=='S') {
      O << Solver::Qry(X, Y) << NE;
    }
  }
  return 0;
}