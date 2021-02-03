#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t,n,c0,c1,h; char s[2005]; int v[2];
    cin >> t;
    while (t--) {
        cin >> n >> v[0] >> v[1] >> h >> s;
        int ans = 0;
        for (int i=0; i<n; i++) {
            bool tb = s[i] - '0';
            int cp = v[tb];
            int op = v[!tb] + h;
            ans += min(cp, op);
        }
        cout << ans << endl;
    }
    return 0;
}
