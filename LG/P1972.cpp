#include <bits/stdc++.h>
using namespace std;
#define Rn(a, n) a + 1, a + n + 1

typedef long long ll;
const int N = 1e6 + 5;
const int POOL = 20000005;
int n, a[N], pre[N], la[N], T[N];

namespace U {
  inline ll retR() {
    ll ret(0), c(0); bool neg(0); while (!isdigit(c = getchar())) neg = c == '-';
    ret = c - '0'; while (isdigit(c = getchar())) ret *= 10ll, ret += c - '0';
    return neg ? -ret : ret;
  }
  template <typename IntVal>
  inline void refR(IntVal v) { v = retR(); }
}; // Utils
auto R = U::retR;

namespace Tr {
  struct node {
    int l, r, v;
  } pool[POOL];
  int pc = 0, Tn = 0;

  void _build(int y, int L=1, int R=Tn) {
    if (L == R) return;
    int mid = L + R >> 1;
    _build(pool[y].l = ++pc, L, mid);
    _build(pool[y].r = ++pc, mid+1, R);
  }
  void _change(int &y, int at, int v, int L=1, int R=Tn) {
    pool[++pc] = {pool[y].l, pool[y].r, pool[y].v + v};
    y = pc;
    if (L == R) return;
    int mid = L + R >> 1;
    if (at <= mid) _change(pool[y].l, at, v, L, mid);
    else _change(pool[y].r, at, v, mid+1, R);
  }

  inline int change(int root, int at, int v) {
    int ret = 0; pool[0] = pool[root];
    _change(ret, at, v); return ret;
  }
  int query(int y1, int y2, int l, int r, int L=1, int R=Tn) {
    if (L > r || R < l) return 0;
    if (l <= L && R <= r) return pool[y2].v - pool[y1].v;
    int mid = L + R >> 1;
    return query(pool[y1].l, pool[y2].l, l, r, L, mid) + query(pool[y1].r, pool[y2].r, l, r, mid+1, R);
  }

  inline int build(int n) {
    pool[pc = 1] = {1, n, 1 + n >> 1};
    Tn = n; _build(1); return 1;
  }
};

int main() {
  n = R(); T[0] = Tr::build(n);
  for (int i=1; i<=n; i++) {
    a[i] = R();
    la[i] = pre[a[i]] + 1; pre[a[i]] = i;
    T[i] = Tr::change(T[i-1], la[i], 1);
  }
  int q = R();
  for (int l,r; q--; ) {
    l = R(), r = R();
    printf("%d\n", Tr::query(T[l-1], T[r], 1, l));
  }
  return 0;
}