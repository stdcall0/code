#include <bits/stdc++.h>
using namespace std;

#define fl fflush(stdout)
int n, a[50005], b[50005], m1, m2;

inline int op1(int x, int y) {
  if (m1-- == 0) {
    exit(-1);
  }
  printf("! %d %d\n", x, y); fl;
  scanf("%d", &x); return x;
}
inline set<int> op2(const set<int> &S, int v) {
  if (m2-- == 0) {
    exit(-1);
  }
  printf("? %d", S.size());
  for (int i : S) printf(" %d", i);
  printf(" %d\n", v);
  fl; int _; scanf("%d", &_);
  set<int> r; for (int i=0; i<_; ++i) {
    int x; scanf("%d", &x); r.insert(x);
  } return r;
}
inline set<int> findbelow(set<int> &S, int v) {
  if (v >= n) return S;
  set<int> r = op2(S, v + 1), _;
  for (int i : S) if (r.count(i) == 0) _.insert(i);
  for (int i : _) S.erase(i);
  return _;
}
inline void mark(int x, int v) {
  a[x] = v; b[v] = x;
}
inline void sp4(const set<int> &S) {
  set<int> _ = op2(S, 3);
  assert(_.size() == 2);
  int x = *_.begin(), y = *(++_.begin());
  for (int i : S)
    if (_.count(i) == 0) {
      int v = op1(x, i), w = op1(y, i);
      if (v || w) {
        mark(i, 2);
        if (v) mark(x, 3), mark(y, 4);
        else mark(x, 4), mark(y, 3);
      } else mark(i, 1);
    }
}

int main() {
  int _; scanf("%d%d%d%d", &n,&m1,&m2,&_);
  set<int> S; for (int i=1; i<=n; ++i) S.insert(i);
  set<int> s = findbelow(S, 4);
  sp4(s);
  int pw = 4;
  while (pw < n) {
    int pre = b[pw]; s = findbelow(S, pw * 2);
    for (int i : s) {
      int _ = op1(i, pre);
      if (_) mark(i, _ + pw);
      else mark(i, pw * 2);
    }
    pw *= 2;
  }
  printf("A");
  for (int i=1; i<=n; ++i)
    printf(" %d", a[i]);
  printf("\n"); fl;
  return 0;
}
