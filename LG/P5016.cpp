#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
array<ll, (int)1e5 + 5> a;

int main() {
    ll n, m, s1, p1, s2, mdid(-1); cin >> n;
    
    for (ll i=1; i<=n; i++) {
        scanf("%lld", &a[i]);
    }

    cin >> m >> p1 >> s1 >> s2;
    ll c1(0), mdet(0), ndet;
    for (ll i=1; i<=n; i++) c1 += a[i] * (m - i);
    c1 += s1 * (m - p1);
    for (ll p2=1; p2<=n; p2++) {
        ll c3(s2 * (m - p2));
        if ((ndet = std::abs(c1 + c3)) < mdet || mdid == -1) { // L || R
            mdid = p2, mdet = ndet;
        }
    }
    cout << mdid << endl;
    return 0;
}
