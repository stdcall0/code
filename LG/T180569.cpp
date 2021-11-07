#include <bits/stdc++.h>
using namespace std;

int n, m1, m2, m3;
set<int> S;
int a[500005];
int pw[25];

inline int op1(int x, int y) {
  --m1; assert(m1 >= 0);
  printf("! %d %d\n", x, y); fflush(stdout);
  scanf("%d", &x); return x;
}
inline set<int> op2(const set<int> &S, int p) {
  --m2; assert(m2 >= 0);
  printf("? %d", (int)S.size());
  for (auto i : S) printf(" %d", i);
  printf(" %d\n", p); fflush(stdout);
  int _; scanf("%d", &_);
  set<int> res;
  for (int i = 0; i < _; ++i) { scanf("%d", &p); res.insert(p); }
  return res;
}T

int main() {
  scanf("%d%d%d%d", &n, &m1,&m2,&m3);
  for (int i = 1; i <= n; ++i) S.insert(i);
  set<int> p(op2(S, 2));
  for (int i = 1; i <= n; ++i)
    if (!p.count(i)) a[i] = pw[0] = 1, S.erase(i);
  int k = 1, v = 2;
  while (v / 2 < n) {
    // find K pos
    if (v < n) p = op2(S, v + 1);
    else p = set<int>();
    for (int i = 1; i <= n; ++i)
      if (S.count(i) && !p.count(i)) {
        a[i] = op1(i, pw[k-1]), S.erase(i);
        if (a[i] == 0) pw[k] = a[i] = v;
        else a[i] += pw[k-1];
      }
    ++k; v *= 2;
  }
  printf("A");
  for (int i = 1; i <= n; ++i) printf(" %d", a[i]);
  puts(""); fflush(stdout);
  return 0;
}
