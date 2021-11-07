#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;
int n, q, a[N], sz;
int col[N], knd = 0;
bool ans[N];

struct node {
  int l, r, id;
  bool operator<(const node& x) const {
    return (l / sz == x.l / sz) ? (r < x.r) : (l < x.l);
  }
} b[N];

inline void Add(int x) { if (++col[a[x]] == 2) ++knd; }
inline void Del(int x) { if (--col[a[x]] == 1) --knd; }

int main() {
  scanf("%d%d", &n,&q); sz = (int)sqrt(n);
  for (int i=1; i<=n; ++i) scanf("%d", &a[i]);
  for (int i=1; i<=q; ++i) {
    scanf("%d%d", &b[i].l, &b[i].r);
    b[i].id = i;
  }
  sort(b+1, b+1+q);
  int L=1, R=0;
  for (int i=1; i<=q; ++i) {
    while (b[i].l < L) Add(--L);
    while (b[i].r > R) Add(++R);
    while (b[i].l > L) Del(L++);
    while (b[i].r < R) Del(R--);
    ans[b[i].id] = knd == 0;
  }
  for (int i=1; i<=q; ++i)
    puts(ans[i] ? "Yes" : "No");
  return 0;
}
