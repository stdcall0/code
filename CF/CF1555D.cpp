#include <bits/stdc++.h>

const int N = 2e5 + 5;
int n, m;
std::string s;
std::vector<std::array<int, N> > v;

int main() {
  std::ios::sync_with_stdio(false);
  std::string s;
  std::cin >> n >> m >> s;

  std::string t = "abc";

  do {
    static std::array<int, N> p;
    p[0] = s[0] != t[0];
    for (int i = 1; i < s.size(); ++i) {
      p[i] = p[i - 1] + (s[i] != t[i % 3]);
    }
    v.push_back(p);
  } while (std::next_permutation(t.begin(), t.end()));
  while (m--) {
    static int l, r, ans;
    std::cin >> l >> r;
    ans = 114514114; for (auto &p : v)
      ans = std::min(ans, p[r - 1] - (l == 1 ? 0 : p[l - 2]));
    printf("%d\n", ans);
  }
  return 0;
}
