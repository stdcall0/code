#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll P = 1e9 + 7;
const ll N = 5 * 1e5 * 2;
array<int, N> a, b;

int main () {
    ll n, ans = 0, sa = 0, sb = 0; cin >> n;
    for (int i=1; i<=n; i++) {
        scanf("%d", &sa); a[i] = (a[i-1] + sa) % P;
    }
    for (int i=1; i<=n; i++) {
        scanf("%d", &sa); b[i] = (b[i-1] + sa) % P;
    }
    sa = 0; for (int i=1; i<=n; i++) {
        (ans += (n+1) * a[i] % P * b[i] % P) %= P;
        sa += a[i]; sb += b[i];
    }
    ans = (ans - sa * sb % P + P) % P;
    cout << ans << endl;
    return 0;
}

