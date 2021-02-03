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
}(), n, Q, cnt[N][26];
bool vis[N], ans[N];
char co[N];
struct Query {
  int dep, Qid;
};
vector<Query> qry[N];

namespace Graph {
  int hed[N], gcnt = 0;
  struct edge { int to, nxt; } E[N * 2];
  auto _add = [](int x, int y) {
    E[++gcnt] = (edge){y, hed[x]}; hed[x] = gcnt;
  };
  inline void Addedge(int x, int y) {
    _add(x, y); _add(y, x);
  }
};
namespace Composer {
  int fa[N], dep[N], siz[N], son[N], top[N], dfn[N], tim = 0;
  using namespace Graph;
  void _ba(int o) {
    son[o] = -1; siz[o] = 1;
    for (int e=hed[o]; e; e=E[e].nxt) {
      int x = E[e].to;
      if (!dep[x]) {
        dep[x] = dep[o] + 1;
        fa[x] = o; _ba(x);
        siz[o] += siz[x];
        if (son[o] == -1 || siz[x] > siz[son[o]]) son[o] = x;
      }
    }
  }
  void _bb(int o, int t) {
    top[o] = t; dfn[o] = ++tim;
    if (son[o] == -1) return;
    _bb(son[o], t);
    for (int e=hed[o]; e; e=E[e].nxt) {
      int x = E[e].to;
      if (x != fa[o] && x != son[o]) {
        _bb(x, x);
      }
    }
  }
  inline void B(int n, int R=1) { dep[R] = 1; fa[R] = 0; _ba(R); _bb(R, R); }
};
/// @namespace Solver
void calc(int o, int det) {
  using namespace Composer;
  cnt[dep[o]][co[o] - 'a'] += det;

  for (int e=hed[o]; e; e=E[e].nxt) {
    int x = E[e].to;
    if (x != fa[o] && !vis[x]) {
      calc(x, det);
    }
  }
}
void dfu(int o, bool rollback) {
  using namespace Composer;
  for (int e=hed[o]; e; e=E[e].nxt) {
    int x = E[e].to;
    if (x != fa[o] && x != son[o]) {
      dfu(x, true);
    }
  }
  if (son[o] != -1) dfu(son[o], false), vis[son[o]] = 1;
  calc(o, 1);
  vis[son[o]] = 0;
  for (Query& q : qry[o]) {
    bool & R = ans[q.Qid]; R = 1;
    bool occOdd = 0;
    for (int i=0; i<26; ++i) {
      if (cnt[q.dep][i] & 1) {
        if (occOdd) { R = 0; break; }
        occOdd = 1;
      }
    }
  }
  if (rollback) calc(o, -1);
}

int main() {
  I >> n >> Q;
  for (int fa, i=2; i<=n; i++) {
    I >> fa;
    Graph::Addedge(i, fa);
  }
  I >> (co + 1);
  Composer::B(n);
  for (int x,d, i=1; i<=Q; ++i) {
    I >> x >> d;
    Query Q = {d, i};
    qry[x].push_back(Q);
  }

  dfu(1, 0);

  for (int i=1; i<=Q; ++i) O << (ans[i] ? "Yes" : "No") << NE;
  return 0;
}
