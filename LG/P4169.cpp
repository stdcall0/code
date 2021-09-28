#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int n, m, ans[N], Mx=0, My=0, tp=0, qc=0, tq=0;

struct BIT {
  const static int S = 1e6 + 5;
  int a[S + 10];
  int get(int x) { int r=0; for (;x;x^=x&-x) r=max(r, a[x]); return r; }
  void set(int x, int v) { for (;x<=S;x+=x&-x) a[x]=max(a[x], v);}
  void unset(int x) { for (;x<=S;x+=x&-x) a[x]=0; }
} T;
struct node {
  int x, y, v;
  bool operator<(const node& r)const { return x <= r.x; }
} a[N * 2], b[N * 2];
inline int cx(int x, bool Inv) { return Inv ? Mx - x : x; }
inline int cy(int x, bool Inv) { return Inv ? My - x : x; }
void reset(bool invX, bool invY) {
  int mx = 0, my = 0;
  for (int i=1; i<=tp; ++i) if (b[i].v != 0)  {
    mx = max(mx, cx(b[i].x, invX));
    my = max(my, cy(b[i].y, invY));
  }
  tq = 0;
  for (int x,y, i=1; i<=tp; ++i) {
    x = cx(b[i].x, invX); y = cy(b[i].y, invY);
    if (x <= mx && y <= my)
      a[++tq] = {x, y, b[i].v};
  }
}
void cdq(int l, int r) {
  if (l >= r) return;
  int mid = l+r>>1, j=l;
  cdq(l, mid); cdq(mid+1, r);
  for (int i=mid+1; i<=r; ++i) if (a[i].v != 0) {
    while (j<=mid && a[j].x<=a[i].x) {
      if (a[j].v == 0) T.set(a[j].y, a[j].x+a[j].y);
      ++j;
    }
    int _ = T.get(a[i].y);
    if (_) ans[a[i].v] = min(ans[a[i].v], a[i].x+a[i].y-_);
  }
  for (int i=l; i<j; ++i)
    if (a[i].v == 0) T.unset(a[i].y);
  inplace_merge(a+l, a+mid+1, a+r+1);
}

#define upxy ++x, ++y; Mx = max(Mx, x); My = max(My, y)

int main() {
  scanf("%d%d", &n,&m);
  for (int x,y, i=1; i<=n; ++i) {
    scanf("%d%d", &x, &y); upxy;
    b[++tp] = {x, y, 0};
  }
  for (int T,x,y, i=1; i<=m; ++i) {
    scanf("%d%d%d", &T,&x,&y); upxy;
    b[++tp] = {x, y, T == 1 ? 0 : ++qc};
  }
  ++Mx, ++My;
  for (int i=1; i<=qc; ++i) ans[i] = 0x3f3f3f3f;
  for (int i=0; i<4; ++i) {
    reset(i & 1, i >> 1);
    cdq(1, tq);
  }
  for (int i=1; i<=qc; ++i)
    printf("%d\n", ans[i]);
  return 0;
}