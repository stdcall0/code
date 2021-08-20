#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define fi first
#define se second
#define mp make_pair
using LL = long long;
using edge = pair<int, LL>;
int n, R; LL ans = 0;
vector<edge> G[500005];

void dfs(int x, int fa) {
  for (auto &_ : G[x])
    if (_.fi != fa) dfs(_.fi, x);
  LL mx = 0;
  for (auto &_ : G[x]) if (_.fi != fa) mx = max(mx, _.se);
  for (auto &_ : G[x]) if (_.fi != fa) ans += mx - _.se;
  for (auto &_ : G[fa]) if (_.fi == x) _.se += mx;
}

int main() {
  scanf("%d%d", &n, &R);
  int x, y; LL z; rep(i, 2, n) {
    scanf("%d%d%lld", &x,&y,&z);
    G[x].push_back(mp(y, z)); G[y].push_back(mp(x, z));
  }
  dfs(R, 0); printf("%lld\n", ans);
  return 0;
}
