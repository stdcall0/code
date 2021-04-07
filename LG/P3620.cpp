#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;
const int N = 5e5 + 5;

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

int n, k;
ll a[N];
struct node {
  ll v; int i;
  inline bool operator< (const node &res) const {
    return v > res.v;
  }
};
priority_queue<node> q;
bool frag[N];
int l[N], r[N];

int main() {
  n = R(); k = R(); int la = R();
  for (int i=1; i<n; i++) {
    scanf("%lld", &a[i]);
    a[i] -= la; la += a[i];
    q.push({a[i], i});
    l[i] = i - 1; r[i] = i + 1;
  }
  ll ans = 0;
  a[0] = a[n] = 0x3f3f3f3f;
  while (k--) {
    while (frag[q.top().i]) q.pop();
    node t = q.top(); q.pop();
    ans += t.v;
    t.v = a[t.i] = a[l[t.i]] + a[r[t.i]] - a[t.i];
    q.push(t); frag[l[t.i]] = frag[r[t.i]] = 1;
    l[t.i] = l[l[t.i]]; r[t.i] = r[r[t.i]];
    l[r[t.i]] = t.i; r[l[t.i]] = t.i;
  }
  printf("%lld\n", ans);
  return 0;
}
