#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const ll P = (ll)1e9 + 7;
const int N = 1e6 + 5;
ll fac[N], ans=1;

ll fpow(ll x, ll y) {
  if (!y) return 1;
  if (y == 1) return x % P;
  ll rr = fpow(x, y >> 1ll);
  return rr * rr % P * ((y & 1ll) ? x : 1ll) % P;
}
inline ll getinv(ll x) { return fpow(x, P-2); }

int main() {
  ll T, n, k;

  fac[0] = fac[1] = 1;
  for (int i=2; i<=N - 4; ++i) {
    fac[i] = fac[i-1] * i % P;
  }

  ll invTwo = getinv(2);

  cin >> T; while (T--) {
    cin >> n >> k;
    ans = fac[n];
    ll uSiz = n, cnt = 1;
    for (int i=1; i<=k; i++) {
      cnt *= 2;
      if (cnt > n) {
        cnt = n; break;
      }
      uSiz /= 2;
    }
    cerr << k << endl;
    ll b = (n - uSiz * cnt % P + P) % P;
    ll a = (cnt - b + P) % P;
    // cerr << "Target: " << uSiz << " with (" << a << ", " << b << ")." << endl;
    
    ans = fac[n] * fpow(getinv(fac[uSiz]), a) % P * fpow(getinv(fac[uSiz + 1]), b) % P;
    cout << ans << endl;
  }
  return 0;
}