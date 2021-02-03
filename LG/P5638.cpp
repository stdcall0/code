#include <bits/stdc++.h>
using namespace std;

auto fast_io = [](){ ios :: sync_with_stdio(0); cin.tie(nullptr); };
#define int long long
int n, a[1000005], k;

signed main() {
    cin >> n >> k; if (k >= n-1) { cout << 0 << endl; return 0; }
    for (int i=1; i<n; i++) {
        cin >> a[i]; a[i] += a[i-1];
    }
    int ans = a[k];
    for (int K=2; K<=max(1LL, n - k); K++) {
        ans = max(ans, a[k+K-1] - a[K-1]);
    }
    cout << (a[n-1] - ans) << endl;
    return 0;
}