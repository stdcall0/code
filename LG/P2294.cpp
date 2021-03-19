#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 105;
const int M = 3005;

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
    memset(tot, 0, sizeof(tot));
  }
  inline bool solve(int S) {
    while (!Q.empty()) Q.pop();
    memset(vis, 0, sizeof(vis));
    memset(dis, -0x3f, sizeof(dis));
    Q.push(S); vis[S] = 1; dis[S] = 0;
    while (!Q.empty()) {
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
  for (int T = R(); T--; ) {
    n = R(), m = R();
    Solver::init(n);
    for (int l,r,v, i=1; i<=m; i++) {
      l = R(), r = R(), v = R();
      G::_put(l-1, r, v);
      G::_put(r, l-1, -v);
    }
    for (int i=0; i<=n; i++) if (!Solver::tot[i] && !Solver::solve(i)) {
      puts("false");
      goto e;
    }
    puts("true");
    e: ;
  }
  return 0;
}
