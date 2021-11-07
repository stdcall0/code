#include <cstdio>
#include <iostream>
#include <string>

const int maxN = 2e5 + 5;

std::string s;
int a[maxN], b[maxN];

int main() {
  std::cin >> s;
  int n = s.size();
  s += s;
  a[0] = 0;
  for (int i = 1; i < s.size(); ++i) {
    if (s[i] != s[i - 1])
      a[i] = a[i - 1] + 1;
    else
      a[i] = 0;
  }
  for (int i = s.size() - 1; i >= 0; --i) {
    if (s[i] != s[i + 1])
      b[i] = b[i + 1] + 1;
    else
      b[i] = 0;
  }
  int ans = 1;
  for (int i = 0; i < n; ++i)
    if (s[i] != s[i + 1])
      ans = std::max(ans, a[i] + b[i] + 1);
  printf("%d\n", std::min(n, ans));
  return 0;
}
