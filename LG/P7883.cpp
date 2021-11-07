#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 4e5 + 5;
int n; struct Po { LL x, y; } a[N];
bool cmpx(const Po&a, const Po&b) { return a.x < b.x; }
bool cmpy(const Po&a, const Po&b) { return a.y < b.y; }
inline LL sqr(LL x) { return x * x; }
inline LL dis(int p, int q) { return sqr(a[p].x - a[q].x) + sqr(a[p].y - a[q].y); }

LL d = 1145141919810114514ll;
deque<int> Q;

void dfs(int l, int r) {
  if (l >= r) return;
  int mid = l + r >> 1;
  LL mv = a[mid].x;
  dfs(l, mid); dfs(mid+1, r);
  inplace_merge(a+l, a+mid+1, a+r+1, cmpy);
  Q.clear();
  for (int i=l; i<=r; ++i) if (sqr(a[i].x - mv) <= d) {
    while (!Q.empty() && sqr(a[i].y - a[Q[0]].y) > d) Q.pop_front();
    for (int j : Q) d = min(d, dis(i, j));
    Q.push_back(i);
  }
}

int main() {
  scanf("%d", &n);
  for (int i=1; i<=n; ++i) {
    scanf("%lld%lld", &a[i].x, &a[i].y);
  }
  sort(a+1, a+1+n, cmpx);
  dfs(1, n);
  printf("%lld\n", d);
  return 0;
}