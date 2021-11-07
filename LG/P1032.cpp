#include <bits/stdc++.h>
using namespace std;

map<string, int> a;
deque<string> Q;
vector<pair<string, string> > v;
string frm, dest;

void expand(string& x) {
  for (int i=0; i<v.size(); ++i) {
    int p = 0;
    while ((p = x.find(v[i].first, p)) != string::npos) {
      string y = x;
      y.replace(p, v[i].first.size(), v[i].second);
      if (!a[y]) {
        a[y] = a[x] + 1;
        if (a[y] < 10 && y.size() < 30) Q.push_back(y);
      }
      p = p + 1;
    }
  }
}

int main() {
  cin >> frm >> dest;
  string a, b;
  while (cin >> a >> b) v.push_back({a, b});
  Q.push_back(frm);
  while (!Q.empty()) {
    string x = Q.front(); Q.pop_front();
    expand(x);
  }
  if (!(::a[dest] <= 10 && ::a[dest] >= 1)) puts("NO ANSWER!");
  else printf("%d\n", ::a[dest]);
  return 0;
}