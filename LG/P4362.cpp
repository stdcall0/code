#include <bits/stdc++.h>
using namespace std;

int n, m, k;
typedef pair<int, int> edge;
#define fi first
#define se second
vector<edge> G[305];
int f[305][305][2];
int g[305][2];

void dfs(int x, int fa) {
  f[x][0][0] = f[x][1][1] = 0;
  for (auto e : G[x]) {
    if (e.fi == fa) continue;
    dfs(e.fi, x);
    memcpy(g, f[x], sizeof(g));
    memset(f[x], 0x3f, sizeof(f[x]));
    for (int i = 0; i <= k; ++i)
      for (int j = 0; j <= i; ++j) {
        f[x][i][0] = min(f[x][i][0], min(f[e.fi][j][0] + g[i-j][0] + (m == 2 ? e.se : 0), f[e.fi][j][1] + g[i-j][0]));
        f[x][i][1] = min(f[x][i][1], min(f[e.fi][j][0] + g[i-j][1], f[e.fi][j][1] + g[i-j][1] + e.se));
      }
  }
}

int main() {
  memset(f, 0x3f, sizeof(f));
  scanf("%d%d%d", &n, &m, &k);
  if (n - k < m - 1) return puts("-1"), 0;
  for (int x,y,z, i = 1; i < n; ++i) {
    scanf("%d%d%d", &x,&y,&z);
    G[x].push_back({y, z});
    G[y].push_back({x, z});
  }
  dfs(1, 0);
  printf("%d\n", f[1][k][1]);
  return 0;
}
