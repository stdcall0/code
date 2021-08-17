#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll P = 1e9 + 7;
ll a[65], pw[65];

int main() {
  a[1] = 0; pw[0] = 1; pw[1] = 2;
  for (int i = 2; i < 64; ++i) {
    pw[i] = pw[i - 1] * 2;
    a[i] = (a[i-1] + (pw[i-1] + P - 1) % P * (pw[i-2] % P)) % P;
  }
  int T;
  scanf("%d", &T);
  while (T--) {
    ll n; scanf("%lld", &n);
    int hb = std::__lg(n);
    assert(n >= pw[hb]);
    ll remain = (n - pw[hb]) % P;
    ll ans = a[hb] * 2 % P;
    // printf("debug: highest bit %d, pw %lld, remain %lld, ans %lld\n", hb, pw[hb], remain, ans);
    (ans += (remain + 1ll) * remain % P) %= P;
    printf("%lld\n", ans);
  }
  return 0;
}
