#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    int ans; scanf("%d", &ans); ans = std::abs(ans);
    for (int i=2,j; i<=n; i++) {
        scanf("%d", &j); ans = __gcd(ans , abs(j));
    }
    cout << ans << endl;
    return 0;
}
