#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;
  size_t idx = s.find('Z');
  for (auto i = idx; i < s.size(); ++i) {
    if (s[i] != 'Z') {
      cout << "-1\n";
      return 0;
    }
  }
  auto fx = [](char x, bool v) { return x == 'Z' ? '0' : ((x == 'X') ^ v ? '1' : '0'); };
  for (size_t i = 0; i < s.size(); ++i) putchar(fx(s[i], 0)); putchar('\n');
  for (size_t i = 0; i < s.size(); ++i) putchar(fx(s[i], 1)); putchar('\n');
  return 0;
}
