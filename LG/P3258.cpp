#include <bits/stdc++.h>
using namespace std;

const int    N = 3e5 + 15;
const auto  NE = "\n";
auto&       I  = cin;
auto&       O  = cout;

int _eval_value_ = [](){
  ios :: sync_with_stdio(0);
  I.tie(0);
  return 0;
}(), n, a[N];

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
namespace LCA {
  const int D = 20;
  int fa[D][N] = {0}, depth[N] = {0};
  void Init(int x = 1, int faa = 0) { // initialize LCA information
    for (int e=hed[x]; e; e=edges[e].nxt) {
      int y = edges[e].to;
      if (y != faa) {
        depth[y] = depth[x] + 1;
        fa[0][y] = x;
        Init(y, x);
      }
    }
  }
  void InitLCA() { // initialize fa[][] information
    for (int d=1; d<D; ++d) {
      for (int i=1; i<=n; i++) {
        fa[d][i] = fa[d-1][fa[d-1][i]];
      }
    }
  }
  int LCA(int x, int y) {
    if (depth[x] > depth[y]) swap(x, y);
    int hx = depth[x], hy = depth[y];
    for (int det = hy-hx, i=0; det; det>>=1, ++i) {
      if (det & 1) y = fa[i][y];
    }
    if (x == y) return x;
    for (int i=D-1; i>=0; --i) {
      if (fa[i][x] == fa[i][y]) continue;
      x = fa[i][x];
      y = fa[i][y];
    }
    return fa[0][x];
  }
};
namespace Solver {
  int val[N] = {0}, ans[N] = {0};
  auto _fuck_it_ = [](int src, int dest) {
    int lca = LCA::LCA(src, dest);
    ++val[src]; ++val[dest];
    --val[LCA::fa[0][lca]]; --val[lca];
  };
  void FlagRoute() {
    for (int i=1; i<n; i++) {
      _fuck_it_(a[i], a[i+1]);
    }
  }
  int CalcPath(int x=1, int fa=0) {
    ans[x] += val[x];
    for (int e=hed[x]; e; e=edges[e].nxt) {
      int y = edges[e].to;
      if (y != fa) {
        ans[x] += CalcPath(y, x);
      } 
    }
    return ans[x];
  }
  void CalcOffset() {
    for (int i=2; i<=n; i++) {
      ans[a[i]] += -1;
    }
  }
};

int main() {
  I >> n;
  for (int i=1; i<=n; i++) {
    I >> a[i];
  }
  for (int x, y, i=1; i<n;  i++) {
    I >> x >> y;
    AddEdge(x, y);
  }
  LCA::Init();
  LCA::InitLCA();
  Solver::FlagRoute();
  Solver::CalcPath();
  Solver::CalcOffset();
  for (int i=1; i<=n; i++) {
    O << Solver::ans[i] << NE;
  }
  return 0;
}
