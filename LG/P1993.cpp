#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 5e3 + 5;
const int M = N * 6;

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
    for (int i=1; i<=n; i++) {
      G::_put(0, i, 0);
    }
  }
  auto put_leq = [](int x, int y, int z) { G::_put(y, x, z); }; // X - Y <= Z
  auto put_le = [](int x, int y, int z) { put_leq(x, y, z-1); }; // X - Y < Z
  auto put_geq = [](int x, int y, int z) { put_leq(y, x, -z); }; // X - Y >= Z
  auto put_ge = [](int x, int y, int z) { put_leq(y, x, -z-1); }; // X - Y > Z
  auto put_eq = [](int x, int y) { put_leq(x, y, 0); put_leq(y, x, 0); }; // X == Y
  inline bool solve() {
    while (!Q.empty()) Q.pop();
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0; vis[0] = 1;
    Q.push(0); while (!Q.empty()) {
      int x = Q.front(); Q.pop();
      vis[x] = 0; for (int e = G::hed[x]; e; e = G::edges[e].nxt) {
        G::edge E = G::edges[e];
        // printf("Visiting %d from %d, val %d\n", E.to, x, E.val);
        if (dis[x] + E.val < dis[E.to]) {
          dis[E.to] = dis[x] + E.val;
          // printf("Updating dis %d: to %d\n", E.to, dis[E.to]);
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
  for (int op, x, y, z; m--; ) {
    op = R(), x = R(), y = R();
    switch (op) {
      case 1: // A - B >= C
        z = R();
        Solver::put_geq(x, y, z);
        break;
      case 2: // A - B <= C
        z = R();
        Solver::put_leq(x, y, z);
        break;
      case 3:
        Solver::put_eq(x, y);
    }
  }
  puts(Solver::solve() ? "Yes" : "No");
  return 0;
}
