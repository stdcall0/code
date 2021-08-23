#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define fi first
#define se second
typedef long long LL;
typedef pair<int, int> edge;
int n; vector<edge> G[100005];
LL R, f[100005][3], ans = 1;

void dfs(int x, LL r, int fa = 1) {
  (ans *= r) %= (LL)(1e9 + 7);
  f[x][0] = 1; f[x][1] = 2; if (R > 2) f[x][2] = 3;
  for (auto &y : G[x]) {
    if (y.fi == fa) continue;
    if (R <= 2) {
      if (y.se == 0) dfs(y.fi, R - 1, x), f[x][0] += f[y.fi][1], f[x][1] += f[y.fi][0];
      else if (y.se == 2) dfs(y.fi, 1, x), f[x][0] += f[y.fi][0], f[x][1] += f[y.fi][1];
      else dfs(y.fi, R, x), f[x][0] += min(f[y.fi][0], f[y.fi][1]), f[x][1] += min(f[y.fi][0], f[y.fi][1]);
    } else {
      if (y.se == 0) dfs(y.fi, R - 1, x), f[x][0] += min(f[y.fi][1], f[y.fi][2]), f[x][1] += min(f[y.fi][0], f[y.fi][2]), f[x][2] += min(f[y.fi][0], f[y.fi][1]);
      else if (y.se == 2) dfs(y.fi, 1, x), f[x][0] += f[y.fi][0], f[x][1] += f[y.fi][1], f[x][2] += f[y.fi][2];
      else dfs(y.fi, R, x), f[x][0] += min(f[y.fi][0], min(f[y.fi][1], f[y.fi][2])), f[x][1] += min(f[y.fi][0], min(f[y.fi][1], f[y.fi][2])), f[x][2] += min(f[y.fi][0], min(f[y.fi][1], f[y.fi][2]));
    }
  }
}

int main() {
  scanf("%d%d", &n,&R);
  rep(i, 2, n) {
    int x,y,z;
    scanf("%d%d%d", &x,&y,&z);
    G[x].push_back({y, z});
    G[y].push_back({x, z});
  }
  dfs(1, R);
  if (ans) {
    printf("%lld %lld\n", ans, R <= 2 ? min(f[1][1], f[1][0]) : min (f[1][0], min(f[1][1], f[1][2])));
  } else puts("0 0");
  return 0;
}