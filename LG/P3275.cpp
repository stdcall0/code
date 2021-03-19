#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5;
const int M = N * 3;

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

namespace G {
  struct edge {
    int to, nxt, val;
  } edges[M * 2];
  int hed[N], cntEdge = 0;
  inline void reset() { memset(hed, cntEdge = 0, sizeof(hed)); }
  auto _r0_graph_ns = ([]{ return reset(), 0; })();
  auto _put = [](int x, int y, int z) {
    // printf("Edge: %d -> %d = %d\n", x,y,z);
    edges[++cntEdge] = (edge){y, hed[x], z};
    hed[x] = cntEdge;
  };
  auto put = [](int from, int to, int weight) {
    _put(from, to, weight); _put(to, from, weight);
  };
};
namespace Solver {
  int n, dis[N], tot[N];
  bool vis[N];
  queue<int> Q;
  inline void init(int n_) {
    n = n_; G::reset();
    for (int i=n; i>=1; i--) G::_put(0, i, 1);
  }
  inline bool solve() {
    while (!Q.empty()) Q.pop();
    // memset(dis, -0x3f, sizeof(dis));
    dis[0] = 0; vis[0] = 1;
    Q.push(0); while (!Q.empty()) {
      int x = Q.front(); Q.pop();
      vis[x] = 0; for (int e = G::hed[x]; e; e = G::edges[e].nxt) {
        G::edge E = G::edges[e];
        if (dis[x] + E.val > dis[E.to]) {
          dis[E.to] = dis[x] + E.val;
          if (!vis[E.to]) {
            vis[E.to] = 1;
            Q.push(E.to);
            if (++tot[E.to] >= n) {
              return false;
            }
          }
        }
      }
    }
    return true;
  }
};

int n, m;

int main() {
  n = R(), m = R();
  Solver::init(n);
  auto _ = G::_put; for (int op, x, y, z; m--; ) {
    op = R(), x = R(), y = R();
    switch (op) {
      case 1:
        _(x, y, 0); _(y, x, 0); break;
      case 2:
        if (x == y) { puts("-1"); return 0; }
        _(x, y, 1); break;
      case 3:
        _(y, x, 0); break;
      case 4:
        if (x == y) { puts("-1"); return 0; }
        _(y, x, 1); break;
      case 5:
        _(x, y, 0); break;
    }
  }
  if (!Solver::solve()) puts("-1");
  else {
    ll res = 0;
    for (int i=1; i<=n; i++) res += Solver::dis[i];
    printf("%lld\n", res);
  }
  return 0;
}
