#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

const int N = 1e5 + 5;

struct Node {
  int L, R, l, r, v;
};
struct Col {
  int v, id;
  bool operator< (const Col & r) const {
    return v < r.v;
  }
};

int n, m, ev[N], vt[N], tk = 0, c = 0;
int top[N], dfn[N], sz[N], son[N], fa[N], dep[N];
Col val[N];
std::vector<int> G[N];
int rc = 1, rt[N];
Node a[N * 20];

inline void up(int x) {
  a[x].v = a[a[x].l].v + a[a[x].r].v;
}

void build(int l, int r, int x = 1) {
  a[x] = {l, r};
  if (a[x].L == a[x].R)
    return;
  int mid = l + r >> 1;
  build(l, mid, a[x].l = ++rc);
  build(mid + 1, r, a[x].r = ++rc);
}

int modify(int p, int v, int x) {
  if (p < a[x].L || p > a[x].R)
    return x;
  int y = ++rc;
  a[y] = a[x];
  if (a[y].L == a[y].R)
    a[y].v += v;
  else {
    a[y].l = modify(p, v, a[y].l);
    a[y].r = modify(p, v, a[y].r);
    up(y);
  }
  return y;
}

void dfs1(int x, int fa) {
  ::fa[x] = fa;
  dep[x] = dep[fa] + 1;
  rt[x] = modify(ev[x], 1, rt[fa]);
  sz[x] = 1;
  son[x] = -1;
  for (int y : G[x])
    if (y != fa) {
      dfs1(y, x);
      sz[x] += sz[y];
      if (son[x] == -1 || sz[y] > sz[son[x]])
        son[x] = y;
    }
}
void dfs2(int x, int tp) {
  top[x] = tp;
  dfn[x] = ++tk;
  if (son[x] == -1)
    return;
  dfs2(son[x], tp);
  for (int y : G[x])
    if (y != fa[x] && y != son[x])
      dfs2(y, y);
}

int lca(int x, int y) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]])
      y = fa[top[y]];
    else
      x = fa[top[x]];
  }
  return dep[x] < dep[y] ? x : y;
}

inline void read() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &val[i].v),
    val[i].id = i;
  std::sort(val + 1, val + 1 + n);
  for (int i = 1; i <= n; ++i) {
    if (val[i].v != val[i - 1].v)
      ++c,
      vt[c] = val[i].v;
    ev[val[i].id] = c;
  }
  for (int x, y, i = 1; i < n; ++i) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  build(1, c);
  rt[0] = 1;
  dfs1(1, 0);
  dfs2(1, 0);
}

int query(int k, int x1, int x2, int x3, int x4) {
  if (a[x1].L == a[x1].R)
    return a[x1].L;
  int cnt = a[a[x1].l].v + a[a[x2].l].v - a[a[x3].l].v - a[a[x4].l].v;
  if (k <= cnt)
    return query(k, a[x1].l, a[x2].l, a[x3].l, a[x4].l);
  else
    return query(k - cnt, a[x1].r, a[x2].r, a[x3].r, a[x4].r);
}
inline void solv() {
  static int x, y, k, la = 0;
  while (m--) {
    scanf("%d%d%d", &x, &y, &k);
    x ^= la;
    int f = lca(x, y);
    printf("%d\n", la = vt[query(k, rt[x], rt[y], rt[f], rt[fa[f]])]);
  }
}

int main() { read(); solv(); return 0; }
