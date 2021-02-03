#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    typedef long double ld;
    ld sum = 2, cur;
    if (n <= 2) {
        cout << fixed << setprecision(5) << (ld)((n-1) ? 2 : 0) << endl;
        return 0;
    }
    if (n >= 50000000) {
        --n;
        cout << fixed << setprecision(5) << ((ld)1 + log(n) + 0.577215664901532860606512090082) << endl;
        return 0;
    }
    for (int i=3; i<=n; i++) {
        cur = (ld)1 / (i-1) * sum + (ld) i / (i-1);
        sum += cur;
    }
    cout << fixed << setprecision(5) << cur << endl;
    return 0;
}
