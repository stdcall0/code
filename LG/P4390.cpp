#include <bits/stdc++.h>
using namespace std;

int n, Q, ans[10005], tp = 0;
struct BIT {
  const static int S = 2000010; int t[S + 5];
  inline int get(int x) { x += 5; int _=0; for (; x; x -= x & (-x)) _ += t[x]; return _; }
  inline void add(int x, int v=1) { x += 5; for (; x <= S; x += x & (-x)) t[x] += v; }
} T;
struct node {
  int tim, x, y, typ, val;
  bool operator< (const node &r) const
    { return tim == r.tim ? (x == r.x ? (y == r.y ? typ == 0 : y < r.y) : x < r.x) : tim < r.tim; }
} A[200005];
bool cmp(const node&a, const node&b) { return a.x == b.x ? (a.y == b.y ? a.typ == 0 : a.y < b.y) : a.x < b.x; }
void cdq(int l, int r) {
  if (l>=r) return;
  int mid = l+r >> 1;
  cdq(l, mid); cdq(mid+1, r);
  sort(A+l, A+mid+1, cmp); sort(A+mid+1, A+r+1, cmp);
  int j = l;
  for (int i = mid+1; i <= r; ++i) {
    while (j <= mid && A[j].x <= A[i].x) {
      if (A[j].typ == 0) T.add(A[j].y, A[j].val);
      ++j;
    }
    if (A[i].typ != 0)
      ans[A[i].val] += A[i].typ * T.get(A[i].y);
  }
  for (int i = l; i < j; ++i)
    if (A[i].typ == 0) T.add(A[i].y, -A[i].val);
}

int main() {
  int _dis, op, x, y, p, q, v, m=0, ts=0;
  scanf("%d%d", &_dis, &n);
  while (scanf("%d", &op) == 1 && op != 3) {;
    if (op == 1) {
      scanf("%d%d%d", &x,&y,&v);
      A[++tp] = {++ts, x, y, 0, v};
    } else {
      scanf("%d%d%d%d", &x,&y,&p,&q); ++m;
      A[++tp] = {ts, x - 1, y - 1, 1, m};
      A[++tp] = {ts, x - 1, q, -1, m};
      A[++tp] = {ts, p, y - 1, -1, m};
      A[++tp] = {ts, p, q, 1, m};
    }
  }
  sort(A+1, A+1+tp);
  cdq(1, tp);
  for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
  return 0;
}