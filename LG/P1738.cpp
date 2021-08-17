#include <bits/stdc++.h>
using namespace std;

set<string> fs;

int main() {
  int n; scanf("%d", &n);
  int ycz = 0;
  while (n--) {
    static string s;
    cin >> s; s += '/';
    int pos = 0;
    while ((pos = s.find('/', pos + 1)) != string::npos) {
      string sub = s.substr(0, pos);
      if (!fs.count(sub)) ++ycz, fs.insert(sub);
    }
    printf("%d\n", ycz);  
  }
  return 0;
}