#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6 + 5;

namespace U {
  inline ll retR() {
    ll ret(0), c(0); bool neg(0); while (!isdigit(c = getchar())) neg = c == '-';
    ret = c - '0'; while (isdigit(c = getchar())) ret *= 10ll, ret += c - '0';
    return neg ? -ret : ret;
  }
  template <typename IntVal>
  inline void refR(IntVal v) { v = retR(); }
}; // Utils
auto R = U::retR;

int n;
char s[N];
ull pw[N], h[N];
int a[N];

inline ll getHash(int i, int j) { return h[j] - h[i-1] * pw[j-i+1]; }
inline bool cmp(int x, int y) {
  int l = -1, r = min(n-x, n-y);
  while (l < r) {
    int mid = l + r + 1 >> 1;
    if (getHash(x, x + mid) == getHash(y, y + mid)) l = mid;
    else r = mid - 1;
  }
  if (l > min(n-x, n-y)) return x > y;
  else return s[x + l + 1] < s[y + l + 1];
}

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  pw[0] = 1; for (int i=1; i<=n; i++) {
    pw[i] = pw[i-1] * 233;
    h[i] = h[i-1] * 233 + s[i];
    a[i] = i;
  }
  stable_sort(Rn(a, n), cmp);
  for (int i=1; i<=n; i++) printf("%d ", a[i]);
  puts("");
  return 0;
}
