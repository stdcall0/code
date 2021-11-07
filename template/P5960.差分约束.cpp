#include <cstdio>
#include <cstring>
#include <vector>
#include <deque>

const int maxN = 5e3 + 5;

struct Edge {
  int x, v;
};

int n, m;
bool vis[maxN];
int dis[maxN], cnt[maxN];
std::deque<int> Q;
std::vector<Edge> G[maxN];

void addEdge(int x, int y, int z) {
  G[x].push_back({y, z});
}
void solve() {
  memset(dis, 0x3f, sizeof(dis));
  dis[0] = 0;
  vis[0] = true;
  Q.clear();
  Q.push_back(0);

  while (!Q.empty()) {
    int x = Q.front();
    Q.pop_front();
    vis[x] = false;

    for (auto &e : G[x]) {
      if (dis[e.x] > dis[x] + e.v) {
        dis[e.x] = dis[x] + e.v;
        if (!vis[e.x]) {
          vis[e.x] = true;
          if (++cnt[e.x] == n + 1) {
            puts("NO");
            return;
          }
          Q.push_back(e.x);
        }
      }
    }
  }

  for (int i = 1; i <= n; ++i)
    printf("%d ", dis[i]);
  puts("");
}

int main() {
  int x, y, z;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    addEdge(0, i, 0);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    addEdge(y, x, z);
  }
  solve();
  return 0;
}
