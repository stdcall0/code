#include <bits/stdc++.h>
using namespace std;

const int MM[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    string s; cin >> s;
    int ans = 5;
    for (int m = 1; m <= 12; ++m) for (int d = 1; d <= MM[m]; ++d) {
        ans = min(ans, (m/10+'0' != s[0]) + (m%10+'0' != s[1]) + (d/10+'0' != s[3]) + (d%10+'0' != s[4]));
    }
    printf("%d\n", ans);
    
    return 0;
}
