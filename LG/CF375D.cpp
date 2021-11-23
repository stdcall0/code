#include <cstdio>

const int N = 1e5 + 5;

int n, q, col[N];
int to[N * 2], nxt[N * 2], hed[N], ec = 0;
int dfn[N], tick = 0;
Node a[N * 20], ac = 1;

void dfs(int x, int fa) {
  dfn[x] = ++tick;
  for (int i = hed[x]; i; i = nxt[i])
    if (to[i] != fa)
      dfs(to[i], x);
}

int main() {
  static int x, y;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &col[i]);
  for (int i = 1; i < n; ++i) {
    scanf("%d%d", &x, &y);
    nxt[++ec] = hed[x]; to[ec] = y; hed[x] = ec;
    nxt[++ec] = hed[y]; to[ec] = x; hed[y] = ec;
  }
  dfs(1, 0);
  
  return 0;
}
