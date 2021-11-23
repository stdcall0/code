#include <cstdio>
#include <algorithm>

const int N = 21, ST = (1 << 21) + 5;

int n, v[ST];
double a[25][25], f[ST];

bool cmp(int x, int y) { return __builtin_popcount(x) < __builtin_popcount(y); }

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%lf", &a[i][j]), a[i][j] /= 100;
  int s = (1 << n) - 1;
  for (int i = 1; i <= s; ++i) v[i] = i;
  std::sort(v + 1, v + 1 + s, cmp);
  int p = 0; f[0] = 1;
  for (int i = 1; i <= n; ++i) {
    while (__builtin_popcount(v[p]) < i) {
      for (int j = 1; j <= n; ++j) {
        int k = v[p] ^ (1 << j - 1);
        if ((k >> j - 1) & 1)
          f[k] = std::max(f[k], f[v[p]] * a[i][j]);
      }
      ++p;
    }
  }
  printf("%.6lf\n", f[s] * 100);
  return 0;
}