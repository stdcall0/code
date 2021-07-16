#include <cstdio>
#include <cassert>
#include <algorithm>
#include <deque>

const int N = 845;
int n, cnt[N][N], mx[N], a[N];
std::deque<int> Q[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n-i+1; ++j) {
      static int x;
      scanf("%d", &x);
      ++cnt[i][x];
      mx[x] = i;
    }
  }
  Q[n].push_back(1);
  for (int i = 1; i <= n; ++i) {
    int j;
    for (j = mx[i] - 1; j >= 1; --j)
      if (cnt[j][i] < cnt[mx[i]][i] + mx[i] - j) break;
    int x = Q[mx[i]].front();
    a[x + j] = i; Q[mx[i]].pop_front();
    Q[j].push_front(x); Q[mx[i] - j - 1].push_back(x + j + 1);
  }
  for (int i = 1; i <= n; ++i)
    printf("%d ", a[i]);
  puts("");
  return 0;
}
