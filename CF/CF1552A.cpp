#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n; scanf("%d", &n);
    std::string s, s1; std::cin >> s;
    s1 = s;
    std::sort(s.begin(), s.end());
    int ans = 0;
    for (int i = 0; i < s.length(); ++i) {
      ans += s1[i] != s[i];
    }
    printf("%d\n", ans);
  }
  return 0;
}
