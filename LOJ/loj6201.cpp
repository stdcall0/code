#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m, a[N], prc[N], pre[N], ans[N];

struct CDQSolver {
  struct treearray {
    int a[N+10], n;
    inline int get(int x){++x;int r=0;for(;x;x-=x&-x)r+=a[x];return r;}
    inline void add(int x,int v){++x;for(;x<=n;x+=x&-x)a[x]+=v;}
    inline void clr(int x){++x;for(;x<=n;x+=x&-x)a[x]=0;}
  } T;
  struct node {
    int x, y, v, r;
    inline bool operator< (const node&_) const { return x < _.x; }
  } a[N * 8 + 5];
  int cnt = 0;
  inline void query(int id, int x, int y) {
    a[++cnt] = {y, x-1, 1, id};
    a[++cnt] = {x-1, x-1, -1, id};
  }
  inline void modify(int x, int y, int v) {
    a[++cnt] = {x, y, v, 0};
  }
  void run(int l, int r) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    run(l, mid); run(mid+1, r);
    sort(a+l, a+mid+1); sort(a+mid+1, a+r+1);
    int j=l;
    for (int i=mid+1; i<=r; ++i) if (a[i].r != 0) {
      while (j<=mid && a[j].x <= a[i].x) {
        if (a[j].r == 0) T.add(a[j].y, a[j].v);
        ++j;
      }
      ans[a[i].r] += a[i].v * T.get(a[i].y);
    }
    for (int i=l; i<j; ++i) T.clr(a[i].y);
  }
} c;
struct SegmentMan {
  struct node {
    int l, r, x;
    inline bool operator<(const node&_) const { return r < _.r; }
  };
  set<node> cl, co[N]; set<int> pf;
  typedef set<node>::iterator It;
  inline It fn(int x, const set<node>& p) {
    It it = p.lower_bound({0, x});
    assert(it != p.end());
    return it;
  }
  inline void split(int x) {
    It p = fn(x, cl), q = fn(x, co[p->x]);
    assert(p->l == q->l && p->r == q->r && p->l <= x && x <= p->r);
    if (x == p->r) return;
    auto d = *p;
    cl.erase(p); co[d.x].erase(q);
    cl.insert({d.l, x, d.x}); cl.insert({x+1, d.r, d.x});
    co[d.x].insert({d.l, x}); co[d.x].insert({x+1, d.r});
  }
  inline It put(int l, int r, int x) {
    cl.insert({l, r, x});
    return co[x].insert({l, r}).first;
  }
  inline void ins(int l, int r, int x) {
    It it = ++put(l, r, x);
    if (it != co[x].end())
      pf.insert(it->l);
  }
  inline void del(const It& it) {
    if (it->l > 1) pf.insert(it->l);
    It itt = fn(it->r, co[it->x]);
    assert(it->l == itt->l && it->r == itt->r);
    if (++itt != co[it->x].end())
      pf.insert(itt->l);
    co[it->x].erase(--itt); cl.erase(it);
  }
  inline void modify(int l, int r, int x) {
    if (l > 1)
      split(l - 1);
    split(r);
    int pos = l;
    while (pos <= r) {
      It it = fn(pos, cl);
      assert(it->l == pos);
      pos = it->r + 1;
      del(it);
    }
    assert(pos == r+1);
    ins(l, r, x);
    for (int i: pf) {
      It p = fn(i, cl); It q = fn(i, co[p->x]);
      assert(p->l == q->l && p->r == q->r && p->l <= i && i <= p->r);
      c.modify(i, pre[i], -1);
      if (i != p->l) pre[i] = i-1;
      else
        if (q != co[p->x].begin())
          pre[i] = (--q)->r;
        else
          pre[i] = 0;
      c.modify(i, pre[i], 1);
    }
    pf.clear();
  }
} s;

map<int, int> va;
int op[N], L[N], R[N], V[N];

int main() {
  scanf("%d%d", &n, &m); c.T.n = n+2;
  for (int i=1; i<=n; ++i) {
    scanf("%d", &a[i]);
    va[a[i]] = 1;
  }
  for (int i=1; i<=m; ++i) {
    scanf("%d%d%d", &op[i],&L[i],&R[i]);
    if (op[i] == 1) scanf("%d", &V[i]), va[V[i]] = 1;
  }
  int loc=0, qc=0;
  auto it=va.begin(),itt=va.begin();
  for (++it; it!=va.end(); ++it,++itt) it->second += itt->second;
  for (int i=1; i<=n; ++i) {
    a[i] = va[a[i]];
    if (a[i] != a[loc]) {
      if (loc) s.put(loc, i-1, a[loc]);
      loc = i;
    }
    c.modify(i, pre[i] = prc[a[i]], 1);
    prc[a[i]] = i;
  }
  s.put(loc, n, a[n]);
  for (int i=1; i<=m; ++i) {
    if (op[i] == 2) c.query(++qc, L[i], R[i]);
    else s.modify(L[i], R[i], va[V[i]]);
  }
  c.run(1, c.cnt);
  for (int i=1; i<=qc; ++i) printf("%d\n", ans[i]);
  return 0;
}