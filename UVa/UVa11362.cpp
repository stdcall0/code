#include <bits/stdc++.h>
using namespace std;

auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

const int N = 1e4 + 5;
string s[N];

int main() {
  int T; cin >> T;
  for (; T--; ) {
    int n; cin >> n;
    for (int i=1; i<=n; i++) {
      cin >> s[i];
    }
    sort(s+1, s+1 + n);
    for (int i=1; i<=n; i++) {
      if (i == n) {
        puts("YES");
      } else if (s[i + 1].find(s[i]) != string::npos) {
        puts("NO");
        break;
      }
    }
  }
  return 0;
}
