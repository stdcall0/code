#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
typedef long long ll;
typedef unsigned long long ull;

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
ll M;

const ll P[8] = {2, 3, 5, 7, 11, 13, 17, 19};
inline int sfactor(int x, int &rm) {
  int res = 0;
  for (int i=0; i<8; ++i) {
    res <<= 1;
    if (x % P[i] == 0) {
      res |= 1;
      while (x % P[i] == 0) x /= P[i];
    }
  }
  rm = x; return res;
}

struct num {
  int v, sta, fac; // sta: status bin  fac: biggest factor
  inline bool operator< (const num &res) const {
    return fac < res.fac;
  }
} a[505];

const int S = 1 << 8;
typedef ll arr[S + 2][S + 2];
arr dp, f1, f2;

int main() {
  n = R(), M = R(); --n;
  for (int i=2; i<=n+1; i++) {
    int bf; int s = sfactor(i, bf);
    a[i - 1] = num {i, s, bf};
    // printf("Num %d: sta %d maxfac %d\n", i, s, bf);
  }
  sort(Rn(a, n));
  dp[0][0] = 1;
  for (int rnd=1; rnd<=n; rnd++) {
    if (rnd == 1 || a[rnd].fac != a[rnd-1].fac || a[rnd].fac == 1) {
      memcpy(f1, dp, sizeof(f1)); memcpy(f2, dp, sizeof(f2));
    }
    for (int i=S-1; i>=0; --i) {
      for (int j=S-1; j>=0; --j) {
        if (i & j) continue;
        if (!(i & a[rnd].sta)) (f1[i][j | a[rnd].sta] += f1[i][j]) %= M;
        if (!(j & a[rnd].sta)) (f2[i | a[rnd].sta][j] += f2[i][j]) %= M;
      }
    }
    if (rnd == n || a[rnd].fac != a[rnd+1].fac || a[rnd].fac == 1) {
      for (int i=0; i<S; ++i) for (int j=0; j<S; ++j) if (! (i&j)) {
        (dp[i][j] = f1[i][j] + f2[i][j] - dp[i][j] + M) %= M;
      }
    }
  }
  ll ans = 0;
  for (int i=0; i<S; ++i) {
    for (int j=0; j<S; ++j) {
      if (i & j) continue;
      (ans += dp[i][j]) %= M;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
