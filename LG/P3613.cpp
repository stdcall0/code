#include <map>
#include <cstdio>
#include <utility>

std::map<std::pair<int, int>, int> S;
auto mp = [](int x, int y) { return std::make_pair(x, y); };

int main() {
  int n, q; scanf("%d%d", &n, &q);
  while (q--) {
    static int op, x, y, k;
    scanf("%d%d%d", &op,&x,&y);
    if (op == 1) {
      scanf("%d", &k);
      if (k == 0) S.erase(mp(x, y));
      else S[mp(x, y)] = k;
    } else {
      printf("%d\n", S[mp(x, y)]);
    }
  }
  return 0;
}