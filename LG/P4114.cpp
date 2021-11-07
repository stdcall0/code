#include <cstdio>
#include <algorithm>

const int N = 1e5 + 5;

struct SegmentTree {
  struct Node {
    int L, R;
    int l, r, v;
  };

  int c;
  Node a[N * 4];

  SegmentTree() {
    c = 1;
  }

  void build(int l, int r, int *v, int x = 1) {
    a[x] = {l, r, 0, 0, 0};
    if (l == r) {
      a[x].v = v[l];
      return;
    }
    int mid = l + r >> 1;
    build(l, mid, v, a[x].l = ++c),
    build(mid + 1, r, v, a[x].r = ++c);
    a[x].v = std::max(a[a[x].l].v, a[a[x].r].v);
  }

  void modify(int p, int v, int x = 1) {
    if (p < a[x].L || p > a[x].R)
      return;
    if (p == a[x].L && p == a[x].R) {
      a[x].v = v;
      return;
    }
    modify(p, v, a[x].l),
    modify(p, v, a[x].r);
    a[x].v = std::max(a[a[x].l].v, a[a[x].r].v);
  }

  int query(int l, int r, int x = 1) {
    if (r < a[x].L || l > a[x].R)
      return 0;
    if (l <= a[x].L && a[x].R <= r)
      return a[x].v;

    int v1 = query(l, r, a[x].l),
        v2 = query(l, r, a[x].r);
    return std::max(v1, v2);
  }
} T;

int n;
int cnt = 0, hed[N], to[N * 2], nxt[N * 2], val[N * 2];
int tick = 0, top[N], fa[N], sz[N], son[N], dfn[N], dep[N], bnd[N];
int def[N];

namespace Helper {
  inline void addEdge(int x, int y, int v) {
    to[++cnt] = y;
    nxt[cnt] = hed[x];
    val[cnt] = v;
    hed[x] = cnt;
  }

  void dfs1(int x, int fa) {
    sz[x] = 1; son[x] = -1; ::fa[x] = fa;
    for (int mx = 0, i = hed[x]; i; i = nxt[i]) {
      if (to[i] != fa) {
        bnd[(i + 1) / 2] = to[i];
        dep[to[i]] = dep[x] + 1;
        dfs1(to[i], x);
        sz[x] += sz[to[i]];
        if (sz[to[i]] > mx) {
          mx = sz[to[i]];
          son[x] = to[i];
        }
      }
    }
  }
  void dfs2(int x, int tp, int ev) {
    top[x] = tp; dfn[x] = ++tick; def[dfn[x]] = ev;
    if (son[x] == -1) return;
    for (int i = hed[x]; i; i = nxt[i])
      if (to[i] == son[x]) {
        dfs2(to[i], tp, val[i]);
        break;
      }
    for (int i = hed[x]; i; i = nxt[i])
      if (to[i] != fa[x] && to[i] != son[x])
        dfs2(to[i], to[i], val[i]);
  }

  inline void read() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
      static int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      addEdge(u, v, w);
      addEdge(v, u, w);
    }
    dfs1(1, 1); dfs2(1, 1, 0);
    T.build(1, n, def);
  }
};

namespace Solver {
  inline void queries() {
    static char op[10];
    static int x, y;

    while (scanf("%s", op) == 1 && op[0] != 'D') {
      scanf("%d%d", &x, &y);
      if (op[0] == 'C') {
        T.modify(dfn[bnd[x]], y);
      } else {
        int ans = 0;
        while (top[x] != top[y]) {
          if (dep[top[x]] < dep[top[y]])
            std::swap(x, y);
          ans = std::max(ans, T.query(dfn[top[x]], dfn[x]));
          x = fa[top[x]];
        }
        if (dep[x] > dep[y])
          std::swap(x, y);
        ans = std::max(ans, T.query(dfn[x] + 1, dfn[y]));
        printf("%d\n", ans);
      }
    }
  }
};

int main() {
  Helper::read();
  Solver::queries();
  return 0;
}
