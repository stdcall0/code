#include <bits/stdc++.h>
using namespace std;

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const ll P = (ll)1e9 + 7;
ll fpow(ll x, ll y) {
  if (!y) return 1;
  if (y == 1) return x % P;
  ll rr = fpow(x, y >> 1ll);
  return rr * rr % P * ((y & 1ll) ? x : 1ll) % P;
}
inline ll getinv(ll x) { return fpow(x, P-2); }
const int N = 1e6 + 5;
ll fac[N], finv[N], ans=1;

ll targetVal;
ll cntA, cntB;

void Fuck(ll l, ll r, ll k) {
  if (l == r || k == 0) {
    (ans *= finv[r - l + 1]) %= P;
    if (targetVal == -1) targetVal = r - l + 1, cntA = 1;
    else if (r-l+1 < targetVal) {
      assert(targetVal - 1 == r-l+1);
      targetVal = r-l+1;
      cntB = cntA; cntA = 1;
    } else {
      if (r-l+1 == targetVal) {
        ++cntA;
      } else {
        assert(r-l+1 == targetVal+1);
        ++cntB;
      }
    }
    return;
  }
  ll mid = l + r >> 1;
  Fuck(l, mid, k-1);
  Fuck(mid+1, r, k-1);
}

int main() {
  ll T, n, k;

  fac[0] = fac[1] = 1;
  finv[0] = finv[1] = getinv(1);
  for (int i=2; i<=N - 4; ++i) {
    fac[i] = fac[i-1] * i % P;
    finv[i] = getinv(fac[i]);
  }

  cin >> T; while (T--) {
    cin >> n >> k;
    ans = fac[n];
    targetVal = -1;
    Fuck(1, n, k);
    cerr << "Target: " << targetVal << " with (" << cntA << ", " << cntB << ")." << endl;
    cout << ans << endl;
  }
  return 0;
}