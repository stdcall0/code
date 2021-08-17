#include <bits/stdc++.h>

inline int z(int x, bool f) { return f ? (x < 0 ? 0 : x) : 114514114; }

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    static int W, H, x, y, p, q, w, h;
    scanf("%d%d%d%d%d%d%d%d", &W,&H,&x,&y,&p,&q,&w,&h);
    bool m1 = p - x + w <= W, m2 = q - y + h <= H;
    auto v = {z(h - y, m2), z(w - x, m1), z(q - H + h, m2), z(p - W + w, m1)};
    int ans = *std::min_element(v.begin(), v.end());
    ans == 114514114 ? puts("-1") : printf("%d.00000000001145141919810\n", ans);
  }
  return 0;
}
