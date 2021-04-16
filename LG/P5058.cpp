#include <bits/stdc++.h>

#define Rn(a, n) a + 1, a + n + 1
#define Edge(T, x, y) T[x].push_back(y); T[y].push_back(x) //; printf("Edge #%s: %d - %d\n", #T, x, y)
typedef long long ll;
typedef unsigned long long ull;
inline ll R() {
  ll ret(0), c(0); bool neg(0); while (!isdigit(c = std::getchar())) neg = c == '-';
  ret = c - '0'; while (isdigit(c = std::getchar())) ret *= 10ll, ret += c - '0';
  return neg ? -ret : ret;
}

const int N = 2e5 + 5, M = 5e5 + 5;
std::vector<int> G[N], T[N * 2];
int n, c1, c2, g;

int ti = 0, top = 0;
int dfn[N], low[N], stk[N];
void tar(int x) {
  dfn[x] = low[x] = ++ti;
  stk[++top] = x;
  for (auto y : G[x]) {
    if (!dfn[y]) {
      tar(y);
      low[x] = std::min(low[x], low[y]);
      if (low[y] >= dfn[x]) {
        ++g;
        for (int u = 0; u != y; --top) {
          u = stk[top];
          Edge(T, u, g);
        }
        Edge(T, x, g);
      }
    } else {
      if (dfn[y] < dfn[x]) low[x] = std::min(low[x], dfn[y]);
    }
  }
}

void dfs(int x, int fa, int v = 0) {
  if (x == c2) {
    v ? printf("%d\n", v) : puts("No solution");
    exit(0);
  }
  if (x != c1 && x <= n && T[x].size() > 1) {
    v = v ? std::min(v, x) : x;
  }
  for (auto y : T[x]) {
    if (y == fa) continue;
    dfs(y, x, v);
  }
}

int main() {
  n = g = R();
  for (int u = -1, v; u; ) {
    u = R(), v = R();
    if (u != 0) Edge(G, u, v);
  }
  c1 = R(), c2 = R();
  tar(c1);
  if (!dfn[c2]) puts("No solution"), exit(0);
  dfs(c1, 0);
  puts(" ??? ");
  return 0;
}
