#include <bits/stdc++.h>
using namespace std;
// #define NDEBUG
// #pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
// #pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const int N = 1e5 + 5;
const int POOL = 10000005;
int n, m, T[N], f1[N], f2[N];
struct node {
  int a, b;
  bool operator< (const node&res) const {return a < res.a; }
} a[N];

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
    if (L == R) return L;
    int mid = L + R >> 1;
    int Lc = pool[pool[y2].l].v - pool[pool[y1].l].v;
    if (v <= Lc) return query(pool[y1].l, pool[y2].l, v, L, mid);
    else return query(pool[y1].r, pool[y2].r, v-Lc, mid+1, R);
  }

  inline int build(int n) {
    pool[pc = 1] = {1, n, 1 + n >> 1};
    Tn = n; _build(1); return 1;
  }
};

inline int kth_min(int L, int R, int k) {
  return Tr::query(T[L-1], T[R], k);
}

int main() {
  m = R(), n = R(); int f = R();
  T[0] = Tr::build(1e5);
  for (int i=1; i<=n; i++) {
    a[i].a = R(), a[i].b = R();
  }
  sort(a+1, a+1+n);
  for (int i=1; i<=n; i++) {
    T[i] = Tr::change(T[i-1], a[i].b, 1);
  }
  int k = (m-1) / 2;
  for (int i=1; i<=k; i++) {
    int j = n-i+1;
    f1[i] = f1[i-1] + a[i].b;
    f2[j] = f2[j+1] + a[j].b;
  }
  for (int i=k+1; i<=n; i++) {
    int j = n-i+1;
    f1[i] = f1[i-1] + min(0, a[i].b-kth_min(1,i-1,k));
    f2[j] = f2[j+1] + min(0, a[j].b-kth_min(j+1,n,k));
  }
  int res = 0;
  for (int i=k+1; i<=n-k; i++) {
    if (a[i].b + f1[i-1] + f2[i+1] <= f) res = max(res, a[i].a);
  }
  cout << res << endl;
  return 0;
}
