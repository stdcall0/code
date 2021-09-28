#include <bits/stdc++.h>
using namespace std;

const int det = 10;
int n, Q, ans[500005], tp = 0;
struct BIT {
  const static int S = 10000000 + det; int t[S + 5];
  inline void clear() { memset(t, 0, sizeof(t)); }
  inline int lowbit(int x) { return x & (-x); }
  inline int get(int x) { int _=0; for (; x; x -= lowbit(x)) _ += t[x]; return _; }
  inline void add(int x, int v=1) { for (; x <= S; x += lowbit(x)) t[x] += v; }
  inline int rng(int l, int r) { return l <= r ? (get(r) - (l ? get(l - 1) : 0)) : 0; }
} T;
struct node {
  int x, y, typ, val; // typ = 0: tree, val=cnt; typ != 0: query, val = alignid
  inline void proc() { if (typ != 0) ans[val] += typ * T.get(y+det); else T.add(y+det); }
  bool operator< (const node &r) const { return x == r.x ? (y == r.y ? abs(typ) < abs(r.typ) : y < r.y) : x < r.x; }
} A[2500005];

int main() {
  scanf("%d%d", &n, &Q);
  for (int i = 1; i <= n; ++i) {
    int x, y; scanf("%d%d", &x, &y);
    A[++tp] = {x, y, 0, 1};
  }
  for (int i = 1; i <= Q; ++i) {
    int x, y, p, q; scanf("%d%d%d%d", &x, &y, &p, &q);
    A[++tp] = {x - 1, y - 1, 1, i};
    A[++tp] = {x - 1, q, -1, i};
    A[++tp] = {p, y - 1, -1, i};
    A[++tp] = {p, q, 1, i};
  }
  sort(A + 1, A + 1 + tp);
  for (int i = 1; i <= tp; ++i) A[i].proc();
  for (int i = 1; i <= Q; ++i) printf("%d\n", ans[i]);
  return 0;
}