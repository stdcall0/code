#include <bits/stdc++.h>
using namespace std;

string S, T, m;
int n;

vector<int> p, q;
void getPref(const string& s) {
  p = vector<int>(s.size());
  p[0] = 0;
  for (int i=1; i<s.size(); ++i) {
    int j = p[i-1];
    while (j>0 && s[i] != s[j]) j = p[j-1];
    p[i] = j + (s[i] == s[j]);
  }
  
}

int main() { ios::sync_with_stdio(0);
  cin >> T >> S; n = S.size();
  getPref(m = S + "#" + T);
  for (int i = n + 1, _ = m.size(); i < _; ++i) {
    if (p[i] == n) printf("%d\n", i - n * 2 + 1);
  }
  for (int i = 0; i < n; ++i)
    printf("%d ", p[i]);
  puts(""); return 0;
}
