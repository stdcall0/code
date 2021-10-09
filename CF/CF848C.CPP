#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;
int n, m, tp=0, p[N];
LL ans[N];

struct BIT {
  LL T[N + 5];
  inline LL get(int x) { LL r=0;for(;x;x-=x&-x)r+=T[x];return r; }
  inline void set(int x, LL v) { for(;x<=N;x+=x&-x)T[x]+=v; }
  inline void unset(int x) { for(;x<=N;x+=x&-x)T[x]=0; }
} T;
struct node {
  int t, x, y, v;
  bool operator<(const node&r) const { return x != r.x ? x < r.x : (t != r.t ? t < r.t : abs(v) < abs(r.v)); }
} a[N * 6];
set<int> S[N];
inline void proc(int x, int tick, int m) {
  auto it = S[p[x]].find(x);
  int pre = 0, suf = 0;
  if (x != *S[p[x]].begin()) a[++tp] = {tick, x, pre=*--it, -m}, ++it;
  if (x != *S[p[x]].rbegin()) a[++tp] = {tick, suf=*++it, x, -m};
  if (pre && suf) a[++tp] = {tick, suf, pre, m};
}
void cdq(int l, int r) {
  if (l >= r) return;
  int mid = l+r>>1, j=l;
  cdq(l, mid); cdq(mid+1, r);
  for (int i=mid+1; i<=r; ++i) if (a[i].v == 0) {
    for (; j<=mid && a[j].x <= a[i].x; ++j)
      if (a[j].v != 0)
        T.set(a[j].y, a[j].v * (a[j].x-a[j].y));
    ans[a[i].t] += T.get(n) - (a[i].y>1 ? T.get(a[i].y-1) : 0);
  }
  for (int i=l; i<j; ++i)
    if (a[i].v != 0) T.unset(a[i].y);
  inplace_merge(a+l, a+mid+1, a+r+1);
}

int main() {
  scanf("%d%d",&n,&m);
  for (int i=1; i<=n; ++i) {
    scanf("%d", &p[i]);
    if (!S[p[i]].empty())
      a[++tp] = {0, i, *S[p[i]].rbegin(), 1};
    S[p[i]].insert(i);
  }
  int tick = 0;
  for (int t,x,y, i=1; i<=m; ++i) {
    scanf("%d%d%d", &t,&x,&y);
    if (t == 1) { // modify
      if (y == p[x]) continue;
      proc(x, tick, 1);
      S[p[x]].erase(x); S[p[x] = y].insert(x);
      proc(x, tick, -1);
    } else {
      ++tick;
      a[++tp] = {tick, y, x, 0};
    }
  }
  cdq(1, tp);
  for (int i=1; i<=tick; ++i) printf("%lld\n", ans[i]);
  return 0;
}