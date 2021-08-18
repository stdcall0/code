#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> G[105];
int dp[105][105][2]; // Point RemainStep Back

int dfs(int x, int fa) {
  dp[x][0][0] = dp[x][0][1] = 1;
  for (int y : G[x]) {
    if (y == fa) continue;
    dfs(y, x);
  }
  // Case 1: go back to x
  for (int y : G[x]) {
    if (y == fa) continue;
    for (int rs = 2; rs <= n; ++rs) {
      dp[x][rs][1] += dp[y][rs - 2][1] + 1;
    }
  }
  // Case 2: donot go back
  for (int y : G[x]) {
    if (y == fa) continue;
    for (int rs = 1; rs <= n; ++rs) {
      dp[x][rs][0] = max(dp[x][rs][0], dp[y][rs - 2][] + 1);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int x,y, i = 1; i < n; ++i) {
    scanf("%d%d", &x, &y);
    G[x].push_back(y); G[y].push_back(x);
  }
  return 0;
}
