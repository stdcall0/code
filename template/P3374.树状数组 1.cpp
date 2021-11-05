#include <cstdio>

const int maxN = 5e5 + 5;

struct BIT {
  int sz, a[maxN];

  inline void init(int siz) {
    sz = siz;
    for (int i = 1; i <= sz; ++i)
      a[i] = 0;
  }

  inline void query(int x) {
    int ret = 0;
    for (; x; x -= x & (-x))
      ret += a[x];
    return ret;
  }

  inline void 

};

int main() {


  return 0;
}