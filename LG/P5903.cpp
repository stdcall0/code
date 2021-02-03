#include <bits/stdc++.h>
using namespace std;

typedef long long  ll;
const int    N = 5e5 + 15;
const auto  NE = "\n";
auto&       I  = cin ;
auto&       O  = cout;

int _eval_value_ = [](){
  ios :: sync_with_stdio(0);
  I.tie(0);
  return 0;
}(), n, Q, R;

typedef unsigned int uInt;
uInt s;
inline uInt getNext(uInt x) { x ^= x << 13; x ^= x >> 17; x ^= x << 5; return s = x; }

namespace Graph {
  int hed[N], gcnt = 0;
  struct edge { int to, nxt; } E[N * 4];
  auto _add = [](int x, int y) {
    E[++gcnt] = (edge){y, hed[x]}; hed[x] = gcnt;
  };
  inline void Addedge(int x, int y) {
    _add(x, y); _add(y, x);
  }
};
namespace Solver {
  int fa[21][N], d[N];
  using namespace Graph;
  inline void dfs(int x) {
    d[x] = d[fa[0][x]] + 1;
    for (int e=hed[x]; e; e=E[e].nxt) {
      int y = E[e].to;
      if (y != fa[0][x]) {
        fa[0][y] = x;
        dfs(y);
      }
    }
  }
  inline void resc() {
    for (int j=1; j<=20; ++j)
      for (int i=1; i<=n; i++) 
        fa[j][i] = fa[j-1][fa[j-1][i]];
  }
};

int main() {
  I >> n >> Q >> s;
  for (int i=1,f; i<=n; i++) {
    I >> f;
    if (f) Graph::Addedge(f, i); else R = i;
  }
  Solver::dfs(R); Solver::resc();
  int lastAns = 0;
  long long outputAns = 0;
  for (int i=1; i<=Q; i++) {
    register int x = (getNext(s) ^ lastAns) % n + 1;
    register int k = (getNext(s) ^ lastAns) % Solver::d[x];
    using namespace Solver;
    for (register int i=20; i>=0; i--) {
      if (k & (1 << i)) x = fa[i][x];
    }
    outputAns ^= 1ll * (lastAns = x) * i;
  }
  O << outputAns << NE;
  return 0;
}
