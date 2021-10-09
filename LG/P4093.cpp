#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m, f[N];

struct BIT {
  int T[N + 5];
  inline int get(int x) { int r=0;for(;x;x-=x&-x)r=max(r,T[x]);return r; }
  inline void set(int x, int v) { for(;x<=N;x+=x&-x)T[x]=max(T[x],v); }
  inline void unset(int x) { for(;x<=N;x+=x&-x)T[x]=0; }
} T;
struct node {
  int v, mi, mx, id;
} a[N];
bool cmp1(const node&a, const node&b) { return a.mx < b.mx; }
bool cmp2(const node&a, const node&b) { return a.v < b.v; }
bool cmp3(const node&a, const node&b) { return a.id < b.id; }

void cdq(int l, int r) {
  if (l >= r) return;
  int mid=l+r>>1, j=l;
  sort(a+l, a+r+1, cmp3);
  cdq(l, mid);
  sort(a+l, a+mid+1, cmp1);
  sort(a+mid+1, a+r+1, cmp2);
  for (int i=mid+1; i<=r; ++i) {
    while (j<=mid && a[j].mx <= a[i].v) {
      T.set(a[j].v, f[a[j].id]);
      ++j;
    }
    f[a[i].id] = max(f[a[i].id], T.get(a[i].mi) + 1);
  }
  for (int i=l; i<j; ++i)
    T.unset(a[i].v);
  cdq(mid+1, r);
}

int main() {
  scanf("%d%d",&n,&m);
  for (int i=1; i<=n; ++i)
    scanf("%d", &a[i].v), a[i].mx=a[i].mi=a[i].v, f[i]=1, a[i].id=i;
  for (int x,y, i=1; i<=m; ++i)
    scanf("%d%d", &x,&y), a[x].mx=max(a[x].mx, y), a[x].mi=min(a[x].mi, y);
  cdq(1, n);
  printf("%d\n", *max_element(f+1, f+1+n));
  return 0;
}