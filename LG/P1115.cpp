#include <bits/stdc++.h>
using namespace std;

auto fast_io = [](){ ios :: sync_with_stdio(0); cin.tie(nullptr); };

int n, x;

int main() {
    fast_io(); int mx(-1e9), cu(0);
    cin >> n; for (int i=1; i<=n; i++) {
        cin >> x;
        cu += x; mx = max(mx, cu); cu = cu < 0 ? 0 : cu;
    }
    cout << mx << endl;
    return 0;
}