#include <string.h>

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
