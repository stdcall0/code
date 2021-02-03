#include <bits/stdc++.h>
using namespace std;

auto fast_io = [](){ ios :: sync_with_stdio(0); cin.tie(nullptr); };
int n, a[205][205];

int main() {
    fast_io(); cin >> n;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            cin >> a[i][j];
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
        }
    }
    int ans=-127;
    for (int x1=1; x1<=n; x1++) for (int y1=1; y1<=n; y1++)
    for (int x2=x1; x2<=n; x2++) for (int y2=y1; y2<=n; y2++) {
        ans = max(ans, a[x2][y2] - a[x1-1][y2] - a[x2][y1-1] + a[x1-1][y1-1]);
    }
    cout<<ans<<endl;
    return 0;
}