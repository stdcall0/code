#include <string.h>

const int M = 0, N = 0;

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
