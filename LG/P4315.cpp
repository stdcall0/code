#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 1e5 + 5;

struct Trios {
  LL s, h, l;
};
struct SegmentTree {
  struct Node {
    int L, R, l, r;
    LL vs, vh, vl;
    bool ti;
  };

  int c;
  Node a[N * 4];

  SegmentTree() {
    c = 1;
  }

  inline void up(int x) {
    a[x].vs = a[a[x].l].vs + a[a[x].r].vs;
    a[x].vh = std::max(a[a[x].l].vh, a[a[x].r].vh);
    a[x].vl = std::min(a[a[x].l].vl, a[a[x].r].vl);
  }
  inline void apply(int x, bool ti) {
    if (x <= 0) return;
    if (ti) {
      a[x].ti ^= 1;
      LL t = a[x].vl;
      a[x].vl = -a[x].vh;
      a[x].vh = -t;
      a[x].vs = -a[x].vs;
    }
  }
  inline void down(int x) {
    apply(a[x].l, a[x].ti),
    apply(a[x].r, a[x].ti);
    a[x].ti = false;
  }

  void build(int l, int r, int *v, int x = 1) {
    a[x] = {l, r};
    if (l == r) {
      a[x].vs = a[x].vh = a[x].vl = v[l];
      return;
    }
    int mid = l + r >> 1;
    build(l, mid, v, a[x].l = ++c),
    build(mid + 1, r, v, a[x].r = ++c);
    up(x);
  }
  void modifyS(int p, int v, int x = 1) {
    if (p < a[x].L || p > a[x].R)
      return;
    down(x);
    if (p <= a[x].L && a[x].R <= p) {
      a[x].vs = a[x].vh = a[x].vl = v;
      return;
    }
    modifyS(p,v, a[x].l);
    modifyS(p,v, a[x].r);
    up(x);
  }

  void modify(int l, int r, int x = 1) {
    if (r < a[x].L || l > a[x].R)
      return;
    down(x);
    if (l <= a[x].L && a[x].R <= r) {
      apply(x, true);
      return;
    }
    modify(l, r, a[x].l);
    modify(l, r, a[x].r);
    up(x);
  }

  Trios query(int l, int r, int x = 1) {
    if (r < a[x].L || l > a[x].R)
      return {0, -1145141919810ll, +1145141919810ll};
    down(x);
    if (l <= a[x].L && a[x].R <= r)
      return {a[x].vs, a[x].vh, a[x].vl};
    Trios v1 = query(l, r, a[x].l),
          v2 = query(l, r, a[x].r);
    up(x);
    return {v1.s + v2.s, std::max(v1.h, v2.h), std::min(v1.l, v2.l)};
  }
} T;

int n;
int cnt = 0, hed[N], to[N * 2], nxt[N * 2], val[N * 2], bnd[N];
int tick = 0, top[N], fa[N], sz[N], son[N], dfn[N], dep[N], def[N];

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
    ++u; ++v;
    addEdge(u, v, w);
    addEdge(v, u, w);
  }
  dfs1(1, 1); dfs2(1, 1, 0);
  T.build(1, n, def);
}

int w, tt;
inline void fn(LL &v, int l, int r) {
  if (tt == 0) {
    T.modify(l, r);
  } else if (tt == 1) {
    v += T.query(l, r).s;
  } else if (tt == 2) {
    v = std::max(v, T.query(l, r).h);
  } else
    v = std::min(v, T.query(l, r).l);
}
inline LL core(int x, int y, LL no) {
  LL ans = no;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]])
      std::swap(x, y);
    fn(ans, dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y])
    std::swap(x, y);
  fn(ans, dfn[x] + 1, dfn[y]);
  return ans;
}

inline void queries() {
  static char op[10];
  static int x, y, m;
  scanf("%d", &m);
  while (m--) {
    scanf("%s%d%d", op, &x, &y);
    if (op[0] == 'C') {
      T.modifyS(dfn[bnd[x]], y);
    } else { ++x; ++y; if (op[0] == 'N') {
      tt = 0;
      core(x, y, 0);
    } else if (op[0] == 'S') {
      tt = 1;
      printf("%d\n", core(x, y, 0));
    } else if (op[1] == 'A') {
      tt = 2;
      printf("%d\n", core(x, y, -1145141919810ll));
    } else {
      tt = 3;
      printf("%d\n", core(x, y, +1145141919810ll));
    } }
  }
}

int main() { read(); queries(); return 0; }
