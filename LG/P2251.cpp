#include <bits/stdc++.h>
using namespace std;

auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

int n, m, a[1000055];
deque<int> Q;

int main() {
  cin >> n >> m;

  for (int i=1; i<=n; i++) {
    cin >> a[i];
    while (Q.size() && i - Q[0] >= m) Q.pop_front();
    while (Q.size() && a[i] <= a[*--Q.end()]) Q.pop_back();
    Q.push_back(i);

    if (i >= m) cout << a[Q[0]] << endl;
  }

  return 0;
}
