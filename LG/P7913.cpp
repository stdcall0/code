#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

const int maxN = 1e5 + 5;

struct Node {
  int x, v, id;

  inline bool operator< (const Node &r) const {
    return x < r.x;
  }
};

int n, m1, m2, r1[maxN], r2[maxN];
Node a1[maxN * 2], a2[maxN * 2];

void input(int m, Node *a) {
  static int x, y;
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    a[i * 2 - 1] = {x, 1, i};
    a[i * 2] = {y, -1, i};
  }
  std::sort(a + 1, a + m * 2 + 1);
}

void solve(int m, Node *a, int *r) {
  static std::priority_queue<int, std::vector<int>, std::greater<int> > Q;
  static int ref[maxN];

  memset(r, 0, sizeof(r));
  while (!Q.empty())
    Q.pop();
  for (int i = 1; i <= m; ++i)
    Q.push(i);

  for (int i = 1; i <= m * 2; ++i) {
    if (a[i].v == 1) {
      int k = Q.top();
      Q.pop();

      ref[a[i].id] = k;
      ++r[k];
    } else
      Q.push(ref[a[i].id]);
  }

  for (int i = 1; i <= n; ++i)
    r[i] += r[i - 1];
}

int main() {
  scanf("%d%d%d", &n, &m1, &m2);
  input(m1, a1),
  input(m2, a2);
  solve(m1, a1, r1),
  solve(m2, a2, r2);

  int ans = 0;
  for (int i = 0; i <= n; ++i)
    ans = std::max(ans, r1[i] + r2[n - i]);
  printf("%d\n", ans);
  return 0;
}
+