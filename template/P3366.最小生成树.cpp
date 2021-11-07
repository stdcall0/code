#include <cstdio>
#include <algorithm>

struct Edge {
  int x, y, z;

  bool operator< (const Edge& r) const {
    return z < r.z;
  }
};

struct UnionSet {
  int fa[5005];

  inline void init(int n) {
    for (int i = 1; i <= n; ++i)
      fa[i] = i;
  }

  inline int find(int x) {
    if (fa[x] == x)
      return x;
    return fa[x] = find(fa[x]);
  }

  inline int merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
      return 0;
    fa[x] = y;
    return y;
  }
};

int n, m;
Edge a[200005];
UnionSet u;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i)
    scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);

  int ret = 0, cnt = 0;

  u.init(n);
  std::sort(a + 1, a + 1 + m);

  for (int i = 1; i <= m; ++i)
    if (u.merge(a[i].x, a[i].y))
      ret += a[i].z,
      ++cnt;

  if (cnt != n - 1)
    puts("orz");
  else
    printf("%d\n", ret);

  return 0;
}
