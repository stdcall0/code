#include <bits/stdc++.h>
using namespace std;

int n;
int order[1005], v[1005], dep[1005], fa[1005];

int main() {
  scanf("%d", &n); order[1] = 1; v[0] = v[1] = n;
  for (int i = 2; i <= n; ++i) {
    scanf("%d", &fa[i]);
    dep[i] = dep[fa[i]] + 1;
    order[i] = i; v[i] = n;
  }
  sort(order + 1, order + 1 + n, [](int x, int y) { return dep[x] > dep[y]; });
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int x = order[i];
    v[x] = std::min(v[x], std::min(v[fa[x]] + 1, v[fa[fa[x]]] + 2));
    if (v[x] > 2) {
      v[fa[fa[x]]] = 0;
      ++ans;
      v[fa[fa[fa[x]]]] = std::min(v[fa[fa[fa[x]]]], 1);
      v[fa[fa[fa[fa[x]]]]] = std::min(v[fa[fa[fa[fa[x]]]]], 2);
    }
  }
  printf("%d\n", ans);
  return 0;
}
