#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, k, l, p, sv=0,c=0; cin >> n >> k;
        ll ans = 0; p = n - (n + 1) / 2 + 1;
        for (sv=n*k; c<k&&sv>=1; sv--) if ((n*k-sv+1) % p == 0) ++c;
        for(int i=1; i<=sv; ++i) cin >> l;
        for (int i=sv+1; i<=n*k; i++) {
            cin >> l;
            //printf("%d[%d] is %d\n", i, (n+1)/2, (n*k-i+1) % p);
            if ((n*k-i+1) % p == 0) ans += (ll) l;
        }
        cout << ans << endl;
    }
    return 0;
}
