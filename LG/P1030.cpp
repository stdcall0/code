#include <bits/stdc++.h>
using namespace std;

string a, b;

inline string fuckycz(int l, int r, int p, int q) {
  // [L, R] in a
  if (l > r || p > q) return "";
  if (l == r) return string {a[l]};
  int pos = a.find(b[q]);
  return string {b[q]} + fuckycz(l, pos - 1, p, p + pos - l - 1) + fuckycz(pos + 1, r, q - r + pos, q - 1);
}

int main() {
  cin >> a >> b;
  cout << fuckycz(0, a.size() - 1, 0, b.size() - 1) << endl;
  return 0;
}
