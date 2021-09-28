#include <bits/stdc++.h>
using namespace std;

struct node {
  int a, b, c, cnt; int ans;
  bool operator< (const node& r) const { return a == r.a ? (b == r.b ? c < r.c : b < r.b) : a < r.a; }
  bool operator== (const node& r) const { return a == r.a && b == r.b && c == r.c; }
} a[100005], b[100005]; int ans[100005];
struct BIT {
  int t[200005];
  inline void clear() { memset(t, 0, sizeof(t)); }
  inline int lowbit(int x) { return x & (-x); }
  inline int get(int x) { int _=0; for (; x; x -= lowbit(x)) _ += t[x]; return _; }
  inline void add(int x, int v=1) { for (; x <= 200000; x += lowbit(x)) t[x] += v; }
  inline int rng(int l, int r) { return l <= r ? (get(r) - (l ? get(l - 1) : 0)) : 0; }
} T;

void cdq(int l, int r, bool sorted=1) {
  if (l >= r) return;
  int mid = l + r >> 1;
  cdq(l, mid); cdq(mid + 1, r);
  int x = l; for (int y = mid + 1; y <= r; ++y) {
    while (x <= mid && b[x].b <= b[y].b) T.add(b[x].c, b[x].cnt), ++x;
    b[y].ans += T.get(b[y].c);
  }
  for (int y = l; y < x; ++y) T.add(b[y].c, -b[y].cnt);
  if (sorted) sort(b+l, b+r+1, [](const node &a, const node &b) { return a.b < b.b; });
}

int main() {
  int n, k;
  scanf("%d%d", &n,&k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c);
    a[i].cnt = 1;
  }
  sort(a + 1, a + 1 + n);
  int m = 1; b[1] = a[1];
  for (int i = 2; i <= n; ++i) {
    if (a[i] == a[i-1]) ++b[m].cnt;
    else b[++m] = a[i];
  }
  cdq(1, m, 0);
  for (int i = 1; i <= m; ++i) {
    ans[b[i].ans + b[i].cnt - 1] += b[i].cnt;
  }
  for (int i = 0; i < n; ++i) printf("%d\n", ans[i]);
  return 0;
}
