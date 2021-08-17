#include <bits/stdc++.h>
using namespace std;

int n;
const int N = 1e6 + 5;
struct cnm { int x, v; };
vector<cnm> G[N];
int siz[N];
long long ans = 0;

void dfs(int x, int fa) {
  siz[x] = 1;
  for (auto& _ : G[x]) {
    if (_.x == fa) continue;
    dfs(_.x, x);
    siz[x] += siz[_.x];
    ans += 1ll * abs(siz[_.x] * 2 - n) * _.v;
  }
}

int main() {
  scanf("%d", &n);
  for (int i=1; i<n; ++i) {
    static int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    G[x].push_back({y, z}); G[y].push_back({x, z});
  }
  dfs(1, 0);
  printf("%lld\n", ans);
  return 0;
}
