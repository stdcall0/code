#include <cstdio>
#include <algorithm>

int k, q;

inline int ycz(int x) {
  return (x - 1) / k + (bool)((x - 1) % k);
}

int main() {
  scanf("%d%d", &k, &q);
  while (q--) {
    static int x , y;
    scanf("%d%d", &x, &y);
    if (k == 1) printf("%d\n", std::min(x, y));
    else { while (x != y) {
      if (x < y) std::swap(x, y);
      x = ycz(x);
    }
    printf("%d\n", x); }
  }
  return 0;
}