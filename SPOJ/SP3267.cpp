#include <bits/stdc++.h>
using namespace std;
// #define NDEBUG
// #pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
// #pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const int N = 3e4 + 5;
const int POOL = N * 21;
int n, a[N], pre[(int)1e6 + 5], la[N], T[N];

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
    int L, R, mid, l, r, v;
  } pool[POOL];
  int pc = 0;
  inline node& g(int x) { return pool[x]; }
  inline int alloc(int src) {
    ++pc; assert(pc < POOL);
    pool[pc] = pool[src]; return pc;
  }
  inline void up(node &x) {
    x.v = pool[x.l].v + pool[x.r].v;
  }

  void _build(int y) {
    node &x = g(y);
    if (x.L == x.R) return;
    pool[++pc] = {x.L, x.mid, x.L + x.mid >> 1};
    _build(x.l = pc);
    pool[++pc] = {x.mid+1, x.R, x.mid+x.R+1 >> 1};
    _build(x.r = pc);
  }
  void _change(int &y, int at, int v) {
    node& x = g(y = alloc(y));
    if (x.L == x.R) return void(x.v += v);
    if (at <= x.mid) _change(x.l, at, v);
    else _change(x.r, at, v);
    up(x);
  }

  inline int change(int root, int at, int v) {
    int ret = 0; g(0) = pool[root];
    _change(ret, at, v); return ret;
  }
  int query(int y1, int y2, int L, int R) {
    node &x1 = g(y1), &x2 = g(y2);
    if (x1.L > R || x1.R < L) return 0;
    if (L <= x1.L && x1.R <= R) return x2.v - x1.v;
    return query(x1.l, x2.l, L, R) + query(x1.r, x2.r, L, R);
  }

  inline int build(int n) {
    pool[pc = 1] = {1, n, 1 + n >> 1};
    _build(1); return 1;
  }
};

int main() {
  cin >> n; T[0] = Tr::build(n);
  for (int i=1; i<=n; i++) {
    cin >> a[i];
    la[i] = pre[a[i]] + 1; pre[a[i]] = i;
    T[i] = Tr::change(T[i-1], la[i], 1);
  }
  int q; cin >> q;
  for (int l,r; q--; ) {
    cin >> l >> r;
    cout << Tr::query(T[l-1], T[r], 1, l) << endl;
  }
  return 0;
}
