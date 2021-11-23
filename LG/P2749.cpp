#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>

const int N = 105;
const int dx[8] = {-1, -1, -1, 1, 1, 1, 0, 0};
const int dy[8] = {0, -1, 1, 0, -1, 1, -1, 1};

int n, m, now = 0, tot = 0;
char G[N][N];
int ans[N][N];
bool vis[N][N];
std::vector<std::pair<int, int> > li;
std::map<int, int> ta;
int out[N * N];
double dis;

void dfs(int x, int y) {
  vis[x][y] = 1;
  ans[x][y] = now;
  for (auto &i : li)
    dis += sqrt((x - i.first) * (x - i.first) + (y - i.second) * (y - i.second));
  li.push_back(std::make_pair(x, y));
  for (int d = 0; d < 8; ++d) {
    int p = x + dx[d], q = y + dy[d];
    if (p < 1 || q < 1 || p > n || q > m || !G[p][q] || vis[p][q])
      continue;
    dfs(p, q);
  }
}

int main() {
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", G[i] + 1);
    for (int j = 1; j <= m; ++j)
      G[i][j] -= '0';
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (G[i][j] && !vis[i][j]) {
        dis = 0;
        li.clear();
        dfs(i, j);
        int D = dis * 1000;
        if (ta[D]) {
          out[now] = ta[D] - 1;
        } else {
          out[now] = tot++;
          ta[D] = out[now] + 1;
        }
        ++now;
      }
      putchar(G[i][j] ? out[ans[i][j]] + 'a' : '0');
    }
    puts("");
  }
  return 0;
}
