#include <bits/stdc++.h>
using namespace std;

auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

const int N = 1e6 + 5;
int n, m, a_[N], rid[N];

namespace SegTree {
#define ig Segment &l=a[x.l], &r=a[x.r]
#define igg Segment &l=a[y.l], &r=a[y.r]
  struct Segment {
    int L, R, mid;
    int l, r;          // Left and Right node ID
    int v;
    inline void up() {
      // nothing here.
    }
  } a[40000555];
  int ac, rc; // segment count, revision count
  inline int clone(const Segment &x) {
    a[++ac] = x;
    return ac;
  }
  inline void b(Segment &x) {
    x.mid = x.L + x.R >> 1;
    if (x.L == x.R) return void(x.v = a_[x.L]);
    b(a[x.l = ++ac] = {x.L, x.mid});
    b(a[x.r = ++ac] = {x.mid+1, x.R});
    x.up();
  }
  int q(Segment &x, int L) {
    if (x.L == x.R) return x.v;
    ig; if (L <= x.mid) return q(l, L);
    else return q(r, L);
  }
  int c(Segment &x, int L, int v) {
    int ir = clone(x); Segment &y = a[ir];
    if (x.L == x.R) {
      y.v = v;
      return ir;
    }
    igg; if (L <= y.mid) y.l = c(l, L, v);
    else y.r = c(r, L, v);
    y.up();
    return ir;
  }
  struct Revision {
    int root;
    inline int Q(int x) { return q(a[root], x); }
    inline int C(int, int);
  } r[N];
  inline int Revision::C(int x, int y) {
    r[++rc].root = c(a[root], x, y);
    return rc;
  }
  inline void B(int n) {
    r[rc = 1] = {1};
    b(a[ac = 1] = {1, n});
  }
};

int main() {
  cin >> n >> m;
  for (int i=1; i<=n; i++) {
    cin >> a_[i];
  }
  SegTree::B(n);
  rid[0] = 1;
  for (int i=1; i<=m; ++i) {
    int v, opt, x, y;
    cin >> v >> opt >> x;
    if (opt == 1) {
      cin >> y;
      rid[i] = SegTree::r[rid[v]].C(x, y);
    } else {
      cout << SegTree::r[rid[v]].Q(x) << endl;
      rid[i] = rid[v];
    }
  }
  return 0;
}