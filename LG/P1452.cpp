#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 4e5 + 5;
int n;
struct Po { LL x, y; } a[N];
inline LL sqr(LL x) { return x * x; }
inline LL dis(int p, int q) { return sqr(a[p].x - a[q].x) + sqr(a[p].y - a[q].y); }

int main() {
  scanf("%d", &n);
  for (int i=1; i<=n; ++i) {
    scanf("%lld%lld", &a[i].x, &a[i].y);
  }
  LL d = 0;
  srand(19530515);
  for (int k=1; k<=250; ++k) {
  int s = rand() % n + 1;
  for (int i=1; i<=5; ++i) {
    LL d2 = 0; int ns = s;
    for (int j=1; j<=n; ++j) if (s != j && dis(s, j) > d2) {
      d2 = dis(s, j); ns = j;
    }
    d = max(d, d2);
    s = ns;
  }
  }
  printf("%lld\n", d);
  return 0;
}