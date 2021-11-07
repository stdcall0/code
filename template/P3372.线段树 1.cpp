#include <cstdio>

typedef long long LL;
const int maxN = 1e5 + 5;

struct SegmentTree {
  struct Node {
    int L, R, l, r;
    LL v, tag;
  } a[maxN * 4];

  int cnt = 1;

  inline void tagit(Node &x, LL v) {
    x.v += (x.R - x.L + 1) * v;
    x.tag += v;
  }

  inline void down(Node &x) {
    if (x.l)
      tagit(a[x.l], x.tag);
    if (x.r)
      tagit(a[x.r], x.tag);
    x.tag = 0;
  }

  inline void up(Node &x) {
    x.v = a[x.l].v + a[x.r].v;
  }

  void build(int L, int R, int *s, int x = 1) {
    a[x] = {L, R, 0, 0, 0, 0};
    if (L == R) {
      a[x].v = s[L];
      return;
    }

    int mid = L + R >> 1;

    a[x].l = ++cnt;
    a[x].r = ++cnt;
    build(L, mid, s, a[x].l);
    build(mid+1, R, s, a[x].r);

    up(a[x]);
  }

  void modify(int L, int R, int v, int x = 1) {
    if (x == 0 || L > a[x].R || R < a[x].L)
      return;

    if (L <= a[x].L && a[x].R <= R) {
      tagit(a[x], v);
      return;
    }

    down(a[x]);
    modify(L, R, v, a[x].l);
    modify(L, R, v, a[x].r);

    up(a[x]);
  }

  LL query(int L, int R, int x = 1) {
    if (x == 0 || L > a[x].R || R < a[x].L)
      return 0;

    if (L <= a[x].L && a[x].R <= R)
      return a[x].v;

    down(a[x]);
    return query(L, R, a[x].l) + query(L, R, a[x].r);
  }
};

int n, m;
int a[maxN];
SegmentTree T;

int main() {
  int op, x, y, z;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);

  T.build(1, n, a);
  while (m--) {
    scanf("%d%d%d", &op, &x, &y);
    if (op == 1) {
      scanf("%d", &z);
      T.modify(x, y, z);
    } else {
      printf("%lld\n", T.query(x, y));
    }
  }
  return 0;
}