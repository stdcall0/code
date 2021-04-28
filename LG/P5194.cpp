#include <bits/stdc++.h>

#define Rn(a, n) a + 1, a + n + 1
#define Edge(T, x, y) T[x].push_back(y); T[y].push_back(x) //; printf("Edge #%s: %d - %d\n", #T, x, y)
typedef long long ll;
typedef unsigned long long ull;
inline ll Rl() {
  ll ret(0); int c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-';
  ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0';
  return neg ? -ret : ret;
}
inline int R() {
  int ret(0); int c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-';
  ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0';
  return neg ? -ret : ret;
}

int n, c;
ll w[1005], su[1005], ans = 0;

void dfs(int x, ll W = 0) {
  if (W > c) return;
  if (su[x - 1] + W <= c) {
    ans = std::max(ans, su[x - 1] + W);
    return;
  }
  ans = std::max(ans, W);
  if (x <= 1) return;
  for (int i = 1; i < x; ++i)
    dfs(i, W + w[i]);
}

int main() {
  n = R(), c = R();
  for (int i = 1; i <= n; ++i) {
    w[i] = Rl();
    su[i] = su[i - 1] + w[i];
  }
  dfs(n + 1);
  printf("%lld\n", ans);
  return 0;
}
