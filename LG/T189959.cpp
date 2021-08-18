#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL s, k; int n, m; set<int>S;

inline LL va(int L, int R) {
  return (s - k) * (R - L + 1) + 1LL * (L + R) * (R - L + 1) / 2 * k;
}
inline LL ask(int L, int R) {
  printf("%d %d\n", L, R); fflush(stdout);
  LL r; scanf("%lld", &r);
  return r;
}
inline void reply() {
  printf("-1");
  for (int x : S) printf(" %d", x);
  puts(""); fflush(stdout);
}

void cnm(int L, int R, LL val) {
  if (val == 0) {
    for (int i = L; i <= R; ++i) {
      --m; S.insert(i);
    }
    return;
  }
  if (L >= R) return;
  LL ppos = (va(L, R) - val - s);
  if (m && R - L < n / m && ppos % k == 0) {
    LL p = ppos / k + 1;
    if (L <= p && p <= R) {
      --m; S.insert(p);
      return;
    }
  }
  int mid = L + R >> 1;
  
  LL p = ask(L, mid); LL q = val - p;
  if (p != va(L, mid)) cnm(L, mid, p);
  if (q != va(mid+1, R)) cnm(mid + 1, R, q);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%lld%lld", &n,&m,&s,&k);
    S.clear(); cnm(1, n, ask(1, n)); reply();
  }
  return 0;
}