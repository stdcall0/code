#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;
int n;
struct Po { double x, y; } a[N];
bool cmpx(const Po&a, const Po&b) { return a.x < b.x; }
bool cmpy(const Po&a, const Po&b) { return a.y < b.y; }
inline double sqr(double x) { return x * x; }
inline double dis(int p, int q) { return sqrt(sqr(a[p].x - a[q].x) + sqr(a[p].y - a[q].y)); }

double d = 1145141919810114514.;
deque<int> Q;

void dfs(int l, int r) {
  if (l >= r) return;
  int mid = l + r >> 1;
  double mv = a[mid].x;
  dfs(l, mid); dfs(mid+1, r);
  inplace_merge(a+l, a+mid+1, a+r+1, cmpy);
  Q.clear();
  for (int i=l; i<=r; ++i) if (abs(a[i].x - mv) <= d) {
    while (!Q.empty() && abs(a[i].y - a[Q[0]].y) > d) Q.pop_front();
    for (int j : Q) d = min(d, dis(i, j));
    Q.push_back(i);
  }
}

int main() {
  scanf("%d", &n);
  for (int i=1; i<=n; ++i) {
    scanf("%lf%lf", &a[i].x, &a[i].y);
  }
  sort(a+1, a+1+n, cmpx);
  dfs(1, n);
  printf("%.2lf ", d);

  srand(time(0));
  for (int k=1; k<=114; ++k) {
  int s = rand() % n + 1;
  for (int i=1; i<=5; ++i) {
    double d2 = 0; int ns = s;
    for (int j=1; j<=n; ++j) if (s != j && dis(s, j) > d2) {
      d2 = dis(s, j); ns = j;
    }
    d = max(d, d2);
    s = ns;
  }
  }
  printf("%.2lf\n", d);
  return 0;
}