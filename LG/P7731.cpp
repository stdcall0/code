#include <bits/stdc++.h>

int n, k[100005], b[100005], x1,y1,x2,y2;

int main() {
  scanf("%d%d%d%d%d", &n,&x1,&y1,&x2,&y2);
  for (int i=1; i<=n; ++i) {
    scanf("%d%d", &k[i], &b[i]);
  }
  if (x1==x2 && y1 <= y2) return puts("0"), 0;
  auto slope = [](int x, int y) { return 1. * (b[x]-b[y]) / (k[x]-k[y]); };
  auto s = -slope(x1, x2);
  if (y1 <= s && s <= y2) return puts("1"), 0;
  for (int i=1; i<=n; ++i) {
    if (i != x1 && i != x2) {
      auto s1 = -slope(x1, i), s2 = -slope(x2, i);
      if (y1 <= s1 && s1 <= s2 && s2 <= y2) return puts("2"), 0;
    }
  }
  puts("-1");
  return 0;
}