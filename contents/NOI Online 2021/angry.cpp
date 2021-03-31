#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll P = 1e9 + 7;
const int li = 500 * 4 + 3 + 5;
const int K = 501;
ll a[li], sum[li][K + 3];
ll b[10], ind;
bitset<500005> bs;

ll fpow(ll x, ll y) {
  if (y == 0) return 1;
  if (y == 1) return x % P;
  ll res = fpow(x, y >> 1ll);
  if (y & 1) return res * res % P * x % P;
  else return res * res % P;
}
inline ll inve(ll x) { return fpow(x, P-2); }

inline ll g(int k, ll x) { // 拉格朗日插值，计算A[0..n]的k次方和
  ll r = 0, z, m; ++k;
  for (int i=0; i<ind; ++i) {
    (r += fpow(b[i], k-1)) %= P;
  }
  if (!x) return r;
  // k = 1 -> 3 个点。i = 0 ~ k+1
  for (int i=0,p=3; i<=k; ++i,p+=4) { // k+1 个点
    z = m = 1; for (int j=0,q=3; j<=k; ++j,q+=4) {
      if (i == j) continue;
      (z *= x - q) %= P;
      (m *= p - q) %= P;
    }
    (m += P) %= P; (z += P) %= P;
    ll t = z * inve(m) % P * sum[p][k-1] % P;
    (r += t) %= P;
  }
  return r;
}

signed main() {
  a[0] = 1;
  for (int i=1; i<=li; i++) {
    a[i] = (i + 1) * 2 - 1 - (__builtin_popcount(i) & 1);
  }
  for (int i=1; i<=K; i++) sum[0][i] = 1;
  for (int i=1; i<=li; i++) {
    for (int j=1; j<=K; j++) {
      (sum[i][j] = sum[i-1][j] + fpow(a[i], j)) %= P;
    }
  }
  
  char c; ll n = 0;
  int bi = 0;
  while (isdigit(c = getchar())) {
    c -= '0';
    assert(c == 0 || c == 1);
    (n = n * 2 + c) %= P;
    bs[++bi] = c;
  }

  n = (n + 1) % P * inve(2) % P + (1 + b[1] ? -1 : 1) * (1 - (bs.count() & 1 ? -1 : 1)) * inve(4) % P;
  n %= P; (n += P) %= P;
  printf("%lld\n", n);
  ll n_pass = (n - 1 + P) % P, remain = 0, now;
  while (n_pass && n_pass % 4ll != 3ll) {
    --n_pass; ++remain;
  }
  ind = remain;
  while (remain > 0) {
    if (bs.count() & 1) {
      now = 0;
      for (int j=bi; j>=1; --j) {
        (now = now * 2 + bs[j]) %= P;
      }
      printf("%lld\n", now);
      b[--remain] = now;
    }
    if (remain == 0) break;
    bool s = 0;
    for (int j=1; j<=bi; ++j) {
      if (bs[j]) {
        s = 1; bs[j] = 0;
        for (int k=0; k<j; ++k) bs[k] = 1;
        break;
      }
    }
    assert(s);
  }
  int k; scanf("%d", &k);
  ll ans = 0; for (int r,t=0; t<k; ++t) {
    scanf("%d", &r);
    if (t == 0) (ans += n * r) %= P;
    else {
      printf("%dB: Ans %lld\n", t, ans);
      printf("%d: %lld\n", t, g(t, n_pass));
      (ans += g(t, n_pass) * r) %= P;
      printf("%d: Ans %lld\n", t, ans);
    }
  }
  printf("%lld\n", ans);
  return 0;
}