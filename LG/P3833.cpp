#include <cstdio>
#include <vector>

typedef long long LL;
const int N = 1e5 + 5;

struct Node {
  int L, R, l, r;
  LL v, t;
};

int n, cc = 1;
int fa[N], sz[N], son[N], top[N], dep[N];
int dfn[N], rnk[N], ti = 0;
Node a[N * 4];
std::vector<int> G[N];

inline void apply(int x, LL t) {
  a[x].v += t * (a[x].R - a[x].L + 1);
  a[x].t += t;
}
inline void down(int x) {
  if (a[x].t) {
    apply(a[x].l, a[x].t);
    apply(a[x].r, a[x].t);
  }
  a[x].t = 0;
}
inline void up(int x) {
  a[x].v = a[a[x].l].v + a[a[x].r].v;
}
void build(int l, int r, int x = 1) {
  a[x] = {l, r};
  if (l == r) return;
  int mid = l + r >> 1;
  build(l, mid, a[x].l = ++cc);
  build(mid+1, r, a[x].r = ++cc);
}
void modify(int l, int r, LL v, int x = 1) {
  if (a[x].R < l || a[x].L > r) return;
  down(x);
  if (l <= a[x].L && a[x].R <= r) {
    apply(x, v);
    return;
  }
  modify(l, r, v, a[x].l);
  modify(l, r, v, a[x].r);
  up(x);
}
LL query(int l, int r, int x = 1) {
  if (a[x].R < l || a[x].L > r) return 0;
  down(x);
  if (l <= a[x].L && a[x].R <= r)
    return a[x].v;
  LL v = query(l, r, a[x].l) + query(l, r, a[x].r);
  return v;
}

void dfs1(int x, int fa) {
  sz[x] = 1; son[x] = -1;
  dep[x] = dep[fa] + 1;
  for (int y : G[x]) {
    if (y == fa) continue;
    dfs1(y, x);
    sz[x] += sz[y];
    if (son[x] == -1 || sz[y] > sz[son[x]])
      son[x] = y;
  }
}
void dfs2(int x, int tp) {
  dfn[x] = ++ti; rnk[ti] = x;
  top[x] = tp;
  if (son[x] != -1)
    dfs2(son[x], tp);
  for (int y : G[x])
    if (y != fa[x] && y != son[x])
      dfs2(y, y);
}

inline void read() {
  static int x, y;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d%d", &x, &y);
    ++x, ++y;
    fa[y] = x;
    G[x].push_back(y),
    G[y].push_back(x);
  }
  dfs1(1, 1); dfs2(1, 1);
  build(1, n);
}
inline void queries(){
  static int m, u, v, d;
  static char op[5];
  scanf("%d", &m);
  while (m--) {
    scanf("%s%d", op, &u); ++u;
    if (op[0] == 'A') {
      scanf("%d%d", &v,&d); ++v;
      while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
          std::swap(u, v);
        modify(dfn[top[u]], dfn[u], d);
        u = fa[top[u]];
      }
      if (dep[u] > dep[v])
        std::swap(u, v);
      modify(dfn[u], dfn[v], d);
    } else {
      printf("%lld\n", query(dfn[u], dfn[u] + sz[u] - 1));
    }
  }
}

int main() { read(); queries(); return 0; }
