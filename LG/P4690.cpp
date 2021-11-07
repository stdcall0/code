#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;
int n, m, a[N], prc[N], pre[N], ans[N];

namespace CDQ {
  struct treearray {
    int a[N+10], n;
    inline int get(int x){++x;int r=0;for(;x;x-=x&-x)r+=a[x];return r;}
    inline void add(int x,int v){++x;for(;x<=n;x+=x&-x)a[x]+=v;}
    inline void clr(int x){++x;for(;x<=n;x+=x&-x)a[x]=0;}
  } T;
  struct node {
    int x, y, v, r;
    inline bool operator< (const node&_) const { return x < _.x; }
  } a[N * 5 + 5];
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
};
namespace Cman {
  struct node {
    int l, r, x;
    inline bool operator<(const node&_) const { return r < _.r; }
  };
  set<node> cl, co[N]; set<int> pf;
  typedef set<node>::iterator It;
  inline It fn(int x, const set<node>& p) { return p.lower_bound({0, x}); }
  inline void split(int x) {
    It p = fn(x, cl); node v = *p;
    if (x != v.r) {
      cl.erase(p);
      cl.insert({v.l, x, v.x});
      cl.insert({x+1, v.r, v.x});
      co[p->x].erase({v.l, v.r});
      co[p->x].insert({v.l, x});
      co[p->x].insert({x+1, v.r});
    }
  }
  inline void pureins(int l, int r, int x) {
    cl.insert({l, r, x});
    co[x].insert({l, r});
  }
  inline void modify(int l, int r, int x) {
    if (l > 1) split(l - 1);
    split(r);
    It it, itt; int loc = l;auto i1t = cl.begin(), i2t = ++cl.begin();
      for (; i2t != cl.end(); ++i2t, ++i1t) {
        printf("[%d,%d] ", i1t->l, i1t->r);
if (i2t->l != i1t->r + 1) {
  printf("\n\n!! loc=%d,l=%d,r=%d [%d,%d] [%d,%d] !!\n\n", loc,l,r,i1t->l,i1t->r,i2t->l,i2t->r);
}
      }
      puts("");
        
    while (loc != r+1) {
      
      it = fn(loc, cl);
      assert(it->l <= loc && loc <= it->r);
      loc = it->r + 1;

      pf.insert(it->l);
      It itt = fn(it->r, co[it->x]);
      assert(itt->l == it->l && itt->r == it->r);
      if (++itt != co[it->x].end())
        pf.insert(itt->l);
      --itt;
      co[it->x].erase(itt); cl.erase(it);
    }
    cl.insert({l, r, x});
    it = co[x].insert({l, r}).first;
    if (++it != co[x].end())
      pf.insert(it->l);
    for (int i: pf) {
      it = fn(i, cl); itt = fn(i, co[it->x]);
      CDQ::modify(i, pre[i], -1);
      if (i != it->l) pre[i] = i-1;
      else if (itt != co[it->x].begin()) pre[i] = (--itt)->r;
      CDQ::modify(i, pre[i], 1);
    } pf.clear();
  }
};

map<int, int> va;
int op[N], L[N], R[N], V[N];

int main() {
  freopen("t.in","r", stdin);
  freopen("t.out","w",stdout);
  scanf("%d%d", &n, &m); CDQ::T.n = n+2;
  for (int i=1; i<=n; ++i) {
    scanf("%d", &a[i]);
    va[a[i]] = 1;
  }
  for (int i=1; i<=m; ++i) {
    scanf("%d%d%d", &op[i],&L[i],&R[i]);
    if (op[i] == 1) scanf("%d", &V[i]), va[V[i]] = 1;
  }
  int lst=1, qc=0;
  auto it=va.begin(),itt=va.begin();
  for (++it; it!=va.end(); ++it,++itt) it->second += itt->second;
  for (int i=1; i<=n; ++i) {
    a[i] = va[a[i]];
    if (a[i] != a[lst]) {
      Cman::pureins(lst, i-1, a[lst]);
      lst = i;
    }
    CDQ::modify(i, pre[i] = prc[a[i]], 1);
    prc[a[i]] = i;
  }
  if(lst<=n) Cman::pureins(lst, n, a[n]);
  for (int i=1; i<=m; ++i) {
    if (op[i] == 2) CDQ::query(++qc, L[i], R[i]);
    else Cman::modify(L[i], R[i], va[V[i]]);
  }
  CDQ::run(1, CDQ::cnt);
  for (int i=1; i<=qc; ++i) printf("%d\n", ans[i]);
  return 0;
}
