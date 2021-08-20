#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define up(x, y) x = max(x, y)
int n, m;
vector<int> G[105];
int dp[105][105][2], tmp[105][2];

void dfs(int x, int fa) {
  memset(dp[x], 0, sizeof(dp[x]));
  dp[x][0][0] = dp[x][0][1] = 1;
  for (int y : G[x]) {
    if (y == fa) continue;
    dfs(y, x);
    memcpy(tmp, dp[x], sizeof(tmp));
    rep(i, 1, m) rep(j, 0, i-1) {
      if (i-j > 1) up(dp[x][i][1], tmp[i-j-2][1] + dp[y][j][1]), up(dp[x][i][0], tmp[i-j-2][0] + dp[y][j][1]);
      up(dp[x][i][0], tmp[i-j-1][1] + dp[y][j][0]);
    }
  }
  rep(i, 1, m) up(dp[x][i][0], dp[x][i-1][0]), up(dp[x][i][1], dp[x][i-1][1]);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int x,y, i = 1; i < n; ++i) {
    scanf("%d%d", &x, &y); ++x;++y;
    G[x].push_back(y); G[y].push_back(x);
  }
  dfs(1, 0);
  printf("%d\n", dp[1][m][0]);
  return 0;
}
