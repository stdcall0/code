#include <cstdio>
#include <cmath>
#include <algorithm>

const int N = 1e6 + 5, S = 1e4;
int n, q;

int sz, cnt, L[S], R[S], id[N];
int a[N], b[N], tag[S];

inline void bmod(int x, int v) {
  tag[x] += v;
}
inline void fmod(int x, int v, int l, int r) {
  for (int i = std::max(l, L[x]); i <= std::min(r, R[x]); ++i)
    a[i] += v;
  for (int i = L[x]; i <= R[x]; ++i)
    b[i] = a[i];
  std::sort(b + L[x], b + R[x] + 1);
}
inline int bqry(int x, int v) {
  return b + R[x] + 1 - std::lower_bound(b + L[x], b + R[x] + 1, v - tag[x]);
}
inline int fqry(int x, int v, int l, int r) {
  int ret = 0;
  for (int i = std::max(l, L[x]); i <= std::min(r, R[x]); ++i)
    if (a[i] + tag[x] >= v)
      ++ret;
  return ret;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]),
    b[i] = a[i];
  sz = sqrt(n);
  cnt = n / sz + (bool)(n % sz);
  int idx = 1;
  for (int i = 1; i <= cnt; ++i) {
    L[i] = (i - 1) * sz + 1;
    R[i] = i == cnt ? n : i * sz;
    while (idx <= R[i])
      id[idx++] = i;
    std::sort(b + L[i], b + R[i] + 1);
  }
  while (q--) {
    static char op[5];
    static int l, r, x;
    scanf("%s%d%d%d", op, &l, &r, &x);
    int li = id[l], ri = id[r];
    if (op[0] == 'M') {
      fmod(li, x, l, r);
      if (li != ri) fmod(ri, x, l, r);
      for (int i = li + 1; i < ri; ++i)
        bmod(i, x);
    } else {
      int ans = fqry(li, x, l, r);
      if (li != ri) ans += fqry(ri, x, l, r);
      for (int i = li + 1; i < ri; ++i)
        ans += bqry(i, x);
      printf("%d\n", ans);
    }
  }
  return 0;
}