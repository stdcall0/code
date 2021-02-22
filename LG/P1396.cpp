#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

const int N = 1e4 + 5, M = 2e4 + 5;
int n, m;

namespace G {
  struct edge {
    int to, nxt, val;
  } edges[M * 2];
  int hed[N], cntEdge = 0;
  inline void reset() { memset(hed, cntEdge = 0, sizeof(hed)); }
  auto _r0_graph_ns = ([]{ return reset(), 0; })();
  inline void put(int from, int to, int weight) {
    auto _put = [&](int x, int y, int z) {
      edges[++cntEdge] = (edge){y, hed[x], z};
      hed[x] = cntEdge;
    };
    _put(from, to, weight); _put(to, from, weight);
  }
  struct graph_iterator {
    int eid; // 0 for end loop
    graph_iterator(int _) : eid(_) {}
    inline edge& operator->() const {
      return edges[eid];
    }
    inline graph_iterator & operator++() {
      eid = edges[eid].nxt;
      return *this;
    }
  } _g_end(0);
  struct graph_wrapper {
    int src; graph_wrapper(int _) : src(_) {}
    inline graph_iterator begin() const { return graph_iterator(hed[src]); }
    inline graph_iterator & end() const { return _g_end; }
  };
  inline graph_wrapper get(int src) { return graph_wrapper(src); }
};
struct UnionSet {
  int fa[N], siz[N], n;
  inline void reset() { for (int i=1; i<=n; i++) fa[i] = i, siz[i] = 1; }
  inline void resize(int nn) { n = nn; reset(); }
  inline int get(int x) {
    if (fa[x] != x) return fa[x] = get(fa[x]);
    return x;
  }
  inline bool together(int x, int y) {
    x = get(x), y = get(y);
    if (x == y) return false;
    if (siz[x] > siz[y]) {
      siz[x] += siz[y];
      return fa[y] = x;
    } else {
      siz[y] += siz[x];
      return fa[x] = y;
    }
  }
  inline bool same(int x, int y) {
    x = get(x), y = get(y);
    return x == y;
  }
} U;
struct rawEdge {
  int from, to, weight;
  rawEdge() {}
  rawEdge(int u, int v, int w) : from(u), to(v), weight(w) {}
  inline bool operator<(const rawEdge& r) const {
    return weight < r.weight;
  }
} E[M];

int main() {
  int s, t;
  cin >> n >> m >> s >> t;
  U.resize(n);
  for (int i=1; i<=m; i++) {
    cin >> E[i].from >> E[i].to >> E[i].weight;
  }
  sort(Rn(E, m));
  for (int i=1; i<=m; i++) {
    U.together(E[i].from, E[i].to);
    if (U.same(s, t)) {
      cout << E[i].weight << endl;
      return 0;
    }
  }
  puts("NMSL NMSL");
  return 0;
}
