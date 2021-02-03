#include <bits/stdc++.h>
using namespace std;

string s[55]; bool f[55][55];
typedef long long ll;
ll g[55];

int main() {
// input
  int n; cin >> n;
  for (int i=1; i<=n; i++) {
    cin >> s[i];
  }

// pre process
  sort(s+1, s+1+n);
  for (int i=1; i<n; i++) {
    for (int j=i+1; j<=n; j++) {
      if (s[i].size() <= s[j].size() && s[j].substr(0, s[i].size()) == s[i]) f[i][j] = 1;
      if (s[i].size() > s[j].size() && s[i].substr(0, s[j].size()) == s[j]) f[i][j] = 1;
    }
  }

// calc answer
  for (int i=1; i<=n; i++) {
    g[i] = 1;
    for (int j=1; j<i; ++j) if (!f[j][i]) {
      g[i] += g[j];
    }
  }
  ll ans = 1; for (auto x : g) ans += x;
  cout << ans << endl;
  return 0;
}