#include <cstdio>

const int maxN = 5e5 + 5;

struct BIT {
  int sz, a[maxN];

  inline void init(int siz) {
    sz = siz;
    for (int i = 1; i <= sz; ++i)
      a[i] = 0;
  }

  inline void add(int x, int v) {
    for (; x <= sz; x += x & -x)
      a[x] += v;
  }

  inline int get(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
      ret += a[x];
    return ret;
  }
};

int n, m;
BIT B;

int main() {
  scanf("%d%d", &n, &m);
  B.init(n);

  for (int v, i = 1; i <= n; ++i) {
    scanf("%d", &v);
    B.add(i, v);
  }

  int op, x, y;
  while (m--) {
    scanf("%d%d%d", &op, &x, &y);

    if (op == 1)
      B.add(x, y);
    else
      printf("%d\n", B.get(y) - (x > 1 ? B.get(x - 1) : 0));
  }
  return 0;
}
