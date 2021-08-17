#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> G[(int)(1e6 + 5)];
int mxDep = 0;
void dfs(int x, int dep, int fa) {
  if (dep > mxDep) {
    mxDep = dep;
  }
  for (int y : G[x]) {
    if (y == fa)continue;
    dfs(y, dep + 1, x);
  }
}

int main() {
  scanf("%d", &n);
  for (int i=1; i<=n;++i) {
    static int l, r; scanf("%d%d", &l,&r);
    if (l != 0) G[i].push_back(l), G[l].push_back(i);
    if (r != 0) G[i].push_back(r), G[r].push_back(i);
  }
  dfs(1, 0, 0);
  printf("%d\n", mxDep + 1);
  return 0;
}
