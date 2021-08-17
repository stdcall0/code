#include <bits/stdc++.h>
using namespace std;

string a, b;

inline string fuckycz(int l, int r, int p, int q) {
  // [L, R] in a
  if (l > r || p > q) return "";
  if (l == r) return string {a[l]};
  int pos = a.find(b[p]);
  // len1 : pos - l ; r - pos
  return fuckycz(l, pos - 1, p + 1, p + pos - l) + fuckycz(pos + 1, r, q - r + pos + 1, q) + string {b[p]};
}

int main() {
  cin >> a >> b;
  cout << fuckycz(0, a.size() - 1, 0, b.size() - 1) << endl;
  return 0;
}
