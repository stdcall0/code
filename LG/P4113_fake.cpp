#include <cstdio>

const int N = 2e5 + 5;

struct Node {
  int L, R, l, r, v;
};

int n, c, m;
int col[N], pre[N], pre2[N], lst[N];
int rc = 0, nc = 0;
int rev[N];
Node a[N * 4];

inline void up(int x) {
  a[x].v = a[a[x].l].v + a[a[x].r].v;
}

void build(int l, int r, int x = 1) {
  a[x] = {l, r};
  if (x == 1)
    rev[nc = 0] = rc = 1;
  if (a[x].L == a[x].R)
    return;
  int mid = l + r >> 1;
  build(l, mid, a[x].l = ++rc);
  build(mid + 1, r, a[x].r = ++rc);
}

int modify(int p, int v, int x = 0) {
  if (x == 0)
    x = rev[nc],
    rev[++nc] = rc + 1;
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

int query(int l, int r, int x) {
  if (r < a[x].L || l > a[x].R)
    return 0;
  if (l <= a[x].L && a[x].R <= r)
    return a[x].v;
  return query(l, r, a[x].l) + query(l, r, a[x].r);
}

inline void read() {
  scanf("%d%d%d", &n, &c, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &col[i]);
    pre[i] = lst[col[i]];
    lst[col[i]] = i;
  }
  pre[0] = -1;
  for (int i = 1; i <= n; ++i)
    pre2[i] = pre[pre[i]];
  build(1, n);
  for (int i = 1; i <= n; ++i) {
    if (pre2[i] != -1)
      modify(pre2[i] + 1, 1);
    else
      rev[nc + 1] = rev[nc],
      ++nc;
  }
}

inline void solv() {
  int l, r;
  while (m--) {
    scanf("%d%d", &l, &r);
    printf("%d\n", query(1, l, rev[r]) - query(1, l, rev[l - 1]));
  }
}

int main() { read(); solv(); return 0; }
