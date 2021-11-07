#include <bits/stdc++.h>
using namespace std;

const int N = 55, M = 405;
int a[N][M], n, m;
int h[N], v[N], rt[N];
int tmp[M * 3], cnt[N];
bool sm[M];
struct op { int x, y; };
vector<op> o;

int Count(int x, int col) {
  return count(a[x]+1, a[x]+h[x]+1, col);
}
int Max(int x) {
  assert(h[x] > 0);
  return *max_element(a[x]+1, a[x]+h[x]+1);
}
int Top(int x) {
  assert(h[x] > 0);
  return a[x][h[x]];
}
int FindTmp(int x, int y) {
  for (int i=1; i<=n; ++i) {
    if (h[i] == m && i != x && i != y)
      return i;
  }
  assert(false); return 0;
}
void Put(int x, int y) {
  assert(h[x] > 0); assert(h[y] < m);
  o.push_back({x, y});
  a[y][++h[y]] = a[x][h[x]--];
}
void Extract(int x, int col, int f, int e) {
  assert(h[x] == h[f] && h[f] == m);
  assert(h[e] == 0);
  int v = Count(x, col);
  for (int i=1; i<=v; ++i) Put(f, e);
  for (int i=1; i<=m; ++i) {
    if (Top(x) == col) Put(x, f);
    else Put(x, e);
  }
  for (int i=1; i<=m-v; ++i) Put(e, x);
  for (int i=1; i<=v; ++i) Put(f, x);
  for (int i=1; i<=v; ++i) Put(e, f);
}
void Split(int x, int y, int f, int e) {
  assert(h[x] == h[y] && h[y] == h[f] && h[f] == m);
  assert(h[e] == 0);
  for (int i=1; i<=m; ++i) tmp[i] = a[x][i], tmp[i + m] = a[y][i];
  sort(tmp+1, tmp+m*2+1);
  for (int i=1; i<=m; ++i) ++cnt[tmp[i]];
  int v = 0;
  for (int i=1; i<=m; ++i)
    if (cnt[a[x][i]] == 0) ++v, sm[i] = 1;
    else --cnt[a[x][i]], sm[i] = 0;
  for (int i=1; i<=v; ++i) Put(f, e);
  for (int i=1; i<=m; ++i)
    if (sm[m-i+1]) Put(x, f); else Put(x, e);
  for (int i=1; i<=m-v; ++i) Put(e, x);
  for (int i=1; i<=m; ++i)
    if (cnt[a[y][m-i+1]]) --cnt[a[y][m-i+1]], Put(y, x); else Put(y, e);
  for (int i=1; i<=m-v; ++i) Put(e, y);
  for (int i=1; i<=v; ++i) Put(f, y);
  for (int i=1; i<=v; ++i) Put(e, f);
}
void MergeSort(int L, int R) {
  if (L >= R) return;
  int mid = L + R >> 1;
  MergeSort(L, mid); MergeSort(mid+1, R);
  int l = L, r = mid+1, idx = L;
  while (l <= mid && r <= R) {
    if (Max(v[l]) < Max(v[r])) {
      Split(v[l], v[r], FindTmp(v[l], v[r]), n + 1);
      rt[idx++] = v[l++];
    } else {
      Split(v[r], v[l], FindTmp(v[l], v[r]), n + 1);
      rt[idx++] = v[r++];
    }
  }
  while (l <= mid) rt[idx++] = v[l++];
  while (r <= R) rt[idx++] = v[r++];
  for (int i=L; i<=R; ++i) v[i] = rt[i];
}
void Solve() {
  if (n == 1) return;
  if (n == 2) {
    Extract(1, 1, 2, 3);
    Extract(2, 1, 1, 3);
    int v = Count(1, 1);
    while (v--) Put(1, 3);
    v = Count(2, 1);
    while (v--) Put(2, 3);
    while (h[1]) Put(1, 2);
    while (h[3]) Put(3, 1);
  } else MergeSort(1, n);
}

int main() {
  scanf("%d%d", &n,&m);
  for (int i=1; i<=n; ++i) {
    h[i] = m; v[i] = i;
    for (int j=1; j<=m; ++j) {
      scanf("%d", &a[i][j]);
    }
  }
  o.clear();
  Solve();
  printf("%d\n", o.size());
  for (auto &i : o) printf("%d %d\n", i.x,i.y);
  return 0;
}
