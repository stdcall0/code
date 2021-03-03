#include <bits/stdc++.h>
using namespace std;
// #define NDEBUG
// #pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
// #pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const int N = 2e5 + 5;
const int POOL = N * 18;
int n, m, a[N], b[N];

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

namespace Tr {
  struct node {
    int L, R, mid, l, r, v; // v is number counts
  } pool[POOL];
  int pc = 0, rc = 0; // pool count, revision count;
  inline node& g(int x) { return pool[x]; }
  inline int alloc(int src) {
    ++pc; assert(pc < POOL);
    pool[pc] = pool[src]; return pc;
  }
  inline void up(node &x) {
    x.v = 0;
    x.v += pool[x.l].v;
    x.v += pool[x.r].v;
  }
  void _build(int y) {
    node &x = g(y);
    if (x.L == x.R) return;
    pool[++pc] = {x.L, x.mid, x.L + x.mid >> 1};
    _build(x.l = pc);
    pool[++pc] = {x.mid+1, x.R, x.mid+x.R+1 >> 1};
    _build(x.r = pc);
  }
  int _qry(int y1, int y2, int k) {
    node &x1 = g(y1), &x2 = g(y2);
    if (x1.L == x1.R) return x1.L;
    int v = g(x2.l).v - g(x1.l).v;
    if (k <= v) return _qry(x1.l, x2.l, k);
    return _qry(x1.r, x2.r, k - v);
  }
  int _change(int y, int at, int v) {
    int xi = alloc(y);
    node& x = g(xi);
    if (x.L == x.R) return x.v += v, xi;
    if (at <= x.mid) {
      x.l = _change(x.l, at, v);
    } else {
      x.r = _change(x.r, at, v);
    }
    up(x);
    return xi;
  }

  struct revision {
    int root;
    inline revision change(int at, int v) {
      return {_change(root, at, v)};
    }
    inline int query(const revision &res, int k) {
      return _qry(root, res.root, k);
    }
  } rev[N];
  inline void push(const revision &res) { rev[++rc] = res; }
  inline revision build(int n) {
    pool[pc = 1] = {1, n, 1 + n >> 1};
    _build(1); return rev[rc = 0] = {1};
  }
};

int main() {
  cin >> n >> m;
  for (int i=1; i<=n; i++) {
    cin >> a[i]; b[i] = a[i];
  }
  sort(b+1, b+1+n);
  int nn = unique(b+1, b+1+n) - b-1;
  Tr::revision rt = Tr::build(nn);
  Tr::revision cur = rt;
  for (int i=1; i<=n; i++) {
    a[i] = lower_bound(b+1, b+1+nn, a[i]) - b;
    Tr::push(cur = cur.change(a[i], 1));
  }
  for (int l,r,k; m--; ) {
    cin >> l >> r >> k;
    cout << b[Tr::rev[l-1].query(Tr::rev[r], k)] << endl;
  }
  return 0;
}
