#include <bits/stdc++.h>
using namespace std;

int mat[10][10], order[10], zerocnt[10];
int ans = -1;

inline int loc2modifier(int x, int y) {
  return 10 - max(abs(x - 4), abs(y - 4));
}
inline bool check(int x, int y) {
  static bool _[11];
    memset(_, 0, sizeof(_));
  for (int i = 0; i < 9; ++i) { // row
    if (mat[x][i] && _[mat[x][i]]) return 0;
    _[mat[x][i]] = 1;
  } memset(_, 0, sizeof(_));
  for (int i = 0; i < 9; ++i) { // col
    if (mat[i][y] && _[mat[i][y]]) return 0;
    _[mat[i][y]] = 1;
  } memset(_, 0, sizeof(_));
  for (int i = (x / 3) * 3; i < (x / 3 + 1) * 3; ++i)
    for (int j = (y / 3) * 3; j < (y / 3 + 1) * 3; ++j) { // mat
      if (mat[i][j] && _[mat[i][j]]) return 0;
      _[mat[i][j]] = 1;
    }
  return 1;
}
void dfs(int i, int y, int s = 0, int mask = 0) {
  int x = order[i];
  if (y == 9) return dfs(i + 1, 0, s, 0);
  if (i == 9) { ans = max(ans, s); return; }
  if (mat[x][y]) {
    if (!check(x, y)) return;
    dfs(i, y + 1, s + mat[x][y] * loc2modifier(x, y), mask | (1 << mat[x][y] - 1));
  } else {
    for (int v = 1; v <= 9; ++v) {
      if (mask & (1 << v - 1)) continue;
      mat[x][y] = v;
      if (check(x, y))
        dfs(i, y + 1, s + v * loc2modifier(x, y), mask | (1 << v - 1));
    }
    mat[x][y] = 0;
  }
}

int main() {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j)
      scanf("%d", &mat[i][j]), zerocnt[i] += mat[i][j] == 0;
    order[i] = i;
  }
  sort(order, order + 9, [](int x, int y) { return zerocnt[x] < zerocnt[y]; });
  dfs(0, 0);
  printf("%d\n", ans);
  return 0;
}
