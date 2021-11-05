#include <cstdio>
#include <vector>
#include <algorithm>

const int maxN = 1e5 + 5;
const int maxV = 1 << 17;

struct BIT {
  int tr[maxV + 5], sz;
  inline void init(int n) {
    sz = n;
    for (int i = 1; i <= sz; ++i)
      tr[i] = 0;
  }
  inline void add(int x, int v = 1) {
    for (; x <= sz; x += x & -x)
      tr[x] += v;
  }
  inline int get(int x) {
    if (x == 0)
      return 0;
    int r = 0;
    for (; x; x -= x & -x)
      r += tr[x];
    return r;
  }
};

int n, m, k, s[maxN], R[maxN], ans[maxN];
std::vector<int> q[maxN]; // queries that L=i
std::vector<int> v[maxV]; // element that S[_]^k = i
BIT t;

int main() {
  static int u;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &u);
    s[i] = s[i - 1] ^ u;
    v[s[i] ^ k].push_back(i);
  }
  t.init(maxV);
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &u, &R[i]);
    q[u].push_back(i);
  }
  if (0 == k)
    t.add(n);
  for (int i = n; i >= 1; --i) {
    auto it = v[s[i - 1]].rbegin();
    for (; it != v[s[i - 1]].rend(); ++it) {
      if (*it < i - 1)
        break;
      t.add(*it);
    }
    auto itt = q[i].begin();
    for (; itt != q[i].end(); ++itt) {
      ans[*itt] = t.get(R[*itt]);
    }
  }
  for (int i = 1; i <= m; ++i)
    printf("%d\n", ans[i]);
  return 0;
}
