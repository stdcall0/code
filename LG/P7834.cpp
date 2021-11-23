#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;
const int N = 1e5 + 5;
const int M = 5e5 + 5;

struct Edge {
  int x, y; LL v;
  bool operator< (const Edge &r) const {
    return v < r.v;
  }
};

struct InpNode {
  LL v; int id;
  bool operator< (const InpNode &r) const {
    return v < r.v;
  }
};

struct Node {
  int L, R, l, r, v;
};

int n, m, q, vc = 0, lst = 0, nc;
LL val[N * 2], mp[N];
int fa[N * 2], f[N * 2][20];
int dfn[N * 2], ti = 0, sz[N * 2];
Edge G[M];
InpNode h[N];
std::vector<int> T[N * 2];

Node a[N * 20];
int tc = 1, rev[N];

void build(int l, int r, int x = 1) {
  a[x] = {l, r};
  if (l == r) return;
  int mid = l + r >> 1;
  build(l, mid, a[x].l = ++tc);
  build(mid + 1, r, a[x].r = ++tc);
}

int modify(int p, int x) {
  if (a[x].R < p || a[x].L > p) return x;
  int y = ++tc;
  a[y] = a[x];
  if (a[y].L == a[y].R)
    a[y].v += 1;
  else
    a[y].l = modify(p, a[y].l),
    a[y].r = modify(p, a[y].r),
    a[y].v = a[a[y].l].v + a[a[y].r].v;
  return y;
}

int rank(int k, int x1, int x2) {
  auto &p = a[x1], &q = a[x2];
  if (p.L == p.R)
    return p.L;
  int v = a[q.r].v - a[p.r].v;
  if (k <= v) return rank(k, p.r, q.r);
  else return rank(k - v, p.l, q.l);
}

inline int find(int x) {
  if (fa[x] != x)
    fa[x] = find(fa[x]);
  return fa[x];
}

inline void kruskal() {
  std::sort(G + 1, G + 1 + m);
  for (int i = 1; i <= n * 2; ++i)
    fa[i] = i;
  nc = n;
  for (int i = 1; i <= m; ++i) {
    int x = find(G[i].x), y = find(G[i].y);
    if (x != y) {
      fa[x] = fa[y] = ++nc;
      T[nc].push_back(x);
      T[nc].push_back(y);
      val[nc] = G[i].v;
    }
  }
}

void dfs(int x) {
  dfn[x] = 1145141919;
  if (x <= n)
    dfn[x] = ++ti, sz[x] = 1,
    lst = rev[dfn[x]] = modify(val[x], lst);
  else
    for (int y : T[x])
      f[y][0] = x,
      dfs(y),
      sz[x] += sz[y],
      dfn[x] = std::min(dfn[x], dfn[y]);
}

inline void A() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &h[i].v);
    h[i].id = i;
  }
  std::sort(h + 1, h + 1 + n);
  for (int i = 1; i <= n; ++i) {
    if (h[i].v != h[i - 1].v)
      mp[++vc] = h[i].v;
    val[h[i].id] = vc;
  }
  for (int i = 1; i <= m; ++i)
    scanf("%d%d%lld", &G[i].x, &G[i].y, &G[i].v);
  kruskal();
  build(1, vc); lst = rev[0] = 1;
  for (int i = nc; i >= 1; --i)
    if (f[i][0] == 0) {
      f[i][0] = i;
      dfs(i);
    }
  for (int i = 1; i <= 19; ++i)
    for (int j = 1; j <= n * 2 - 1; ++j) {
      f[j][i] = f[f[j][i - 1]][i - 1];
    }
}

inline int C(int x, int v) {
  for (int i = 19; i >= 0; --i) {
    if (val[f[x][i]] <= v)
      x = f[x][i];
  }
  return x;
}

inline void B() {
  LL x, v, k, res, la = 0;
  while (q--) {
    scanf("%lld%lld%lld", &x, &v, &k);
    x = (x ^ la) % n + 1,
    k = (k ^ la) % n + 1,
    v ^= la;
    v = C(x, v);
    int L = dfn[v], R = dfn[v] + sz[v] - 1;
    if (sz[v] < k)
      puts("-1"),
      la = 0;
    else
      res = rank(k, rev[L - 1], rev[R]),
      printf("%lld\n", la = mp[res]);
  }
}

int main() {A();B();return 0;}