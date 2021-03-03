#include <bits/stdc++.h>
using namespace std;
// #define NDEBUG
// #pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
// #pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const int N = 5e5 + 5;
const int POOL = 30000005;
int n, T[N], a[N];

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
  int query(int y1, int y2, int v, int L=1, int R=Tn) {
    if (L == R) return pool[y2].v - pool[y1].v;
    int mid = L + R >> 1;
    if (v <= mid) return query(pool[y1].l, pool[y2].l, v, L, mid);
    else return query(pool[y1].r, pool[y2].r, v, mid+1, R);
  }

  inline int build(int n) {
    pool[pc = 1] = {1, n, 1 + n >> 1};
    Tn = n; _build(1); return 1;
  }
};

int main() {
  n = R(); int q = R(), co = 0;
  for (int i=1; i<=n; i++) {
    co = max(co, a[i] = R());
  }
  T[0] = Tr::build(co);
  for (int i=1; i<=n; i++) {
    T[i] = Tr::change(T[i-1], a[i], 1);
  }
  for (int opt,c,l,r; q--; ) {
    opt = R();
    if (opt == 1) {
      l = R(); r = R(); c = R();
      if (c > co) {
        puts("0"); continue;
      }
      printf("%d\n", Tr::query(T[l-1], T[r], c));
    } else {
      c = R();
      if (a[c] == a[c+1]) continue;
      T[c] = Tr::change(T[c+1], a[c], -1);
      swap(a[c], a[c+1]);
    }
  }
  return 0;
}
