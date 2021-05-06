#include <bits/stdc++.h>

#define Rn(a, n) a + 1, a + n + 1
#define Edge(T, x, y) T[x].push_back(y); T[y].push_back(x) //; printf("Edge #%s: %d - %d\n", #T, x, y)
using ll = long long;
using ull = unsigned long long;
inline ll Rl() { ll ret(0); int c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-'; ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0'; return neg ? -ret : ret; }
inline int R() { int ret(0), c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-'; ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0'; return neg ? -ret : ret; }

int n, a[105], sum = 0, nxt[105];
int len, m;
bool z[105];

void dfs(int x, int pre, int rem) {
  if (rem == 0) {
    if (x == m)
      printf("%d\n", len), exit(0);
    int y = std::distance(a, std::find_if(Rn(a, n), [](auto x) { return !x; }));
    z[y] = 1;
    dfs(x + 1, y, len - a[y]);
    z[y] = 0;
  }
  for (int i = std::distance(a, std::lower_bound(a + pre + 1, a + n + 1, rem, std::greater<int>()));
    i <= n; i++) {
      if (!z[i]) {
        z[i] = 1;
        dfs(x, i, rem - a[i]);
        z[i] = 0;

        if (rem == a[i] || rem == len) return;
        i = nxt[i];
      }
    }
}

int main() {
  for (int n = R(), i = 1; i <= n; ++i) {
    if (int x = R(); x <= 50) {
      a[++::n] = x;
      sum += x;
    }
  }
  sort(Rn(a, n), std::greater<int>());
  nxt[n] = n;
  for (int i = n - 1; i > 0; --i) {
    if (a[i] == a[i + 1]) nxt[i] = nxt[i + 1];
    else nxt[i] = i;
  }
  for (len = a[1]; len <= sum / 2; ++len) {
    if (sum % len) continue;
    m = sum / len;
    z[1] = 1;
    dfs(1, 1, len - a[1]);
    z[1] = 0;
  }
  printf("%d\n", sum);
  return 0;
}
