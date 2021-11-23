#include <cstdio>
#include <iostream>
#include <string>
#include <map>

const int N = 5e4 + 5;
const int c[] = {0, 1, 2, 4, 8, 3, 5, 9, 6, 10, 12, 7, 11, 13, 14, 15};
typedef long long LL;

int n, d;
LL f[5], g[5], ca[5][5];
std::string a[N];
std::map<std::string, int> M;

inline void count(int x) {
  std::string s;
  f[0] = f[1] = f[2] = f[3] = f[4] = 0;
  for (int i : c) {
    s = a[x];
    for (int j = 0; j < 4; ++j)
      if (i >> j & 1)
        s[j] = '*';
    f[4 - __builtin_popcount(i)] += M[s];
    ++M[s];
  }
}
inline void roll(int x) {
  for (int i = 4; i >= 0; --i) {
    g[i] = f[i];
    for (int j = i + 1; j <= 4; ++j)
      g[i] -= g[j] * ca[j][i];
  }
}

int main() {
  std::ios :: sync_with_stdio(false);
  std::cin >> n >> d;
  LL ans = 0;
  ca[0][0] = 1;
  for (int i = 1; i <= 4; ++i) {
    ca[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      ca[i][j] = ca[i - 1][j] + ca[i - 1][j - 1];
  }
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i],
    count(i),
    roll(i),
    ans += g[4 - d];
  printf("%lld\n", ans);
  return 0;
}
